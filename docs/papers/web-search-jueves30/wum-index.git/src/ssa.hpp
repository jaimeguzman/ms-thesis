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
#include <fstream>
#include <vector>

using namespace std;

#include <Array.h>
#include <cppUtils.h>
#include <BitSequence.h>
#include <Sequence.h>

using namespace cds_utils;
using namespace cds_static;

template <typename T> class SSA {
public:
  SSA() {
    sbb_ = new BitSequenceBuilderRRR(32);
    sbb_->use();
    
    // Default sampling values
    samplepos_ = 64;
    samplesuff_ = 64;

    // Random shit, boring...
    sampled_ = NULL;
    pos_sample_ = NULL;
    suff_sample_ = NULL;
    bwt_ = NULL;
  }


  ~SSA() {
    if (bwt_ != NULL)
      delete bwt_;
    if (sbb_ != NULL)
      sbb_->unuse();
    if (pos_sample_ != NULL)
      delete [] pos_sample_;
    if (suff_sample_ != NULL)
      delete [] suff_sample_;
    if (sampled_ != NULL)
      delete sampled_;
  }

  SSA(ifstream &fp) {
    n_ = loadValue<size_t>(fp);
    sigma_ = loadValue<size_t>(fp);
    samplepos_ = loadValue<size_t>(fp);
    samplesuff_ = loadValue<size_t>(fp);
    bwt_ = WaveletTreeNoptrs::load(fp);
    sampled_ = BitSequence::load(fp);
    pos_sample_ = loadValue<uint>(fp, 2 + n_ / samplepos_);
    suff_sample_ = loadValue<uint>(fp, 1 + n_ / samplesuff_);
    sbb_ = NULL;
  }

  void Save(ofstream & fp) {
    saveValue(fp, n_);
    saveValue(fp, sigma_);
    saveValue(fp, samplepos_);
    saveValue(fp, samplesuff_);
    bwt_->save(fp);
    sampled_->save(fp);
    saveValue(fp, pos_sample_, 2 + n_ / samplepos_);
    saveValue(fp, suff_sample_, 1 + n_ / samplesuff_);
  }


  size_t Length() {
    return n_;
  }


  size_t Size() {
    size_t size = bwt_->getSize();
    size += sizeof(uint)*(2+n_/samplepos_);
    size += sizeof(uint)*(1+n_/samplesuff_);
    size += sizeof(SSA);
    return size;
  }

  void SetBitSequenceBuilder(BitSequenceBuilder *bb) {
    if (sbb_) {
      sbb_->unuse();
    }
    sbb_ = bb;
    sbb_->use();
  }

  void SetSamplePos(size_t sample) {
    samplepos_ = sample;
  }

  void SetSampleSuff(size_t sample) {
    samplesuff_ = sample;
  }

  void BuildIndex(const vector<T> &sequence, const vector<T> &bwt, const vector<size_t> &sa) {
    vector<uint> v;
    v.reserve(bwt.size());
    copy(bwt.begin(), bwt.end(), back_inserter(v));
    Array a(v);
    sigma_ = a.getMax() + 1;
    bwt_ = new WaveletTreeNoptrs(a, sbb_, new MapperNone());
    for (size_t i = 0; i < bwt.size(); i++) {
      if (bwt[i] != bwt_->access(i)) 
        cout << "Error for position " << i << endl;
    }
    n_ = a.getLength() - 1;

    uint j = 0;
    uint * sampled_vector = new uint[uint_len(n_ + 2, 1)];
    pos_sample_ = new uint[(n_ + 1) / samplepos_ + 2];
    suff_sample_ = new uint[(n_ + 1) / samplesuff_ + 1];
    for(uint i = 0; i < uint_len(n_ + 1, 1); i++) sampled_vector[i] = 0;
    for(uint i = 0; i < n_ + 1; i++) {
      if (sa[i] % samplesuff_ == 0) {
        suff_sample_[j++] = sa[i];
        bitset(sampled_vector, i);
      }
      if (sa[i] % samplepos_ == 0) {
        pos_sample_[sa[i] / samplepos_] = i;
      }
    }
    pos_sample_[n_ / samplepos_ + 1] = pos_sample_[0];
    bitset(sampled_vector, n_ + 1);
    sampled_ = sbb_->build(sampled_vector, n_ + 1);
    delete [] sampled_vector;
  }


  size_t Locate(T *pattern, size_t m, size_t ** occs) {
    uint c = static_cast<uint>(pattern[m-1]); 
    size_t i = m - 1;
    size_t sp = bwt_->occ(c);
    c++;
    size_t ep = bwt_->occ(c) - 1;
    c--;
    while (sp <= ep && i >= 1) {
      c = static_cast<uint>(pattern[--i]);
      sp = bwt_->occ(c) + bwt_->rank(c, sp - 1);
      ep = bwt_->occ(c) + bwt_->rank(c, ep) - 1;
    }
    if (sp<=ep) {
      size_t matches = ep - sp + 1;
      *occs = new size_t[matches];
      size_t i = sp;
      size_t j,dist,rank_tmp;
      while (i <= ep) {
        j = i;
        dist = 0;
        while (!sampled_->access(j)) {
          c = bwt_->access(j, rank_tmp);
          j = bwt_->occ(c) + rank_tmp - 1;
          dist++;
        }
        (*occs)[i - sp] = suff_sample_[sampled_->rank1(j) - 1] + dist;
        i++;
      }
      return ep - sp + 1;
    }
    else {
      *occs = NULL;
      return 0;
    }
  }

  size_t Reverse(size_t pos) {
    size_t j,dist,rank_tmp;
    j = pos;
    dist = 0;
    while (!sampled_->access(j)) {
      uint c = bwt_->access(j, rank_tmp);
      j = bwt_->occ(c) + rank_tmp - 1;
      dist++;
    }
    return suff_sample_[sampled_->rank1(j) - 1] + dist;
  }

  size_t Count(T *pattern, size_t m) {
    uint c = static_cast<uint>(pattern[m-1]); 
    size_t i=m-1;
    size_t sp = bwt_->occ(c);
    c++;
    size_t ep = bwt_->occ(c) - 1;
    c--;
    while (sp<=ep && i>=1) {
      c = static_cast<uint>(pattern[--i]);
      size_t o = bwt_->occ(c);
      sp = o + bwt_->rank(c, sp - 1);
      ep = o + bwt_->rank(c, ep) - 1;
    }
    if(sp<=ep) {
      return ep-sp+1;
    } else {
      return 0;
    }
  }

  pair<size_t, size_t> InitCountRange(T symbol) {
    uint c = static_cast<uint>(symbol);
    size_t sp = bwt_->occ(symbol);
    c++;
    size_t ep = bwt_->occ(c) - 1;
    return make_pair(sp, ep);
  }

  pair<size_t, size_t> StepCount(T symbol, pair<size_t, size_t> &range) {
    uint c = static_cast<uint>(symbol);
    size_t o = bwt_->occ(c);
    size_t sp = o + bwt_->rank(c, range.first - 1);
    size_t ep = o + bwt_->rank(c, range.second) - 1;
    return make_pair(sp, ep);
  }

  T *Rebuild() {
    T *text = new T[n_];
    size_t p = pos_sample_[0];
    uint c =  bwt_->access(p);
    p =  bwt_->occ(c)  + bwt_->rank(c,p) - 1;
    for (int i = n_- 1; i >= 0; i--) {
      size_t tmp_rank;
      c = bwt_->access(p,tmp_rank);
      p = bwt_->occ(c) + tmp_rank - 1;
      text[i] = static_cast<T>(c);
    }
    return text;
  }

  void TopK(size_t ini, size_t fin, int k, vector<T> &result) {
    bwt_->TopK(ini, fin, k, result);
  }


  T *Extract(uint i, uint j) {
    size_t len = j - i + 1;
    T *snippet = new T[len];
    uint c;
    size_t skip, rank_tmp;
    size_t p = 0;
    if ((j / samplepos_ + 1) == (n_ / samplepos_ + 1)) {
      p = pos_sample_[0];
      skip = n_ - j;
    } else {
      p = pos_sample_[j / samplepos_ + 1];
      skip = samplepos_ - j % samplepos_ - 1;
    }
    for (uint dist = 0; dist < skip + len; dist++) {
      c = bwt_->access(p, rank_tmp);
      p = bwt_->occ(c) + rank_tmp - 1;
      if (dist >= skip)
        snippet[len - dist - 1 + skip] = static_cast<T>(c);
    }
    return snippet;
  }

  uint AccessSequence(uint pos) {
    return bwt_->access(pos);
  }

  uint GetSigma() {
    return sigma_;
  }

protected:
  WaveletTreeNoptrs *bwt_;
  uint *pos_sample_;
  uint *suff_sample_;
  size_t samplepos_;
  size_t samplesuff_;
  BitSequence *sampled_;
  size_t n_, sigma_;

  BitSequenceBuilder *sbb_;

};
