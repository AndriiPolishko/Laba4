#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

char* readFile(const string, int&);

class RLA
        {
    void fileopening(string input,string output,string mode)
    {
        if(mode == "a")
        {
            ifstream fin(output + ".bin", ios::binary | ios::in | ios::app);
            ofstream fout(input + ".bin", ios::binary | ios::in );
            RunLenght_archiver(fout, fin);
        }
        if(mode=="d") {
            ifstream fin(input + ".bin", ios::binary | ios::in | ios::app);
            ofstream fout(output + ".bin", ios::binary | ios::in );
            RunLenght_dearchiver(fout, fin);
        }
    }
    void RunLenght_archiver(ofstream &fout, ifstream &fin)
    {
        string data(istreambuf_iterator<char>(fin), {}),ndata;
        int inrow = 1;
        for(size_t i = 0;i<data.size();i++)
        {
            while(data[i]==data[i+1] && i+1<data.size())
            {
                i++;
                inrow++;
            }
            ndata+=to_string(inrow)+data[i];
            inrow = 1;
        }
        fout.write( (char *)&ndata[0], ndata.size());
    }
    void RunLenght_dearchiver(ofstream &fout, ifstream &fin)
    {
        string data(istreambuf_iterator<char>(fin), {}),ndata="";
        for(size_t i = 0;i<data.size();i+=2)
        {
            ndata+=string_mult(int(data[i])-48,data[i+1]);
        }
        fout.write( (char *)&ndata[0], ndata.size());
    }
    string string_mult(int num,char ch)
    {
        string res="";
        for(size_t i = 0;i < num;i++)
            res+=ch;
        return res;
    }
        };
int main() {

    return 0;
}

char* readFile(const string filename,int & bufsize) {

    char *buffer = new char[bufsize];
    ifstream infile;

    infile.open(filename, ios::binary | ios::out);
    if (!infile.is_open())
    {
        cout << "Failed to open the file!\n";
        exit(0);
    }

    infile.read(buffer, bufsize);
    bufsize = infile.gcount();

    // Очищаємо пам`ять
    char* temp = new char[bufsize];
    for (int i = 0; i < bufsize; i++)
    {
        temp[i] = buffer[i];
    }
    delete[] buffer;

    infile.close();

    return temp;
}