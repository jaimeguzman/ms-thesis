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

uchar *LoadFile(const char *name, uint *content_length) {
  ifstream in(name);
  if (!in.good()) {
    return NULL;
  }

  in.seekg(0, ios_base::end);
  size_t length = in.tellg();
  in.seekg(0, ios_base::beg);

  *content_length = length;
  uchar *ret = loadValue<uchar>(in, *content_length);
  in.close();
  return ret;
}

class TrieNode {
public:
	TrieNode(uint id, uint parent, uchar c) {
		id_ = id;
		parent_ = parent;
		c_ = c;
	}

	~TrieNode() {
		for (map<uchar,TrieNode*>::iterator it = children_.begin(); it != children_.end(); ++it) {
			delete it->second;
		}
	}

	void Insert(TrieNode *ch, uchar c) {
		children_[c] = ch;
	}

	uint GetId() {
		return id_;
	}

	TrieNode* GetChild(uchar ch) {
		return children_[ch];
	}

	bool HasPath(uchar ch) {
		return children_.count(ch) > 0;
	}

protected:
	uint id_, parent_;
	uchar c_;
	map<uchar, TrieNode*> children_;
};

void generate(vector<uint> prev, vector<uint> news, uint pos) {
	if (pos == 0) {
		return;
	}
	pos--;
	generate(prev, news, prev[pos]);
	cout << (uchar)news[pos];
}

uchar * decompress(vector<uint> prev, vector<uint> news, uint *len) {
	for (uint i = 0; i < prev.size(); i++) {
		generate(prev, news, prev[i]);
		cout << (uchar)news[i];
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
	uint size = 0;
	uchar *content = LoadFile(name_input, &size);
	// for (int i = 0; i < size; i++) 
	// 	cout << content[i];
	cout << endl;
	cout << "Content length: " << size << endl;
	uint * bs = new uint[uint_len(size+1,1)];
	for (uint i = 0; i < uint_len(size+1,1); i++)
		bs[i] = 0;

	TrieNode *root = new TrieNode(0, 0, 0);

	vector<uint> previous_phrase;
	vector<uint> new_symbol;
	uint pos = 0; uint id = 1;
	while (pos < size) {
		bitset(bs, pos);
		TrieNode *actual = root;
		// cout << "ID: " << id << "  --  ";
		while (pos < size - 1 && actual->HasPath(content[pos])) {
			// cout << content[pos];
			actual = actual->GetChild(content[pos]);
			pos++;
		}
		// cout << content[pos] << endl;
		actual->Insert(new TrieNode(id, actual->GetId(), content[pos]), 
						content[pos]);
		// cout << "(" << id << "," << actual->GetId() << ", " 
		// 			<< content[pos] << ")" << endl;
		previous_phrase.push_back(actual->GetId());
		new_symbol.push_back(content[pos]);
		id++; pos++;
	}
	bitset(bs, size);
	delete root;

	// for(uint i = 0; i < previous_phrase.size(); i++) {
	// 	cout << "(" << previous_phrase[i] << "," 
	// 				<< new_symbol[i] << ")" << endl;
	// }

	// decompress(previous_phrase, new_symbol, NULL);

	Array *a1 = new Array(previous_phrase);
	Array *a2 = new Array(new_symbol);
	BitSequenceRG *bs_rg = new BitSequenceRG(bs, size+1, 20);
	delete []bs;

	ofstream out(name_output);
	if(!out.good()) {
		cerr << "No se puede guardar" << endl;
		return 1;
	}

	a1->save(out);
	a2->save(out);
	bs_rg->save(out);

	out.close();

	delete a1;
	delete a2;
	delete bs_rg;
	return 0;
}
