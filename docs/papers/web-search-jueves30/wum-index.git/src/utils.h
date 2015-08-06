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

#pragma once

#include <vector>
#include <string>
#include <sys/time.h>
#include <sys/resource.h>
#include <fstream>
#include <iostream>
using namespace std;

void Tokenize(const string& str, vector<string>& tokens,const string& delimiters = " ") {
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

vector<vector<uint> > loadFile(ifstream &f) {
    if(!f.good()) 
        __throw_ios_failure("File not good");
    string line;
    vector<vector<uint> > data;
    while(f.good()) {
        getline(f,line);
        vector<string> tokens;
        Tokenize(line, tokens," \n\t");
        vector<uint> aux;
        data.push_back(aux);
	if (tokens.size() == 0)
		continue;
        for (uint i = 0 ; i < tokens.size()-1;i++) {
//            cout << tokens[i].c_str() << endl;
	     int n = atol(tokens[i].c_str());
            // cout << n << endl;
            if (n >= 0)
                data[data.size()-1].push_back(n);
        }
    }    
    return data;
}
vector<vector<uint > > genSequences(vector<vector<uint> > &data, int n) {
    if (n == 0)
        n = 1;
    vector<vector<uint> > result;
    for (uint i = 0 ; i < data.size();i++) {
        if (data[i].size() >= (uint)n) {
            vector<uint> aux;
            result.push_back(aux);
  
            uint begin_pos = 0;
            uint end_pos;
            if (data[i].size()-n ==  0) {
                end_pos = data[i].size();
            } else {
                begin_pos = rand()%(data[i].size()-n);
                end_pos = begin_pos + n;
            }
            // cout << "begin = " << begin_pos << endl;
            // cout << "end = " << end_pos << endl;
            for (uint j = begin_pos;j<end_pos;j++) {
                result[result.size()-1].push_back(data[i][j]);
            }
        }
    }
    return result;
}

class Timer {
  public:
    /** Creates and starts the timer.
     */
    Timer() {
      Restart();
    }

    /** Restarts the timer.
     */
    void Restart() {
      getrusage(RUSAGE_SELF, &ru);
      initial_ru = ru.ru_utime;
      gettimeofday(&initial, NULL);
    }

    /** Stops the timer.
     */
    void Stop() {
      getrusage(RUSAGE_SELF, &ru);
      final_ru = ru.ru_utime;
      gettimeofday(&final, NULL);
    }

    // * Computes the number of microsecond elapsed from start to stop
    //  * This time is for wall-clock time
     
    double ElapsedTime() {
      return (final.tv_sec - initial.tv_sec) * 1000000 + (final.tv_usec - initial.tv_usec);
    }

    /** Computes the number of microsecond elapsed from start to stop
    * This time is for  process CPU usage
    */
    double ElapsedTimeCPU() {
      return (final_ru.tv_sec - initial_ru.tv_sec) * 1000000 + (final_ru.tv_usec - initial_ru.tv_usec);
    }

  protected:
    struct timeval initial, final;
    struct timeval initial_ru, final_ru;
    struct rusage ru;
};

