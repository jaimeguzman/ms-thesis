 //    Copyright 2014 Roberto Konow and Francisco Claude.

 //    This file is part of wum-index.

 //    Foobar is free software: you can redistribute it and/or modify
 //    it under the terms of the GNU General Public License as published by
 //    the Free Software Foundation, either version 3 of the License, or
 //    (at your option) any later version.

 //    Foobar is distributed in the hope that it will be useful,
 //    but WITHOUT ANY WARRANTY; without even the implied warranty of
 //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 //    GNU General Public License for more details.

 //    You should have received a copy of the GNU General Public License
 //    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <sstream>

#include "ssa.hpp"
#include "sequence.hpp"

#include <rmq.h>
#include <libcdsBitString.h>
#include <BitSequence.h>
#include <Sequence.h>
#include "utils.h"
#include <map>
using namespace cds_utils;
using namespace cds_static;
using namespace rmq_space;

using namespace std;
int main(int argc, char **argv) {

//	omp_set_dynamic(0); 
//	omp_set_num_threads(20);
	if (argc != 2) {
		cout << "usage: " << argv[0] << " <output> < input_file" << endl;
		return 0;
	}
	vector<unsigned int> sessions_sequence;
	vector<unsigned int> users_vector;
	vector<unsigned int> users_start;
	unsigned int users = 0;
	
	string s;
	// sessions_sequence.push_back(1);
	map<int,bool> t;
	while (getline(cin, s)) {
		stringstream ss(s);
		int loc;
		while ( ss >> loc ) {
			if (loc >= 0) {
				sessions_sequence.push_back(loc + 1);
				t[loc+1] = true;
				users_vector.push_back(users);
			}
		}
		sessions_sequence.push_back(1);
		users_vector.push_back(users);
		users++;
	}
	int key_max = t.rbegin()->first;
	int missing = 0;
	int next = 0;
	map<int,bool> check;
	for (int i = 2 ; i <= key_max;i++) {
		if (!t[i]) {
			// cout << i << " is missing " << endl;
			missing = i;
			for (int j = i+1 ; j <= key_max;j++) {
				if (t[j]) {
					next = j;
					// cout << "replacing " << missing << " with " << next << endl;
     				std::replace (sessions_sequence.begin(), sessions_sequence.end(), next, missing); // 10 99 30 30 99 10 10 99
					t[next] = false;
					check[missing] = true;
					missing = next;
					break;
				}
			}
		}
	}
	// map<int,bool> check2;
	// for (size_t i = 0 ; i < sessions_sequence.size();i++) {
	// 	check2[sessions_sequence[i]] = true;
	// }
	// cout << "-----------" << endl;
	// for (auto x: check2) {
	// 	cout << x.first << endl;
	// }
	
	
	reverse(sessions_sequence.begin(), sessions_sequence.end());
	reverse(users_vector.begin(), users_vector.end());
	users_vector.push_back(users);
	for (size_t i = 0; i < sessions_sequence.size(); i++) {
		if (sessions_sequence[i] == 1) {
			users_start.push_back(i);
		}
	}
	users_start.push_back(sessions_sequence.size()+1);

	sequence::Sequence<unsigned int> seq(sessions_sequence);

	const vector<size_t> &bwtperm = seq.GetBWTPerm();
	const vector<unsigned int> &bwt = seq.GetBWT();
	const vector<size_t> &sa = seq.GetSA();

	vector<size_t> ibwt(bwtperm.size(), 0);
	for (size_t i = 0; i < bwtperm.size(); i++) {
		ibwt[bwtperm[i]] = i;
	}
	vector<unsigned int> perm_users(users_vector.size(), 0);
	for ( size_t i = 0; i < bwtperm.size(); i++) {
		perm_users[ibwt[i]] = users_vector[i];
	}

	SSA<unsigned int> ssa;
	ssa.BuildIndex(sessions_sequence, bwt, sa);

	ofstream out(argv[1]);
	if (!out.good()) {
		return 1;
	}
	ssa.Save(out);

	BitString bm(sessions_sequence.size() + 1);
	for (auto i : users_start) {
		bm.setBit(i);
	}
	bm.setBit(sessions_sequence.size());
	BitSequenceRRR bs(bm, 32);
	bs.save(out);


	int *freqs = new int[bwt.size()];
	bool start_over = true;
	pair<size_t, size_t> p;
	for ( size_t i = 0; i < sessions_sequence.size(); i++) {
		unsigned int a = sessions_sequence[sessions_sequence.size() - i - 1];
		if (a == 1) { // a user sequence finishes
			start_over = true;
		} else { // we continue an existing one
			if (start_over) { // it's the beginning
				p = ssa.InitCountRange(a);
			} else { // we have to take a step
				p = ssa.StepCount(a, p);
			}
			freqs[ibwt[i]] = p.second - p.first + 1;
		}
	}

	// Build RMQ for freqs
	RMQ *r = new RMQ(freqs, sessions_sequence.size());
	r->save(out);
	// How the hell do I store this shit?
	delete r;
	delete[] freqs;

	// Building the Carray for muthu
	vector<uint> user_list;
	for (size_t pos = 0; pos < sessions_sequence.size(); pos++) {
		unsigned int user = bs.rank1(pos);
		user_list.push_back(user); 
	}
	Array *A = new Array(user_list);
    MapperNone * map = new MapperNone();
    BitSequenceBuilder * bsb = new BitSequenceBuilderRG(20);
    WaveletTreeNoptrs *wt = new WaveletTreeNoptrs(*A, bsb, map);

    int * Carray = new int[sessions_sequence.size()];
    int pos = 0;

    for (size_t i = 0 ; i < sessions_sequence.size() ; i++) {
        uint occ_symbol = wt->rank(user_list[i],i); // count the occs

        if (occ_symbol-1 == 0)
            pos = -1;

        else 
            pos = wt->select(user_list[i],occ_symbol-1); //


        if ((uint)pos >= (uint)-1) 
            pos = -1;

        Carray[i] = pos;
    }

    user_list.clear();
    RMQ *muthu = new RMQ(Carray,sessions_sequence.size());
    muthu->save(out);

    delete[] Carray;
    delete muthu;
    delete A;
    delete wt;  
    // End of Muthu

	// check if getting user is working
	for (size_t pos = 0; pos < sessions_sequence.size(); pos++) {
		size_t perm_pos = ibwt[pos];
		size_t p = ssa.Reverse(perm_pos) - 1;
		if (p != pos) {
			cout << "Error for position " << pos << endl;
			cout << "p = " << p << endl;
			cout << "permpos = " << perm_pos << endl;
		}

		// unsigned int user = distance(users_start.begin(), upper_bound(users_start.begin(), users_start.end(), pos));
		unsigned int user = bs.rank1(pos);
		if (users - user != perm_users[ibwt[pos]]) {
			cout << "Raton es una mierda" << endl;
			cout << "users = " << users << endl;	
			cout << "user = " << users-user << endl;
			cout << "perm_users = " << perm_users[bwtperm[pos]] << endl;
		}
	}
	out.close();
	// return 0;
	// return 0;
}

// Document listing for Muthu: -> this function is going to be in the other file
