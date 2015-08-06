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
#include "index.hpp"
#include "utils.h"

using namespace std;
using namespace cds_static;
using namespace cds_utils;
using namespace rmq_space;

template <typename T>
unsigned long long experiments(Index<T> *index,int op, uint *params,Timer *t, ofstream &f,vector<vector<uint> > p = vector<vector<uint> >() ) {
	unsigned long long aux = 0;
	switch(op) {
		case 1: {
			// expAccess
			// params[0] = min user sequence_length;
			// params[1] = amount of accesses per user;
			vector<pair<size_t,size_t> > users;
			vector<uint> acceses;
			uint user_size = index->GetAmountUsers();
			size_t total_access = 0;
			for (uint i = 0 ; i < user_size;i++) {
				uint user_length = index->GetSeqLengthUser(i);
				if (user_length == params[0] ) {
					users.push_back(make_pair(i,user_length));
					acceses.push_back(((params[1]*1.0)/100.0)*user_length+1);
					total_access += acceses[acceses.size()-1];
				}
			}
			t->Restart();
			for (uint i = 0 ; i < users.size();i++) {
				for (uint j = 0;j<acceses[i];j++) {
					aux += index->Access(users[i].first,rand()%users[i].second);
				}
			}		
			t->Stop();
			f <<  params[0] << " " << total_access << " " <<  users.size() <<  " " << t->ElapsedTime() << " " << fixed <<  (t->ElapsedTime()*1.0)/(total_access*1.0) << endl;
			 break;
		}
		case 2: {
			// expUserPath
			// params[0] = min_user sequence length;
			vector<pair<size_t,size_t> > users;
			uint user_size = index->GetAmountUsers();
			for (uint i = 0 ; i < user_size;i++) {
				uint user_length = index->GetSeqLengthUser(i);
				if (user_length == params[0])
					users.push_back(make_pair(i,user_length));
			}

			t->Restart();
			for (uint i = 0 ; i < users.size();i++) {
					auto p = index->UserPath(users[i].first);
					aux += p.second;
					delete [] p.first;
			}		
			t->Stop();
			f << params[0] << " " << users.size() << " " << t->ElapsedTime() << " " << fixed << (t->ElapsedTime()*1.0)/(users.size()*1.0) << endl;
			break;
		}
		case 3: {
			//expCount
			// params[0] = n
			t->Restart();
			aux = 0;
			for (uint i = 0 ; i < p.size();i++) {
				aux += index->Count(p[i]);
			}					
			t->Stop();
			f << params[0] << " " << p.size() << " " <<  t->ElapsedTime() << " " << fixed << (t->ElapsedTime()*1.0)/(p.size()*1.0) << " " << aux <<  endl;
			break;
		}
		case 4: {
			//expPredict
			// params[0] = n
			// params[1] = k
			t->Restart();
			for (uint i = 0 ; i < p.size();i++) {
				vector<uint> v;
				index->Predict(p[i],params[1], v);
				aux += v.size();
			}					
			t->Stop();
			f << params[0] << " " << params[1] << " " << p.size() << " " <<  t->ElapsedTime() \
			 << " " << fixed << (t->ElapsedTime()*1.0)/(p.size()*1.0) << endl;
			
			break;			break;
		}
		case 5: {
			//expMostFrequent
			// params[0] = n_start
			// params[1] = n_end
			// params[2] = k_start;
			// params[3] = k_end;
			
			for (uint n = params[0] ; n < params[1];n+=2) {				
				for (uint k = params[2]; k < params[3];k+=params[3]/params[2]) {
					t->Restart();
					vector<uint*> v;
					index->MostFrequent(k, n, v);
					aux += v.size();
					t->Stop();
					for (auto t = v.begin(); t != v.end(); ++t)
						delete [] *t;
					f << n << " " << k << " " << fixed << t->ElapsedTime() << endl;
				}
			}
			break;
		}
		case 6: {
			//expLeastFrequent
			// params[0] = n_start
			// params[1] = n_end
			// params[2] = k_start;
			// params[3] = k_end;
			vector<uint*> v;
			for (uint n = params[0] ; n < params[1];n+=2) {				
				for (uint k = params[2]; k < params[3];k+=params[3]/params[2]) {
					t->Restart();
					vector<uint*> v;
					index->LeastFrequent(k, n, v);
					aux += v.size();
					t->Stop();
					for (auto t = v.begin(); t != v.end(); ++t)
						delete [] *t;
					f << n << " " << k << " " << fixed << t->ElapsedTime() << endl;
				}
			}
			break;
		}
		case 7: {
			//expMostFrequentSeq
			// params[0] = n_start
			// params[1] = n_end
			// params[2] = k_start;
			// params[3] = k_end;
			for (uint n = params[0] ; n < params[1];n+=2) {				
				for (uint k = params[2]; k < params[3];k+=params[3]/params[2]) {
					t->Restart();
					for (uint i = 0;i < p.size();i++) {
						vector<uint*> v;
						index->MostFrequentSeq(p[i],k,n,v);
						for (auto t = v.begin(); t != v.end(); ++t)
							delete [] *t;
					}
					t->Stop();
					f << params[4] << " " << n << " " << k << " " << p.size() << " " << fixed <<  (t->ElapsedTime()*1.0)/(p.size()*1.0) << endl;
				}
			}
			break;
		}
		case 8: {
			//expFindUsers
			// params[0] = n
			t->Restart();
			for (uint i = 0 ; i < p.size();i++) {
				index->FindUsers(p[i]);
			}					
			t->Stop();
			f << params[0] << " " << p.size() << " " <<  t->ElapsedTime() \
			 << " " << fixed << (t->ElapsedTime()*1.0)/(p.size()*1.0) << endl;
			break;
		}
		default:
			 cout << "Wrong op number" << endl;
			 break;
	}
	cout << "aux = " << aux << endl;
	return aux;
}

