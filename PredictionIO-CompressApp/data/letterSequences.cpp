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

    while(it != mapCategories.end()){

        //cout<<it->first<<" :: "<<it->second<<endl;
        it++;
    }


    cout << "testing ...."<< endl;
    cout << alphabet.at(0) << endl;


	 // ifstream ifs;
	 // ifs.open ("msnbc990928-10entry.seq", ifstream::in);

	 // char c = ifs.get();
	 // while (ifs.good()) {

	 //   int num = atoi(&c) ;
	 //   if(num!=0) cout <<  num << " " ;
	 //   c = ifs.get();
	 // }
	 // ifs.close();


    std::vector<int> myintArray;

    std::string line;
    std::ifstream myfile("msnbc990928-10entry.seq");


   std::ifstream  fin("msnbc990928-10entry.seq");
   std::string    file_line;
   while(std::getline(fin, file_line))
   {
      //current line of text is in file_line, not including the \n 
   	  // cout << file_line << endl;
   	  string buf; // Have a buffer string
	  stringstream ss(file_line); // Insert the string into a stream

	  vector<string> tokens; // Create vector to hold our words

	  while (ss >> buf)
	        tokens.push_back(buf);

	  for (int i = 0; i < tokens.size(); ++i){
	
		string tmp = tokens.at(i); 
		cout << alphabet.at( stoi(tmp)) << " ";

	  }cout<< endl;



   }
    
    // Check if insertion is successful or not
	/*    if(mapCategories.insert(make_pair("news", 1)).second == false){

        cout<<"Element with key 'earth' not inserted because already existed"<<endl;
    }*/

    // Searching element in map by key.
    // if(mapCategories.find("sun") != mapCategories.end())
    //     cout<<"word 'sun' found"<<endl;
    // if(mapCategories.find("mars") == mapCategories.end())
    //     cout<<"word 'mars' not found"<<endl;




    return 0;
}
                