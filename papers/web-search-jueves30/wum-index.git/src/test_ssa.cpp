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

// Follow the instructions in http://www.thebigblob.com/getting-started-with-google-test-on-ubuntu/
// to get this running in ubuntu.

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cassert>

using namespace std;

#include <gtest/gtest.h>

#include "ssa.hpp"
#include "sequence.hpp"

TEST(SSATest, UPTO10Rebuild) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);
	unsigned int *s2 = a.Rebuild();
	vector<unsigned int> v2;
	copy(s2, s2+10, back_inserter(v2));
	EXPECT_EQ(seq, v2);
	delete [] s2;
}

TEST(SSATest, UPTO10Count) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);

	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(1, cnt);
	}
	for (int i = 1; i < 9; i++) {
		p1[0] = i;
		p1[1] = i + 2;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(0, cnt);
	}
}

TEST(SSATest, UPTO10Extract) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		unsigned int *p = a.Extract(i - 1, i);
		EXPECT_EQ(p[0], p1[0]);
		EXPECT_EQ(p[1], p1[1]);
	}
}


TEST(SSATest, UPTO10Locate) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t *buff;
		size_t cnt = a.Locate(p1, 2, &buff);
		EXPECT_EQ(1, cnt);
		EXPECT_EQ(buff[0], i - 1);
		delete []buff;
	}
}

TEST(SSATest, BORING) {
	int N = 1000;
	vector<unsigned int> seq(N, 1);
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);

	unsigned int *p = new unsigned int[N];
	copy(seq.begin(), seq.end(), p);
	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t rec_cnt = a.Count(p, len);
		EXPECT_EQ(exp_cnt, rec_cnt);
	}

	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t *res;
		size_t res_cnt = a.Locate(p, len, &res);
		sort(res, res + res_cnt);
		EXPECT_EQ(exp_cnt, res_cnt);
		for (int i = 0; i < N - len + 1; i++) {
			EXPECT_EQ(i, res[i]);
		}
		delete [] res;
	}

	unsigned int *rebuild = a.Rebuild();
	vector<unsigned int> v2(rebuild, rebuild+N);
	EXPECT_EQ(seq, v2);
	delete [] rebuild;

}

TEST(SSATest, UPTO10Rebuild2) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);
	unsigned int *s2 = a.Rebuild();
	vector<unsigned int> v2;
	copy(s2, s2+10, back_inserter(v2));
	EXPECT_EQ(seq, v2);
	delete [] s2;
}

TEST(SSATest, UPTO10Count2) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);

	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(1, cnt);
	}
	for (int i = 1; i < 9; i++) {
		p1[0] = i;
		p1[1] = i + 2;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(0, cnt);
	}
}

TEST(SSATest, UPTO10Extract2) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		unsigned int *p = a.Extract(i - 1, i);
		EXPECT_EQ(p[0], p1[0]);
		EXPECT_EQ(p[1], p1[1]);
	}
}


TEST(SSATest, UPTO10Locate2) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t *buff;
		size_t cnt = a.Locate(p1, 2, &buff);
		EXPECT_EQ(1, cnt);
		EXPECT_EQ(buff[0], i - 1);
		delete []buff;
	}
}

TEST(SSATest, UPTO10Reverse2) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);
	
	for (int i = 1; i < 10; i++ ) {
		EXPECT_EQ(i-1, a.Reverse(i));
	}
}

TEST(SSATest, BORING2) {
	int N = 1000;
	vector<unsigned int> seq(N, 1);
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(2);
	a.SetSampleSuff(2);
	a.BuildIndex(seq, bwt, sa);

	unsigned int *p = new unsigned int[N];
	copy(seq.begin(), seq.end(), p);
	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t rec_cnt = a.Count(p, len);
		EXPECT_EQ(exp_cnt, rec_cnt);
	}

	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t *res;
		size_t res_cnt = a.Locate(p, len, &res);
		sort(res, res + res_cnt);
		EXPECT_EQ(exp_cnt, res_cnt);
		for (int i = 0; i < N - len + 1; i++) {
			EXPECT_EQ(i, res[i]);
		}
		delete [] res;
	}

	unsigned int *rebuild = a.Rebuild();
	vector<unsigned int> v2(rebuild, rebuild+N);
	EXPECT_EQ(seq, v2);
	delete [] rebuild;

}


