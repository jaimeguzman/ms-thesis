#include <iostream>
#include <map>
#include <fstream>
#include <vector>

#include <libcdsBasics.h>
#include <Array.h>
#include <cppUtils.h>
#include <BitSequence.h>
#include <BitSequenceRG.h>

using namespace std;
using namespace cds_utils;
using namespace cds_static;

using namespace std;
using namespace cds_utils;

void print_pos(Array *prev, Array *news, BitSequence *bs, uint pos) {
	uint ph = bs->rank1(pos);
	uint ph_ini = bs->select1(ph);
	uint ph_fin = bs->select1(ph+1) - 1;
	while (ph_fin != pos) {
		ph = prev->getField(ph-1);
		ph_fin--;
	}
	cout << "T[" << pos << "] = " << (char)news->getField(ph-1) << endl;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "usage: " << argv[0] << " <input>" << endl;
		return 0;
	}
	char *name_input = argv[1];
	

	ifstream in(name_input);
	if (!in.good()) {
		cerr << "Error reading input file" << endl;
		return 1;
	}

	Array *prev = new Array(in);
	Array *news = new Array(in);
	BitSequenceRG *bsrg = BitSequenceRG::load(in);

	in.close();


	uint pos;
	cout << "pos: ";
	while ((cin >> pos)) {
		print_pos(prev, news, bsrg, pos);
		cout << "pos: ";
	}
	
	delete prev;
	delete news;
	delete bsrg;

	return 0;
}
