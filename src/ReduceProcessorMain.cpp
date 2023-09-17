#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include "ReduceProcessor.cpp"

#define BUFFER_SIZE 30
#define OUTPUT_SIZE 500

using namespace std;

char* stringToCharStar(string input)
{
    char* char_arr;
    char_arr = &input[0];
    return char_arr;
}

int main(int argc, char const *argv[])
{
    string data = "";
    string all_named_pipes = argv[0];
    stringstream buffer(all_named_pipes);

    string token;
    while(getline(buffer, token, ',')) 
    {
        char* named_buffer_path = stringToCharStar(token);
        int fd = open(named_buffer_path, O_RDONLY);
        char char_array[OUTPUT_SIZE];
        read(fd, char_array, sizeof(char_array));
        data += char_array;
        // cout << char_array << endl;
        close(fd);
    }
    string output = reducing(data);
    char tmp_out[OUTPUT_SIZE];
    strcpy(tmp_out, output.c_str());
    write(atoi(argv[2]), tmp_out, strlen(tmp_out)+1);
    // cout << output << endl;

    return 0;
}
