#include <iostream>
#include <fstream>
#include <vector>

#define GB 1024 * 1024 * 1024
#define MB 1024 * 1024
#define KB 1024

using namespace std;

char* readFile(const string, int&);
void compressData(string&, char*, int);
int readBits(int, int, int);
int readBits(int, int);
string toString(char*, int);
string getByte(char);

int main() {
    int bufsize = GB;
    char *input;
    string filename = "input.txt";
    string sInput;
    vector<char> output;

    input = readFile(filename, bufsize);
    sInput = toString(input, bufsize);
    cout << sInput << endl;
}

char* readFile(const string filename,int & bufsize) {

    char *buffer = new char[bufsize];
    ifstream infile;

    infile.open("input.txt", ios::binary | ios::out);
    if (!infile.is_open())
    {
        cout << "Failed to open the file!\n";
    }

    infile.read(buffer, bufsize);
    bufsize = infile.gcount();

    // Очищаємо пам'ять
    char* temp = new char[bufsize];
    for (int i = 0; i < bufsize; i++)
    {
        temp[i] = buffer[i];
    }
    delete[] buffer;

    infile.close();

    return temp;
}

void compressData(string& output, char* input, int dataSize)
{
    vector<string> dictionary;
    string sub;
    int start, len;

    // Ініціалізація
    start = 0;
    len = 1;
    while (start < dataSize)
    {
        //sub = getPhrase(input, start, len);
    }

}

int readBits(int byte, int y, int o)
{
    if (o > 7 || y < 0 || y > o) {
        cout << "Fatal error! Can't read bits from " << y << " to " << o << endl;
        cout << "Function: readBits(int, int, int)" << endl;
        return 0;
    }

    int n = 0;

    for (int i = y; i <= o; i++)
    {
        n += 1 << i;
    }

    return byte & n;
}

int readBits(int byte, int b)
{
    if (b > 6 || b < 0) {
        cout << "Fatal error! Can't read bit: " << b << endl;
        cout << "Function: readBits(int, int)" << endl;
        return 0;
    }

    int n = 1 << b;

    return byte & n;
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