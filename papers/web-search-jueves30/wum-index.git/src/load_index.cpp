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
int main(int argc, char **argv) {
	if (argc < 1) {
		cout << "usage: " << argv[0] << " indexed_file ";
		return 2;
	}
	ifstream in(argv[1],std::ios::binary);
	if (!in.good()) {
		cout << "file not readable " << endl;
		return 2;
	}
	Index<unsigned int> *index = new Index<unsigned int>(in);
	index->MostFrequent(10, 3);
	index->LeastFrequent(10, 3);
	vector<unsigned int> query;
	query.push_back(7);
	query.push_back(7);
	query.push_back(7);
	index->MostFrequentSeq(query, 10, 5);
	// query.push_back(8);
	// query.push_back(8);
		// -> according to grep "7 7 7" count is 2 // cat ../dataset/msn_test.seq | grep -o '13' | wc -l
	
	// query.push_back(13);
		// -> according to grep "13" count is 36 // cat ../dataset/msn_test.seq | grep -o '13' | wc -l

	// cout << "number of times: " << index->Count(query) << endl; // bad results
	// cout << "first user, first pos:" << index->Access(1, 0) << endl; // bad results
	// cout << "first user, second pos:" << index->Access(1, 1) << endl; // bad results
	// cout << " Third user, first pos:" << index->Access(3, 0) << endl; // bad results
	// cout << " Third user, first pos:" << index->Access(3, 3) << endl; // bad results
	// for (uint user_id = 1; user_id <= 10;user_id++) {
	// 	pair<unsigned int*,size_t> result = index->UserPath(user_id);
	// 	for (uint i = result.second ; i > 0;i--) {
	// 		cout << result.first[i-1] - 1 << " ";
	// 	}
	// 	cout << endl;
	// }

	// TEST FINDUSERS
	// vector<uint> t = index->FindUsers(query);
	// for (uint i = 0 ; i < t.size();i++) {
	// 	cout << t[i] << endl;
	// }
	
	// TEST PREDICT
	// vector<uint> t2 = index->Predict(query,15);
	// for (uint i = 0 ; i < t2.size();i++) {
	// 	cout << t2[i] << endl;
	// }
}