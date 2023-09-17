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
#include "MapProcessor.cpp"

#define BUFFER_SIZE 30

using namespace std;

char* stringToCharStar(string input)
{
    char* char_arr;
    char_arr = &input[0];
    return char_arr;
}

int main(int argc, char const *argv[])
{
    char read_msg[BUFFER_SIZE];
    string word_count;
    if (read(atoi(argv[0]), read_msg, BUFFER_SIZE + 1) > 0)
    {
        string str = read_msg;
        word_count = mapping(str);
    }

    char* word_count_char = stringToCharStar(word_count);
    int fd = open(argv[1], O_WRONLY);
    write(fd, word_count_char, strlen(word_count_char) + 1);
    close(fd);

    return 0;
}
