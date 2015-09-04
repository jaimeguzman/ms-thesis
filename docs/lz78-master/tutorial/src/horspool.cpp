#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cerrno>
#include <time.h>

#include <stdio.h>  
#include <string.h>  
#include <limits.h>  


using namespace std;

 
typedef std::vector<size_t> occtable_type;

/* This function creates an occ table to be used by the search algorithms. */
/* It only needs to be created once per a needle to search. */
const occtable_type
    CreateOccTable(const unsigned char* needle, size_t needle_length)
{
    occtable_type occ(UCHAR_MAX+1, needle_length); // initialize a table of UCHAR_MAX+1 elements to value needle_length
 
    /* Populate it with the analysis of the needle */
    /* But ignoring the last letter */
    if(needle_length >= 1)
    {
        const size_t needle_length_minus_1 = needle_length-1;
        for(size_t a=0; a<needle_length_minus_1; ++a)
            occ[needle[a]] = needle_length_minus_1 - a;
    }
    return occ;
}

/* A Boyer-Moore-Horspool search algorithm. */
/* If it finds the needle, it returns an offset to haystack from which
* the needle was found. Otherwise, it returns haystack_length.
*/
size_t SearchInHorspool(const unsigned char* haystack, size_t haystack_length,
    const occtable_type& occ,
    const unsigned char* needle,
    const size_t needle_length)
{
    if(needle_length > haystack_length) return haystack_length;
    if(needle_length == 1)
    {
        const unsigned char* result = (const unsigned char*)std::memchr(haystack, *needle, haystack_length);
        return result ? size_t(result-haystack) : haystack_length;
    }
 
    const size_t needle_length_minus_1 = needle_length-1;
 
    const unsigned char last_needle_char = needle[needle_length_minus_1];
 
    size_t haystack_position=0;
    int contador = 0;
    while(haystack_position <= haystack_length-needle_length)
    {
        const unsigned char occ_char = haystack[haystack_position + needle_length_minus_1];
 
        // The author modified this part. Original algorithm matches needle right-to-left.
        // This code calls memcmp() (usually matches left-to-right) after matching the last
        // character, thereby incorporating some ideas from
        // "Tuning the Boyer-Moore-Horspool String Searching Algorithm"
        // by Timo Raita, 1992.
        if(last_needle_char == occ_char
        && std::memcmp(needle, haystack+haystack_position, needle_length_minus_1) == 0)
        {
            contador++;
        }
 
        haystack_position += occ[occ_char];
    }
    return contador;
}

string get_file_contents(const char *filename)
{
  ifstream in(filename, ios::in | ios::binary);
  if (in)
  {
    return(string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>()));
  }
  throw(errno);
}

int main(int argc, char **argv) {

	if (argc != 3) {
		cout << "uso: " << argv[0] << " <texto> <archivo_patrones>" << endl;
		return 0;
	}
	
	time_t start, end;
	int pos = 0, m = 0;
	double total_time;
	string texto, line, pattern;
	texto = get_file_contents(argv[1]);
	ifstream file;
	
	
/*******con un solo patron*****/
/*
	pattern = argv[2];
			
	const occtable_type occ = CreateOccTable((const unsigned char *) pattern.c_str(),pattern.size());
	cout << pattern << " se encuentra " << SearchInHorspool((const unsigned char *) texto.c_str(), texto.size(),occ,(const unsigned char *) pattern.c_str(), pattern.size()) << " veces" << endl;
	pattern.clear();
*/


/********con archivo de patrones*******/
	file.open(argv[2]);
	if (file.is_open()) {
		while (getline(file,line)) {
			pattern = line;
			if (pattern == "")
				pattern = "page";
			clock_t begin = clock();
			const occtable_type occ = CreateOccTable((const unsigned char *) pattern.c_str(),pattern.size());
			cout << pattern << " se encuentra " << SearchInHorspool((const unsigned char *) texto.c_str(), texto.size(),occ,(const unsigned char *) pattern.c_str(), pattern.size()) << " veces" << endl;
			//SearchInHorspool((const unsigned char *) texto.c_str(), texto.size(),occ,(const unsigned char *) pattern.c_str(), pattern.size());
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			total_time += elapsed_secs;
			pattern.clear();
		}
	}
	cout << "Tiempo promedio: " << (total_time/5000) << endl;
	file.close();
	return 0;	
}
	