// access start_end_step;
uint paramranges1[] = {0,105,5};
uint paramranges2[] = {0,105,5};
uint paramranges3[] = {0,40,2};
uint paramranges4[] = {0,40,2,1,20,1};
uint paramranges5[] = {1,40,10,100};
uint paramranges6[] = {1,40,10,100};
uint paramranges7[] = {0,40,2,1,40,10,100};


int main(int argc, char** argv) {
	if (argc <= 1) {
		cout << "usage: " << argv[0] << "<index file> <original file> <amount of operations> <operation list [1...7]>" << endl;
		return 0;
	}
	const char * file = argv[1];
	const char * orig = argv[2];

	uint ops = (uint)atoi(argv[3]);
	uint *o = new uint[ops];

	ofstream *results = new ofstream[ops];
	for (uint i = 0;i<ops;i++) {
		o[i] = atoi(argv[i+4]);
		stringstream ss;
		ss << file << "." << o[i] << ".r";
		results[i].open(ss.str().c_str());
	}
	ifstream f(file,std::ios::binary);
	ifstream ff(orig);
	vector<vector<uint> > data = loadFile(ff);
	Timer *t = new Timer();
	Index<unsigned int> *index = new Index<unsigned int>(f);
	t->Stop();
	cout << "Time to Load Index: " << fixed << t->ElapsedTime() << endl;
	index->PrintSize();
	for (uint i = 0 ; i < ops;i++) {
		cout << "executing " << o[i] << endl;
		switch(o[i]) {
			case 1: {
				for (uint j = paramranges1[0]; j <= paramranges1[1];j += paramranges1[2]) {
					uint *params = new uint[2];
					params[0] = j;
					params[1] = 50;
					experiments(index,o[i],params,t,results[i]);
					delete[] params;
				}
				break;
			}
			case 2: {
				for (uint j = paramranges2[0]; j <= paramranges2[1];j += paramranges2[2]) {
					uint *params = new uint[1];
					params[0] = j;
					experiments(index,o[i],params,t,results[i]);
					delete[] params;	
				}
				break;
			}
			case 3: {
				for (uint j = paramranges3[0]; j <= paramranges3[1];j += paramranges3[2]) {
					uint *params = new uint[1];
					params[0] = j;
					vector<vector<uint> > p = genSequences(data, j);
					experiments(index,o[i],params,t,results[i],p);
					delete[] params;
				}
				break;
			}
			case 4: {
				for (uint j = paramranges4[0]; j <= paramranges4[1];j += paramranges4[2]) {
					for (uint k = paramranges4[3];k<=paramranges4[4];k+= paramranges4[5]) {
						uint *params = new uint[2];
						params[0] = j;
						params[1] = k;
						vector<vector<uint> > p = genSequences(data, j);
						experiments(index,o[i],params,t,results[i],p);
						delete[] params;
					}
				}
				break;
			}
			case 5: {
				experiments(index,o[i],paramranges5,t,results[i]);
				break;
			}
			case 6: {
				experiments(index,o[i],paramranges6,t,results[i]);
				break;
			}
			case 7: {
				for (uint j = paramranges7[0]; j <= paramranges7[1];j += paramranges7[2]) {
					uint *params = new uint[6];
					params[0] = paramranges7[3];
					params[1] = paramranges7[4];
					params[2] = paramranges7[5];
					params[3] = paramranges7[6];
					params[4] = j;
					vector<vector<uint> > p = genSequences(data, j);
					experiments(index,o[i],params,t,results[i],p);
					delete[] params;
				}
				break;
			}
			case 8: {
				for (uint j = paramranges3[0]; j <= paramranges3[1];j += paramranges3[2]) {
					uint *params = new uint[1];
					params[0] = j;
					vector<vector<uint> > p = genSequences(data, j);
					experiments(index,o[i],params,t,results[i],p);
					delete[] params;
				}
				break;
			}
		}
		results[i].close();
	}
	delete[] results;
	delete t;
	// delete index;
	delete[] o;
}
