#include <iostream>     // cout
#include <fstream>      // ifstream
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

/** 
  alias lseq = g++ -std=c++11 letterSequences.cpp -o letterSequences 
  ./letterSequences

% Different categories found in input file:

frontpage news tech local opinion on-air misc weather msn-news health living business msn-sports sports summary bbs travel

@TODO:
 	le quite las primeras lineas al input para concentrarme
 	en los datos 

**/

 
int main()
{
   map<string, int> mapCategories;
    // Inserting data in map
	
	mapCategories.insert(make_pair("frontpage", 1));
    mapCategories.insert(make_pair("news", 		2));
    mapCategories.insert(make_pair("tech", 		3));
    mapCategories.insert(make_pair("local", 	4));
    mapCategories.insert(make_pair("opinion", 	5));
    mapCategories.insert(make_pair("on-air", 	6));
    mapCategories.insert(make_pair("misc", 		7));
    mapCategories.insert(make_pair("weather", 	8));
    mapCategories.insert(make_pair("msn-news", 	9));
    mapCategories.insert(make_pair("health", 	10));
    mapCategories.insert(make_pair("living", 	11));
    mapCategories.insert(make_pair("business", 	12));
    mapCategories.insert(make_pair("msn-sports",13));
    mapCategories.insert(make_pair("sports", 	14));
    mapCategories.insert(make_pair("summary", 	15));
    mapCategories.insert(make_pair("bbs", 		16));
    mapCategories.insert(make_pair("travel", 	17));
    

   vector<char> alphabet = { 'A','B','C','D','E','F','G',
							  'H','I','J','K','L','M','N','O',
							  'P','Q','R','S','T','U','V','W',
							  'X','Y','Z'};

   // Iterate through all elements in map
   map<string, int>::iterator it = mapCategories.begin();

   ifstream  fin("msnbc990928.seq");
   string    file_line;

   int fold = 0 ;

   while(getline(fin, file_line))
   {

   	  string 		buf; // Have a buffer string
	  stringstream 	ss(file_line); // Insert the string into a stream
	  vector<string> tokens; // Create vector to hold our words
	  
	  while (ss >> buf) tokens.push_back(buf);


	  if( tokens.size() < 6 ){
	  		  ++fold;

		  for (int i = 0; i < tokens.size(); ++i){
			string tmp = tokens.at(i); 
			cout << alphabet.at( stoi(tmp) - 1) << " ";
		  }cout<< endl;

	  }




	  if( fold == 1000000 ) break;

   }
    return 0;
}
                