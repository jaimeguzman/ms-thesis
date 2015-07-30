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
#include <stack>
#include <queue>
#include <utility>
#include <tuple>
#include <rmq.h>
using namespace cds_static;
using namespace cds_utils;
using namespace rmq_space;
template <typename T> class Index {

protected:
	RMQ *weights_;
	RMQ *muthu_;
	SSA<T> *sequence_;
	BitSequenceRRR *bs_;
	uint users_;
	uint sigma_;

private: 
	pair<uint,uint> getUser(size_t user_id) {
		user_id = users_ - user_id;
		uint pos_user_begin = bs_->select1(user_id);
		if (pos_user_begin == (uint)-1) 
			__throw_out_of_range("user_id out of range");

		uint pos_user_end = bs_->select1(user_id+1) - 1;
		if (pos_user_end == (uint)-2) 
			pos_user_end = bs_->getLength()-1;

		return make_pair(pos_user_begin,pos_user_end);
	}

	void UserListing(uint i, uint j,uint &k,vector<uint> &results) {
		if (i>=j) return;
		if (j> sequence_->Length()) return;
		if (k == 0) return;
		// cout << "i = " << i << endl;
		// cout << "j = " << j << endl;
		cout << k << endl;
		uint pos = muthu_->query(i,j);
		uint user_id = bs_->rank1(sequence_->Reverse(pos)); 
		results.push_back(users_ - user_id); 

		
		k--;
		UserListing(i,pos-1,k,results);
		UserListing(pos+1,j,k,results);
	}
	void UserListingStack(uint i, uint j, uint k,vector<uint> &results) {
		pair<uint,uint> r = make_pair(i,j);
		stack<pair<uint,uint> > ranges;
		ranges.push(r);
		uint x,y,pos,user_id;
		while(!ranges.empty() && k!=0) {
			r = ranges.top();
			ranges.pop();
			x = r.first;
			y = r.second;
			if (x>=y)
				continue;
			pos = muthu_->query(i,j);
			user_id = bs_->rank1(sequence_->Reverse(pos)); 
			results.push_back(users_ - user_id); 

			k--;
			// cout << k << endl;
			ranges.push(make_pair(x,pos-1));	
			ranges.push(make_pair(pos+1,y));
		}
	}
public:
	Index(ifstream &in) {
		sequence_ = new SSA<T>(in);
		bs_ = BitSequenceRRR::load(in);
		weights_ = RMQ::load(in);
		muthu_  = RMQ::load(in);
		users_ = bs_->countOnes();
		sigma_ = sequence_->GetSigma();
		// T * reb = sequence_->Rebuild();
		// bool awesome = true;
		// for (int i = 0; i < sequence_->Length(); i++) {
		// 	if (reb[sequence_->Length() - 1 - i] == 1) {
		// 		cerr << endl;
		// 		awesome = true;
		// 	}
		// 	else {
		// 		cerr << (awesome?"":" ") << reb[sequence_->Length()-1 - i] - 1;
		// 		awesome = false;
		// 	}
		// }
	}
	~Index() {
		delete sequence_;
		delete weights_;
		delete bs_;
		delete muthu_;
	}


	uint GetAmountUsers() {
		return this->users_;
	}
	
	uint GetSeqLengthUser(size_t user_id) {
		pair<uint,uint> u = getUser(user_id);
		return u.second - u.first+1;
	}
	// Working OK
	T Access(size_t user_id,size_t pos) {
		pair<uint,uint> user_pos = getUser(user_id);
		size_t final_pos = user_pos.second - pos;
		T *seq = sequence_->Extract(final_pos, final_pos+1);
		T s = seq[0];
		delete [] seq;
		return s-1;

	}
	
	// Working OK
	pair<T*,size_t> UserPath(size_t user_id) {
		pair<uint,uint> user_pos = getUser(user_id);
		return make_pair(sequence_->Extract(user_pos.first+1,user_pos.second), user_pos.second-user_pos.first);
	}

	// Working OK
	size_t Count(vector<T> &path) {
		pair<size_t,size_t> range = sequence_->InitCountRange(path[0]+1);
		for (uint i = 1 ; range.first <= range.second && i < path.size();i++) { // we do not need to reverse this... right?
			range = sequence_->StepCount(path[i]+1, range);
		}
		if (range.first > range.second) return 0;
		return range.second - range.first + 1;
	}


	void Predict(vector<T> &path, uint k, vector<T> &result) {
		pair<size_t,size_t> range = sequence_->InitCountRange(path[0]+1);
		for (uint i = 1 ; range.first <= range.second && i < path.size(); i++)
			range = sequence_->StepCount(path[i]+1, range);
 		
 		if (range.first > range.second) return;

 		sequence_->TopK(range.first,range.second,k,result);
	}


	// NOT WORKING 	// feeling lazy to implement this one
	void MostFrequent(uint k, size_t n, vector<T*> &result) {
		typedef tuple<size_t, size_t, size_t, size_t> elems;
		priority_queue<elems, vector<elems>, less<elems>> q;
		vector<size_t> res;
		for (int i = 2; i < sigma_; i++) {
			pair<size_t, size_t> p = sequence_->InitCountRange(i);
			q.push(make_tuple(p.second - p.first + 1, 1, p.first, p.second));
		}
		while(!q.empty() && res.size() < k) {
			elems e = q.top();
			q.pop();
			if (n == get<1>(e)) {
				res.push_back(get<2>(e));
				// cout << " -> " << get<0>(e) << endl;
				continue;
			}
			auto p = make_pair(get<2>(e), get<3>(e));
			for (int i = 2; i < sigma_; i++) {
				auto r = sequence_->StepCount(i, p);
				if (r.first <= r.second) {
					elems t = make_tuple(r.second - r.first + 1, get<1>(e) + 1, r.first, r.second);
					q.push(t);
				}
			}
		}
		for (auto it = res.begin(); it != res.end(); ++it) {
			auto pos = sequence_->Reverse(*it);
			auto t = sequence_->Extract(pos, pos+n);
			result.push_back(t);
		}
	}

	// NOT WORKING 	// feeling lazy to implement this one
	void LeastFrequent(uint k, size_t n,vector<T*> &result) {
		typedef tuple<size_t, size_t, size_t, size_t> elems;
		priority_queue<elems, vector<elems>, greater<elems>> q;
		vector<size_t> res;
		for (int i = 2; i < sigma_; i++) {
			pair<size_t, size_t> p = sequence_->InitCountRange(i);
			q.push(make_tuple(p.second - p.first + 1, 1, p.first, p.second));
		}
		while(!q.empty() && res.size() < k) {
			elems e = q.top();
			q.pop();
			if (n == get<1>(e)) {
				res.push_back(get<2>(e));
				// cout << " -> " << get<0>(e) << endl;
				continue;
			}
			auto p = make_pair(get<2>(e), get<3>(e));
			for (int i = 2; i < sigma_; i++) {
				auto r = sequence_->StepCount(i, p);
				if (r.first <= r.second) {
					elems t = make_tuple(r.second - r.first + 1, get<1>(e) + 1, r.first, r.second);
					q.push(t);
				}
			}
		}
		for (auto it = res.begin(); it != res.end(); ++it) {
			auto pos = sequence_->Reverse(*it);
			auto t = sequence_->Extract(pos, pos+n);
			result.push_back(t);
		}
	}

	// MostCommonSubSeq(p,n,k)
	void MostFrequentSeq(vector<T> &seq, uint k, size_t n,vector<T*> &result) {
		// cout << "MostFrequentSeq" << endl;
		typedef tuple<size_t, size_t, size_t, size_t> elems;
		priority_queue<elems, vector<elems>, less<elems>> q;
		vector<size_t> res;
		pair<size_t, size_t> p = sequence_->InitCountRange(seq[0] + 1);
		for (auto it = seq.begin()+1; it != seq.end(); ++it) {
			if (p.first > p.second) {
				// cout << "No paths" << endl;
				return;
			}
			p = sequence_->StepCount(*it + 1, p);
		}
		if (p.first > p.second) {
			// cout << "No paths" << endl;
			return;
		}
		q.push(make_tuple(p.second - p.first + 1, seq.size(), p.first, p.second));
		while(!q.empty() && res.size() < k) {
			elems e = q.top();
			q.pop();
			if (n == get<1>(e)) {
				res.push_back(get<2>(e));
				// cout << " -> " << get<0>(e) << endl;
				continue;
			}
			auto p = make_pair(get<2>(e), get<3>(e));
			for (int i = 2; i < sigma_; i++) {
				auto r = sequence_->StepCount(i, p);
				if (r.first <= r.second) {
					elems t = make_tuple(r.second - r.first + 1, get<1>(e) + 1, r.first, r.second);
					q.push(t);
				}
			}
		}
		for (auto it = res.begin(); it != res.end(); ++it) {
			auto pos = sequence_->Reverse(*it);
			auto t = sequence_->Extract(pos, pos+n);
			result.push_back(t);
		}
	}

	//working OK
	vector<T> FindUsers(vector<T> &path) { 
		pair<size_t,size_t> range = sequence_->InitCountRange(path[0]+1);
		for (uint i = 1 ; i < path.size();i++) 
			range = sequence_->StepCount(path[i]+1, range);
		vector<T> result;
		uint k = 10;
		UserListingStack(range.first, range.second-1, k, result);
		return result;
	}

	void PrintSize() {
		size_t w_size = weights_->getSize();
		size_t m_size = muthu_->getSize();
		size_t s_size = sequence_->Size();
		size_t b_size =  bs_->getSize();
		size_t e_size = sizeof(this);
		size_t total = w_size+m_size+s_size+b_size+e_size;
		cout << "RMQ W:" << w_size  << endl;
		cout << "MUTHU:" << m_size << endl;
		cout << "SSA:" << s_size << endl;
		cout << "Bitmap:" << b_size << endl;
		cout << "EXTRA:" << e_size << endl;
		cout << "TOTAL:" << total << " | " << (total*1.0)/(1024.0*1024.0) << " MB " << endl;
		cout << "Naive:" << (sequence_->Length()-users_)*4 << " | " << ((sequence_->Length()-users_)*4*1.0)/(1024.0*1024.0) << " MB " << endl;
		cout << "RATIO:" << (total*1.0)/((sequence_->Length()-users_)*4.0) << endl;

	}

}; 

