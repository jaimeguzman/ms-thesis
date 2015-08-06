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

#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::copy;
using std::sort;

namespace {
	// This class is only used by the Sequence class
	template <typename T> class cmp_sa {
	public:
		cmp_sa(vector<T> & seq) {
			seq_ = &seq;
		}

		~cmp_sa() {}

		bool operator()(size_t i, size_t j) {
			while (i!=seq_->size() && j!=seq_->size()) {
				if (seq_->at(i) != seq_->at(j)) {
					return seq_->at(i) < seq_->at(j);
				}
				i++; j++;
			}
			if (i == seq_->size()) return true;
			return false;
		}

	protected:
		vector<T> *seq_;
	};
}

namespace sequence {
	// Sequence class allows to build suffix arrays (and their inverse) and BWTs for
	// a sequence of any type. The class receives initially a vector que the sequence
	// and allows to retrieve a read-only copy of the SA, the iSA, the BWT, and the
	// BWTPerm, which corresponds to the permutation describing the BWT.
	// The class creates a copy of the input sequence, and all the space required
	// by the structures is only freed once the object dies.
	// There is no particular order in which constructions should happen. Actually,
	// calling the required getters is enough to get the depending structures built.
	// IMPORTANT: The code assumes the lowest value in the sequence is 1, and uses 0
	// to mark the last position in the sequence.
	template <typename T> class Sequence {
		public:
			Sequence(vector<T> &seq) {
				seq_.reserve(seq.size()+1);
				copy(seq.begin(), seq.end(), back_inserter(seq_));
				sa_built_ = bwt_built_ = isa_built_ = false;
				len_ = seq.size();
			}

			~Sequence() {}

			void BuildSA() {
				for (size_t i = 0; i < len_ + 1; i++) {
					sa_.push_back(i);
				}
				sort(sa_.begin(), sa_.end(), ::cmp_sa<T>(seq_));
				sa_built_ = true;
			}

			void BuildISA() {
				if (!sa_built_) BuildSA();
				isa_.reserve(len_ + 1);
				for (size_t i = 0; i < len_ + 1; i++) {
					isa_[sa_[i]] = i;
				}
				isa_built_ = true;
			}

			void BuildBWT() {
				if (!sa_built_) BuildSA();
				bwt_.reserve(len_ + 1);
				bwt_perm_.reserve(len_ + 1);
				for (auto p : sa_) {
					if (p == 0) {
						bwt_.push_back(static_cast<T>(0));
						bwt_perm_.push_back(len_);
					} else {
						bwt_.push_back(seq_[p - 1]);
						bwt_perm_.push_back(p - 1);
					}
				}
				bwt_built_ = true;
			}

			const vector<size_t> &GetBWTPerm() {
				if (!bwt_built_) BuildBWT();
				return bwt_perm_;
			}

			const vector<size_t> &GetSA() {
				if (!sa_built_) BuildSA();
				return sa_;
			}

			const vector<size_t> &GetISA() {
				if (!isa_built_) BuildISA();
				return isa_;
			}

			const vector<T> &GetSequence() {
				return seq_;
			}

			const vector<T> &GetBWT() {
				if (!bwt_built_) BuildBWT();
				return bwt_;
			}

		protected:	
			vector<T> seq_;
			vector<T> bwt_;
			size_t len_;

			vector<size_t> sa_;
			vector<size_t> isa_;
			vector<size_t> bwt_perm_;

			bool sa_built_, isa_built_, bwt_built_;
	};
};
