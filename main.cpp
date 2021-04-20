#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int findPrefix(vector<string>&, string &);
void printWhatsleft(int, string);
int readFile(const string, char*, const int);

int main() {
    const int bufsize = 100;
    char buffer[bufsize];
    int chars_read;
    string filename = "input.txt";

    chars_read = readFile(filename, buffer, bufsize);

    cout << "Chars read: " << chars_read << endl;


}
int findPrefix(vector<string>& dict, string& s) {

    for (int i = 0; i < dict.size(); i++)
    {
        if (dict[i] == s){
            return i;
        }
    }
    return -1;
}

void printWhatsleft(int start, string s)
{
    cout << ">> Left to encode: ";
    for (int i = start; i < s.size(); i++)
    {
        cout << s[i];
    }
    cout << endl;
}

int readFile(const string filename, char *buffer, const int bufsize) {

    ifstream infile;
    int chars_read;

    infile.open("input.txt", ios::binary | ios::out);
    if (!infile.is_open())
    {
        cout << "Failed to open the file!\n";
    }
    infile.read(buffer, bufsize);
    chars_read = infile.gcount();

    infile.close();

    return chars_read;
}
