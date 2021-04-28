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

class LZ78_DC
{
public:
    LZ78_DC(string, string);
    ~LZ78_DC();

    int bufsize;
    char* input;
    string sInput;
    string fileName;
    string outputFileName,decompressed;
    string sOutput;
    vector<char> output;
    string sotp;
    int zeros;
    void init();

private:
    string Decompress(string& );
    void writeDataToFile(vector<char>&, string);
    char* readFile(const string, int&);
    string toString(char*, int);
    void convertDataToBin(string&, vector<char>&);
    string  getByte(char ch);
    void show_vec(const vector<string>& input);
    string decompressData_pt3(vector<string> &input);
    void decompressData_pt2(vector<string> &input);
    vector<string> decompressData_pt1(string &input);
    int last_zeros(string&);
    void delete_zeros(string&,int );
    char  stringToChar(string bin);
};