TEST(SSATest, UPTO10Rebuild3) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(1);
	a.SetSampleSuff(1);
	a.BuildIndex(seq, bwt, sa);
	unsigned int *s2 = a.Rebuild();
	vector<unsigned int> v2;
	copy(s2, s2+10, back_inserter(v2));
	EXPECT_EQ(seq, v2);
	delete [] s2;
}

TEST(SSATest, UPTO10Count3) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(1);
	a.SetSampleSuff(1);
	a.BuildIndex(seq, bwt, sa);

	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(1, cnt);
	}
	for (int i = 1; i < 9; i++) {
		p1[0] = i;
		p1[1] = i + 2;
		size_t cnt = a.Count(p1, 2);
		EXPECT_EQ(0, cnt);
	}
}

TEST(SSATest, UPTO10Extract3) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(1);
	a.SetSampleSuff(1);
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		unsigned int *p = a.Extract(i - 1, i);
		EXPECT_EQ(p[0], p1[0]);
		EXPECT_EQ(p[1], p1[1]);
	}
}


TEST(SSATest, UPTO10Locate3) {
	vector<unsigned int> seq {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(1);
	a.SetSampleSuff(1);
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int p1[2];
	for (int i = 1; i < 10; i++) {
		p1[0] = i;
		p1[1] = i + 1;
		size_t *buff;
		size_t cnt = a.Locate(p1, 2, &buff);
		EXPECT_EQ(1, cnt);
		EXPECT_EQ(buff[0], i - 1);
		delete []buff;
	}
}

TEST(SSATest, BORING3) {
	int N = 1000;
	vector<unsigned int> seq(N, 1);
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.SetSamplePos(1);
	a.SetSampleSuff(1);
	a.BuildIndex(seq, bwt, sa);

	unsigned int *p = new unsigned int[N];
	copy(seq.begin(), seq.end(), p);
	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t rec_cnt = a.Count(p, len);
		EXPECT_EQ(exp_cnt, rec_cnt);
	}

	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t *res;
		size_t res_cnt = a.Locate(p, len, &res);
		sort(res, res + res_cnt);
		EXPECT_EQ(exp_cnt, res_cnt);
		for (int i = 0; i < N - len + 1; i++) {
			EXPECT_EQ(i, res[i]);
		}
		delete [] res;
	}

	unsigned int *rebuild = a.Rebuild();
	vector<unsigned int> v2(rebuild, rebuild+N);
	EXPECT_EQ(seq, v2);
	delete [] rebuild;

}

TEST(SSATest, BORING4) {
	int N = 1000;
	vector<unsigned int> seq(N, 1);
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);
	ofstream out("tunito");
	a.Save(out);
	out.close();

	ifstream in("tunito");
	SSA<unsigned int> b(in);
	in.close();

	remove("tunito");

	unsigned int *p = new unsigned int[N];
	copy(seq.begin(), seq.end(), p);
	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t rec_cnt = b.Count(p, len);
		EXPECT_EQ(exp_cnt, rec_cnt);
	}

	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		size_t *res;
		size_t res_cnt = b.Locate(p, len, &res);
		sort(res, res + res_cnt);
		EXPECT_EQ(exp_cnt, res_cnt);
		for (int i = 0; i < N - len + 1; i++) {
			EXPECT_EQ(i, res[i]);
		}
		delete [] res;
	}

	unsigned int *rebuild = b.Rebuild();
	vector<unsigned int> v2(rebuild, rebuild+N);
	EXPECT_EQ(seq, v2);
	delete [] rebuild;

}

TEST(SSATest, BORING5) {
	int N = 1000;
	vector<unsigned int> seq(N, 1);
	sequence::Sequence<unsigned int> ms(seq);
	const vector<unsigned int> &bwt = ms.GetBWT();
	const vector<size_t> &sa = ms.GetSA();
	SSA<unsigned int> a;
	a.BuildIndex(seq, bwt, sa);
	
	unsigned int *p = new unsigned int[N];
	copy(seq.begin(), seq.end(), p);
	for (int len = 1; len < N; len++) {
		size_t exp_cnt = N - len + 1;
		pair<size_t, size_t> p = a.InitCountRange(1);
		for (int i = 1; i < len; i++) {
			p = a.StepCount(1, p);
		}
		size_t rec_cnt = p.second - p.first + 1;
		EXPECT_EQ(exp_cnt, rec_cnt);
	}

	unsigned int *rebuild = a.Rebuild();
	vector<unsigned int> v2(rebuild, rebuild+N);
	EXPECT_EQ(seq, v2);
	delete [] rebuild;

}
