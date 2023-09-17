#include <string>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream> 

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 30
#define OUTPUT_SIZE 500
#define DATA_PATH "../testcases"

namespace fs = std::filesystem;
using namespace std;

vector <string> namedPipesNames(vector <string> file_names)
{
    vector <string> named_pipes_names;
    for(int  i = 0; i < file_names.size(); i++)
    {
        string file_name = file_names[i];
        file_name.erase(0, 13);
        file_name.erase(1, 4);
        file_name = "../tmp/FIFO_" + file_name ;
        named_pipes_names.push_back(file_name);
    }
    return named_pipes_names;
}

void createNamedPipes(vector <string> named_pipes_names)
{
    for (int i = 0; i < named_pipes_names.size(); i++)
    {
        char tmp[BUFFER_SIZE];
        strcpy(tmp, named_pipes_names[i].c_str());
        mkfifo(tmp, 0666);        
    }
}

vector <string> fileNames()
{
    vector <string> file_names;
    
    for (const auto & entry : fs::directory_iterator(DATA_PATH))
    {
        file_names.push_back(entry.path());
    }
    return file_names;
}

char* stringToCharStar(string input)
{
    char* char_arr;
    char_arr = &input[0];
    return char_arr;
}

string concatNamedPipesNames(vector <string> named_pipes_names)
{
    string all_named_pipes = "";
    for (int i = 0; i < named_pipes_names.size(); i++)
    {
        all_named_pipes += named_pipes_names[i];
        all_named_pipes += ',';
    }
    return all_named_pipes;
}

int main(int argc, char const *argv[])
{
    
    vector <string> file_names = fileNames();
    int files_number = file_names.size();
    vector <string> named_pipes_names = namedPipesNames(file_names);
    createNamedPipes(named_pipes_names);

    for (int i = 0; i < files_number; i++)
    {
        char* file_name = stringToCharStar(file_names[i]);
        int fd[2];
        pid_t pid;

        if (pipe(fd) == -1)
            cout << "Pipe failed" << endl;

        pid = fork();
        if (pid < 0)
            cout << "Fork failed" << endl;
        if (pid > 0) // Parent Process
        {
            close(fd[READ_END]);
            if (write(fd[WRITE_END], file_name, strlen(file_name)+1) < 0)
                cout << "Failed to write file name in map pipe!" << endl;
            close(fd[WRITE_END]);
        }
        else // Child Process
        {
            close(fd[WRITE_END]);
            char* pipe_read_end = stringToCharStar(to_string(fd[READ_END]));
            char* named_pipe_path = stringToCharStar(named_pipes_names[i]);
            char *argv[3] = {pipe_read_end, named_pipe_path, NULL};
            if (execv("./MapProcessorMain.out", argv) < 0)
                cout << "Failed to run file MapProcessorMain!" << endl;
            close(fd[READ_END]);
        }
    }

    int fd[2];
    pid_t pid;
    if (pipe(fd) == -1)
        cout << "Pipe failed" << endl;
    pid = fork();
    if (pid < 0)
        cout << "Fork failed" << endl;

    if (pid > 0) // Parent Process
    {
        char final[OUTPUT_SIZE];
        close(fd[WRITE_END]);
        if (read(fd[READ_END], final, sizeof(final)+1) < 0)
            cout << "Failed to read the output from reduce pipe!" << endl;
        close(fd[READ_END]);
        ofstream outfile ("output.csv");
        outfile << final;
    }
    else // Child Process
    {
        string all_named_pipes = concatNamedPipesNames(named_pipes_names);
        char* named_pipes_paths = stringToCharStar(all_named_pipes);
        char* files_number_ = stringToCharStar(to_string(files_number));
        close(fd[READ_END]);
        char* pipe_write_end = stringToCharStar(to_string(fd[WRITE_END]));
        char *argv[4] = {named_pipes_paths, files_number_, pipe_write_end, NULL};
        if (execv("./ReduceProcessorMain.out", argv) < 0)
            cout << "Failed to run file ReduceProcessorMain!" << endl;
        close(fd[WRITE_END]);
    }
    return 0;
}
