#include "LZ78_C.h"


LZ78_C::LZ78_C(string in, string out)
{
    fileName = in;
    outputFileName = out;
    bufsize = MB;
    sOutput = "";
}

LZ78_C::~LZ78_C()
{
}

void LZ78_C::init() {
    cout << "Compresing data....";
    input = readFile(fileName, bufsize);
    sInput = toString(input, bufsize);
    compressData(sOutput, sInput);
    cout << sOutput << endl;
    convertDataToBin(sOutput, output);
    writeDataToFile(output, outputFileName);
    cout << "Done" << endl;
}

char* LZ78_C::readFile(const string filename, int& bufsize) {

    char* buffer = new char[bufsize];
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

void  LZ78_C::compressData(string& output, string& Input)
{
    vector<string> dict = { "" };
    string sub, t;
    int start, len, previuosPrefix, prefix = 0, k;

    // Кодування
    start = 0;
    len = 1;
    k = 1;
    while (true)
    {
        if ((start + len) % 2000 == 0)
        {
            cout << (start + len) << "/" << Input.size() << endl;
        }
        if (start + len > Input.size()) break;
        sub = Input.substr(start, len);
        previuosPrefix = findPrefix(dict, sub);
        if (previuosPrefix != -1)
        {
            if (start + len >= Input.size())
            {
                sub = Input.substr(start, len);
                prefix = findPrefix(dict, sub);
                t = intToBin(prefix, k);
                if (sub != dict[prefix])
                {
                    t += char(sub[sub.size() - 1]);
                }
                output += t;
                cout << t << " ";
                break;
            }
            else if (dict.size() < 100000) {
                prefix = previuosPrefix;
                len++;
            }
            else {
                t = intToBin(prefix, k) + char(sub[sub.size() - 1]);
                output += t;
                cout << t << " ";
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
            cout << t << " ";
            dict.push_back(sub);
            k++;
            start += len;
            prefix = 0;
            len = 1;

        }
    }
}

string  LZ78_C::toString(char* input, int inputSize)
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

string  LZ78_C::getByte(char ch)
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

string  LZ78_C::intToBin(int dec, int k)
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

int  LZ78_C::findPrefix(vector<string>& dict, string& s) {

    for (int i = 0; i < dict.size(); i++)
    {
        if (dict[i] == s) {
            return i;
        }
    }
    return -1;
}

void  LZ78_C::convertDataToBin(string& sout, vector<char>& bout) {
    int t = 0;
    if (sout.size() % 8 != 0)
    {
        t = 8 - sout.size() % 8;
        for (int i = 0; i < t; i++)
        {
            sout += '0';
        }
    }

    for (int i = 0; i < sout.size(); i += 8)
    {
        bout.push_back(stringToChar(sout.substr(i, 8)));
    }
    bout.push_back(char(t));

}

char  LZ78_C::stringToChar(string bin) {
    int ch = 0;


    for (int i = 0; i < 8; i++)
    {
        if (bin[i] == '1')
            ch += 1 << (7 - i);
    }
    return char(ch);
}

void  LZ78_C::writeDataToFile(vector<char>& output, string fileName) {
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