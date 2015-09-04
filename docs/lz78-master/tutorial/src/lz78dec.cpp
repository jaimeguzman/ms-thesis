#include <iostream>
#include <map>
#include <fstream>
#include <vector>

#include <libcdsBasics.h>
#include <Array.h>
#include <cppUtils.h>

using namespace std;
using namespace cds_utils;


void generate(ofstream &out, Array *prev, Array *news, uint pos) {
	if (pos == 0) {
		return;
	}
	pos--;
	generate(out, prev, news, prev->getField(pos));
	unsigned char v = (unsigned char)news->getField(pos);
	out.write((char *)&v,sizeof(unsigned char));
}

uchar * decompress(ofstream &out, Array *prev, Array *news) {
	for (uint i = 0; i < prev->getLength(); i++) {
		generate(out, prev, news, prev->getField(i));
		unsigned char v = (unsigned char)news->getField(i);
		out.write((char *)&v,sizeof(unsigned char));
	}
	return NULL;
}

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <input> <output>" << endl;
		return 0;
	}
	char *name_input = argv[1];
	char *name_output = argv[2];

	ifstream in(name_input);
	if (!in.good()) {
		cerr << "Error reading input file" << endl;
		return 1;
	}

	Array *prev = new Array(in);
	Array *news = new Array(in);

	in.close();

	ofstream out(name_output);
	if (!out.good()) {
		cerr << "Error opening output file" << endl;
		return 2;
	}

	decompress(out, prev, news);
	out.close();

	return 0;
}
