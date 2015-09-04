#include "ssa.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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

int main(int argc, char ** argv) {
  if(argc!=5) {
    cout << "usage: " << argv[0] << " <text> <index-file> <pattern-file> <pattern-length>" << endl;
    return 0;
  }

  fstream input(argv[1],ios::in | ios::binary);
  if(!input.is_open()) {
    cout << "Error opening file: " << argv[1] << endl;
    return -1;
  }

  input.seekg(0,ios::end);
  uint n=input.tellg();
  uchar * text = new uchar[n+1];

  input.seekg(0,ios::beg);
  input.read((char*)text,sizeof(uchar)*n);
  input.close();
  //for(uint i=0;i<n;i++) text[i]++;
  //text[n] = 0;

  ifstream ssainput(argv[2]);
  ssa * _ssa = new ssa(ssainput);
  ssainput.close();
  _ssa->print_stats();

  uint m;
  {
    stringstream ss;
    ss << argv[4];
    ss >> m;
  }
  
  /*uint rep;
  {
    stringstream ss;
    ss << argv[4];
    ss >> rep;
  }
  */ 

  char *name_input = argv[3];
  uint size = 0;
  uchar *texto = LoadFile(name_input, &size);
  
  
  uint pos = 0;
  uchar * pattern = new uchar[m+1];
 
  while (pos < 1*m) {
	cout << pos << endl;  
    for(uint k=0;k<m;k++)
      pattern[k] = texto[pos+k];
    pattern[m] = 0;
 
    uint occ = _ssa->count(pattern,m);
  
    cout << pattern << ": "<< occ << endl;
    pos+= m+1;
}

  delete [] pattern;
  delete _ssa;
  delete [] text;
  return 0;
}
