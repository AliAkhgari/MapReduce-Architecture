#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

inline string reducing(string data)
{
    map <string, int> word_cnt;
    string file_data;
    stringstream buffer(data);
    while (buffer >> file_data)
    {
        int index = file_data.find(':');
        int size = file_data.length();
        string key = "";
        string value = "";
        for (int i = 0; i < index; i++)
            key += file_data[i];
        for (int i = index+1; i < size; i++)
            value += file_data[i];

        if (word_cnt.find(key) == word_cnt.end()) // not found
                word_cnt.insert({key, atoi(value.c_str())});
        else // found
            word_cnt[key] += atoi(value.c_str());

    }

    string word_cnt_str = "";
    for(const auto& elem : word_cnt)
        word_cnt_str += elem.first + ": " + to_string(elem.second) + "\n";

    return word_cnt_str;
}
