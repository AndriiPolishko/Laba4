#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

char* readFile(const string, int&);
string toString(char* , int );
string getByte(char );
string intToBin(int dec, int k);
void compressData(string& , string&);
int findPrefix(vector<string>& , string& );
void writeDataToFile(vector<char>& , string );

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

void writeDataToFile(vector<char>& output, string fileName) {
    ofstream outfile;
    outfile.open(fileName, ios::binary | ios::out);

    if (!outfile.is_open())
    {
        cout << "Failed to open output file!" << endl;
        cout << ">> writeDataToFile(vector<char>&, string)" << endl;
    }
    else {
        outfile.write(&output[0], output.size());
    }
}

int findPrefix(vector<string>& dict, string& s) {

    for (int i = 0; i < dict.size(); i++)
    {
        if (dict[i] == s) {
            return i;
        }
    }
    return -1;
}

string intToBin(int dec, int k)
{
    string bin = "";
    float l;

    l = log2(k);


    if (l == int(l))
    {
        k = l;
    }
    else {
        k = l + 1;
    }

    for (int i = 0; i < k; i++)
    {
        if (dec & (1 << i)) {
            bin += '1';
        }
        else {
            bin += '0';
        }
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

void compressData(string& output, string& input)
{
    vector<string> dict = {""};
    string sub, t;
    int start, len, previuosPrefix, prefix = 0, k;

    // Кодування
    start = 0;
    len = 1;
    k = 1;
    while (true)
    {
        if ((start+len)%2000==0)
        {
            cout << (start + len) << "/" << input.size() << endl;
        }
        if (start + len > input.size()) break;
        sub = input.substr(start, len);
        previuosPrefix = findPrefix(dict, sub);
        if (previuosPrefix != -1)
        {
            if (start + len >= input.size())
            {
                t =  intToBin(prefix, k) + char(sub[sub.size() - 1]);
                output += t;
                break;
            }
            else if(dict.size()<100000){
                prefix = previuosPrefix;
                len++;
            }
            else {
                t = intToBin(prefix, k) + char(sub[sub.size() - 1]);
                output += t;
                dict.push_back(sub);
                k++;
                start += len;
                prefix = 0;
                len = 1;
            }
        }
        else {

            t = intToBin(prefix, k) + char(sub[sub.size() - 1]);
            output += t;
            dict.push_back(sub);
            k++;
            start += len;
            prefix = 0;
            len = 1;

        }
    }

    cout<<endl<<endl;
    for(int i = 0;i<dict.size();i++)
        cout<<dict[i]<<" ";
    cout<<endl;
}

string getByte(char ch)
{
    string phrase = "";
    int byte = int(ch);

    for (int i = 7; i > -1; i--)
    {
        if (byte & (1 << i))
            phrase += '1';
        else
            phrase += '0';
    }
    return phrase;
}

string toString(char* input, int inputSize)
{
    string result = "";
    string byte;
    for (int i = 0; i < inputSize; i++)
    {
        byte = getByte(input[i]);
        result += byte;
    }

    return result;
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