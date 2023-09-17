#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

inline string mapping(string path)
{
    map <string, int> word_cnt;

    string file_data;
    ifstream infile(path);
    infile >> file_data;
    stringstream buffer(file_data);
    infile.close();

    string token;
    while(getline(buffer, token, ',')) 
    {
        if (token.length() != 0)
        {
            if ( word_cnt.find(token) == word_cnt.end() ) // not found
                word_cnt.insert({token, 1});
            else // found
                word_cnt[token] += 1;
        }
    }

    string word_cnt_str = "";
    for(const auto& elem : word_cnt)
        word_cnt_str += elem.first + ':' + to_string(elem.second) + "\n";

    return word_cnt_str;
}
