#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <bitset>
#include <sstream>

using namespace std;

#define GB 1024 * 1024 * 1024
#define MB 1024 * 1024
#define KB 1024

char* readFile(const string, int&);
string toString(char* , int );
string getByte(char );
string intToBin(int dec, int k);
void compressData(string& , string&);
int findPrefix(vector<string>& , string& );
void writeDataToFile(vector<char>& , string );
void convertDataToBin(string& sout, vector<char>& bout);

vector<string> decompressData_pt1(string &);
void decompressData_pt2(vector<string> &);
string decompressData_pt3(vector<string> &input);
void show_vec(const vector<string> &);
vector<char> bin_to_str(string);
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
    int bufsize = MB,nbuf = MB;
    char *input,*otp;
    string fileName = "input.txt";
    string outputFileName = "output.lz78";
    string sInput,sotp;
    string sOutput= "";
    vector<char> output;

    cout << "Reading file....";
    input = readFile(fileName, bufsize);
    cout<<input<<endl;
    cout << "Done\nConverting data into string...";
    sInput = toString(input, bufsize);
    cout<<sInput<<endl;
    cout << "Done\nCompressing data...";
    compressData(sOutput, sInput);
    cout<<sOutput<<endl;
    cout << "Done\nConverting data back to bin...";
    convertDataToBin(sOutput, output);
    cout << "Done\nWriting data in file...";
    writeDataToFile(output, outputFileName);
    cout << "Done" << endl;
    otp = readFile(outputFileName, nbuf);
    sotp = toString(otp,nbuf);
    cout<<sotp<<endl;
    vector<string> s = decompressData_pt1(sotp);
    show_vec(s);
    ///vector<string> res = decompressData_pt2(s);
    decompressData_pt2(s);
    show_vec(s);
    string ori = decompressData_pt3(s);
    vector<char> decomp = bin_to_str(ori);
    writeDataToFile(decomp,"decoded.txt");

}

vector<char> bin_to_str(string data)
{
    std::stringstream sstream(data);
    std::string output;
    vector<char> mas;

    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        mas.push_back(c);
    }
    return mas;

}


void convertDataToBin(string& sout, vector<char>& bout) {
    if (sout.size() % 8 != 0) {
        int t = 8 - sout.size() % 8;
        for (int i = 0; i < t; i++) {
            sout += '0';
        }
    }
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

vector<string> decompressData_pt1(string &input)
{
    vector<string> dict;
    dict.push_back("");
    string sub, t;
    int start,previuosPrefix, prefix = 0, k;
    float len;
    // Кодування
    start = 0;
    len = 1;
    k = 1;
    while (start<input.size())
    {
        len = log2(k);
        if(len!=int(len))
            len = int(len)+1;
        len+=1;
        sub = input.substr(start, len);
        start += len;
        k++;
        //cout<<sub<<" ";
        dict.push_back(sub);
    }
    return dict;
}


void decompressData_pt2(vector<string> &input)
{
    vector<string> res;
    res.push_back("");
    string temp;
    char pref;
    int ind;
    for(int i = 0 ;i<input.size();i++)
    {
        temp = input[i];
        pref = input[i].back();
        if(temp.size()>1)
        {
            int ind = stoi(temp.substr(0,temp.size()-1),0,2);
            temp=to_string(ind)+pref;
            input[i] = temp;
        }
        else
            input[i] = temp;

    }
}

string decompressData_pt3(vector<string> &input)
{
    string temp,res;
    char pref;
    int pos;
    for(int i = 0;i<input.size();i++)
    {
        temp = input[i];
        if(temp.size()>1)
        {
            pref = temp.back();
            pos = int(temp[0])-48;
            temp =input[pos]+pref;
            input[i]=temp;
            cout<<temp<<endl;
            res+=temp;

        }
        else
            res+=temp;

    }
    return res;
}

void show_vec(const vector<string>& input)
{
    cout<<endl;
    for(int i = 0;i<input.size();i++) cout<<input[i]<<" ";
    cout<<endl;
}
