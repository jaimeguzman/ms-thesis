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
#include <vector>
#include <map>
#include <sstream>
#include <queue>
using namespace std;
typedef unsigned int uint;

int main(int argc,char ** argv)  {
	vector<unsigned int> sessions_sequence;
	string s;
	string pattern = argv[1];
	while (getline(cin, s)) {
		stringstream ss(s);
		int loc;
		while ( ss >> loc ) {
			if (loc >= 0) {
				sessions_sequence.push_back(loc + 1);
			}
		}
		sessions_sequence.push_back(1);
	}
	map<string, uint> check;
	int begin = 0;
	int end = 1;
	bool start_over = true;
	for ( size_t i = 0; i < sessions_sequence.size(); i++) {
		unsigned int a = sessions_sequence[i];
		if (a == 1) { // a user sequence finishes
			start_over = true;
		} else { // we continue an existing one
			if (start_over) { // it's the beginning
				begin = i;
				end = i+1;
				start_over = false;
			} else { // we have to take a step
				end++;
			}
			stringstream ss;
			for (int j = begin;j < end;j++) {
				cout << sessions_sequence[j] << " ";
				ss << sessions_sequence[j] ;
			}
			if (check.find(ss.str()) == check.end()) {
				check[ss.str()] = 1;
			} else {
				check[ss.str()]++;
			}
			cout << endl;
		}
	}
	for(auto p = check.begin();p != check.end();++p) {
		cout << p->first << " , " << p->second << endl;
	}
	cout << "------------" << endl;
	priority_queue<pair<uint,string> > cola;
	for (auto p = check.find(pattern);p != check.end();++p) {
		cout << p->first.substr(0,pattern.size()+1) << " , " << p->second << endl;
		// cout << "Adding " << p->first.substr(pattern.size(),1) << endl;
		cola.push(make_pair(p->second,p->first.substr(pattern.size(),2)));
	}
		cout << "------------" << endl;

	while(!cola.empty()) {
		pair<uint,string> t = cola.top();
		cout << t.second << " -> " << t.first << endl;
		cola.pop();
	}
}