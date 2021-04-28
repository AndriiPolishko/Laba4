#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

#define GB 1024 * 1024 * 1024
#define MB 1024 * 1024
#define KB 1024

class LZ78_C
{
public:
    LZ78_C(string, string);
    ~LZ78_C();

    int bufsize;
    char* input;
    string sInput;
    string fileName;
    string outputFileName;
    string sOutput;
    vector<char> output;

    void init();

private:
    void compressData(string&, string&);
    void writeDataToFile(vector<char>&, string);
    char* readFile(const string, int&);
    int findPrefix(vector<string>&, string&);
    string toString(char*, int);
    string getByte(char);
    string intToBin(int, int);
    void convertDataToBin(string&, vector<char>&);
    char stringToChar(string);

};
