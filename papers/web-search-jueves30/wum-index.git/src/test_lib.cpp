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

#include <vector>
#include <iostream>
#include <Array.h>
using namespace cds_utils;

#include <rmq.h>
using namespace std;
using namespace rmq_space;

int main() {
	vector<uint> t;
	int *x = new int[1000];
	for (uint i = 0 ; i < 1000;i++) {
		t.push_back(rand()%1000);
		x[i] = rand()%1000;
	}
	Array *r = new Array(t);
	RMQ *rmq = new RMQ(x,1000);
	cout << "array size =" << r->getSize();
	cout << "rmq size = " << rmq->getSize();
}
