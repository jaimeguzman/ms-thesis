#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cerrno>
#include <streambuf>

using namespace std;

string get_file_contents(const char *filename)
{
  ifstream in(filename, ios::in | ios::binary);
  if (in)
  {
    return(string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()));
  }
  throw(errno);
}



int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "Uso: " << argv[0] << " <Texto> <Patron>" << endl;
		return -1;
	}
	string line,texto, patron, aux, pat;
	patron = argv[2];
	/*ifstream file;
	file.open(argv[1]);
	if (file.is_open()) {
		while (getline(file,line)) {
			texto += line;
		}
	}
	else {
		cout << "Error al abrir el archivo" << endl;
		return -1;
	}
	file.close();
	*/
	texto = get_file_contents(argv[1]);
	int p = patron.size(), cont = 0, iy = 0, c = 0; // p = largo del patron | iy = posicion del patron revisando
	for (int ix = 0; ix < texto.size(); ix++) {
		if (ix + p > texto.size()) {
			break;
		}
		aux = texto.at(ix);
		pat = patron.at(iy);
		if (aux.compare(pat) == 0) {
			for (c = 1; c < p; c++) {
				aux = texto.at(ix+c);
				pat = patron.at(iy+c);
				if (aux.compare(pat) != 0) {
					iy = 0;
					break;
				}
			}
			if (c == p) {
			cont += 1;
			}
		}
	}
	cout << patron << " se encuentra " << cont << " veces en el texto\n";
	return 0;
}
