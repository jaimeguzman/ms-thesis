#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string.h>

#include <libcdsBasics.h>
#include <Array.h>
#include <cppUtils.h>
#include <BitSequence.h>
#include <BitSequenceRG.h>

using namespace std;
using namespace cds_utils;
using namespace cds_static;

/*        Revisa si check esta en conj                   */
bool is_in(vector<int> conj,int check) {
	for (int ix = 0; ix < conj.size(); ix++) {
		if (check == conj[ix])
			return true;
	}
	return false;
}

/*             Devuelve la ultima letra del string    */
char last_letter(string x) {
	char lastChar = x.at( x.length() - 1 );
	return lastChar;
}

int max_ele(vector<int> conj) {
	int aux = 0;
	for (int ix = 0; ix < conj.size(); ix++) {
		if (conj[ix] > aux) { aux = conj[ix]; }
		return aux;
	}
}
	

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <index> <patron>" << endl;
		return 0;
	}
	
	char patron[16];
	int lenp, aux, aux2;
	uint occ = 0;
	string tmp;
	
	tmp = "";
	strcpy(patron,argv[2]);
	lenp = strlen(patron);
	
	vector<string> prefijos;
	vector< vector<int> > conjuntos(lenp);
	
	for (aux = 0; aux < lenp; aux++) { //se agregan los prefijos al vector
		aux2 = 0;
		while (aux2 <= aux) {
			tmp += patron[aux2];
			aux2++;
		}
		prefijos.push_back(tmp);
		tmp = "";
	}
	/*
	for(int c=0; c < prefijos.size() ; c++){
      cout << prefijos[c] << endl;
	}
	*/
	/*
	conjuntos[0].push_back(2);
	for(int c = 0 ; c < conjuntos[0].size() ; c++){
      cout << conjuntos[0][c] << endl;
	}
	*/
	ifstream in(argv[1]);
	Array *prev = new Array(in);
	Array *news = new Array(in);
	string last;
	
	for (uint i = 0; i < prev->getLength(); i++) {
		//cout << i+1 << " (" << prev->getField(i) << "," << (unsigned char)news->getField(i)<<")" << endl;
		for (int iy = 0; iy < prefijos.size(); iy++) {
			last = last_letter(prefijos[iy]);
			if (iy == 0 && (unsigned char)news->getField(i) == prefijos[0][0]) {					
					conjuntos[iy].push_back(i+1);
					//break;
			}
			else if ((unsigned char)news->getField(i) == last_letter(prefijos[iy]) && is_in(conjuntos[iy-1],prev->getField(i))) { // si la letra del par es igual a la ultima letra del prefijo, y el par referencia al par anterior, se agrega al conjunto
					conjuntos[iy].push_back(i+1);
			}	
		}	
	}

	//Que hay en los conjuntos
	/*
	for (int aux = 0; aux < conjuntos.size(); aux++) {
		cout << "conjunto n: " << aux << endl;
		for (int asd = 0; asd < conjuntos[aux].size(); asd++)
			cout << conjuntos[aux][asd] << endl;
	}*/
	
	int fin = conjuntos.size();
	occ = conjuntos[fin-1].size();
	cout << max_ele(conjuntos[fin-1]);
	for (uint i = max_ele(conjuntos[fin-1]); i < prev->getLength(); i++) {
		if (is_in(conjuntos[fin-1],prev->getField(i))) {//si referencia a algun par que contiene al patron se suma una ocurrencia
			occ++;
		}
	}
	cout << patron << " se encuentra " << occ << " veces\n";
		
	return 0;	
}
