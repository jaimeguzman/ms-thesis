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

#include "sequence.hpp"

using namespace sequence;

TEST(BWTTest, Bannana) {
	string s = "BANNANA";
	vector<char> seq(s.length());
	copy(s.begin(), s.end(), seq.begin());
	Sequence<char> ms(seq);
	const vector<char> &bwt = ms.GetBWT();
	vector<char> s2 {'A', 'N', 'N', 'B', 0, 'A', 'N', 'A'};
	EXPECT_EQ(bwt, s2);
}

TEST(BWTTest, Banana) {
	string s = "BANANA";
	vector<char> seq(s.length());
	copy(s.begin(), s.end(), seq.begin());
	Sequence<char> ms(seq);
	const vector<char> &bwt = ms.GetBWT();
	vector<char> s2 {'A', 'N', 'N', 'B', 0, 'A', 'A'};
	EXPECT_EQ(bwt, s2);
}

TEST(BWTTest, HolaMundo) {
	string s = "Hola mundo!";
	vector<char> seq(s.length());
	copy(s.begin(), s.end(), seq.begin());
	Sequence<char> ms(seq);
	const vector<char> &bwt = ms.GetBWT();
	vector<char> s2 {'!', 'a', 'o', 0, 'l', 'n', 'o', ' ', 'u', 'd', 'H', 'm'};
	EXPECT_EQ(bwt, s2);
}

TEST(BWTTest, JuicyJuice) {
	string s = "Juicy juice!";
	vector<char> seq(s.length());
	copy(s.begin(), s.end(), seq.begin());
	Sequence<char> ms(seq);
	const vector<char> &bwt = ms.GetBWT();
	vector<char> s2 {'!', 'y', 'e', 0, 'i', 'i', 'c', 'u', 'u', ' ', 'j', 'J', 'c'};
	EXPECT_EQ(bwt, s2);
}

TEST(BWTTest, PRLLPPD) {
	string s = "Esto es un paralelepipedo";
	vector<char> seq(s.length());
	copy(s.begin(), s.end(), seq.begin());
	Sequence<char> ms(seq);
	const vector<char> &bwt = ms.GetBWT();
	vector<char> s2 {'o', 'o', 'n', 's', 0, 'r', 'p', 'e', 'p', 'l', 'l', ' ', 'p', 'a', 'e', 'u', 'd', 't', ' ', 'i', 'e', 'a', 'e', 'E', 's', ' '};
	EXPECT_EQ(bwt, s2);
}
