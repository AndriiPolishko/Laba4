#include "LZ78_DC.h"


LZ78_DC::LZ78_DC(string in, string out)
{
    fileName = in;
    outputFileName = out;
    bufsize = MB;
    sOutput = "";
}

LZ78_DC::~LZ78_DC()
{
}

int LZ78_DC::last_zeros(string& bits)
{
    string temp = bits.substr(bits.size()-8,8);
     bits.erase(bits.size()-8,bits.size());
    return stoi(temp, 0, 2);
}
void LZ78_DC::delete_zeros(string& bits,int num)
{
    bits.erase(bits.size()-num,bits.size());
}

vector<string> LZ78_DC::decompressData_pt1(string &input)
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

void LZ78_DC::decompressData_pt2(vector<string> &input)
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

            //temp=to_string(ind)+pref;
            temp = input[ind]+pref;
            input[i] = temp;
        }
        else
            input[i] = temp;

    }
}

string LZ78_DC::vec_to_str(const vector<string>& vec)
{
    string res="";
    for(int i = 0;i<vec.size();i++)
        res+=vec[i];
    return res;
}

void LZ78_DC::init() {
    cout << "Decompresing data....\n";
    input = readFile(fileName, bufsize);

    sotp = toString( input,bufsize);
    if(sotp.size()==0)
    {
        cout<<"You passed empy file";
        exit(0);
    }
    //cout<<endl<<sotp;
    zeros = last_zeros(sotp);
    vector<string> s = decompressData_pt1(sotp);
    //show_vec(s);
    ///vector<string> res = decompressData_pt2(s);
    decompressData_pt2(s);
    //show_vec(s);

    string ori = vec_to_str(s);
    delete_zeros(ori,zeros);
    convertDataToBin(ori,output);
    writeDataToFile(output, outputFileName);
    cout << "Done" << endl;
}

char* LZ78_DC::readFile(const string filename, int& bufsize) {

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


string  LZ78_DC::toString(char* input, int inputSize)
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

void  LZ78_DC::convertDataToBin(string& sout, vector<char>& bout) {
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

char  LZ78_DC::stringToChar(string bin) {
    int ch = 0;


    for (int i = 0; i < 8; i++)
    {
        if (bin[i] == '1')
            ch += 1 << (7 - i);
    }
    return char(ch);
}

void  LZ78_DC::writeDataToFile(vector<char>& output, string fileName) {
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

string  LZ78_DC::getByte(char ch)
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



/*string LZ78_DC::decompressData_pt3(vector<string> &input)
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
*/
void LZ78_DC::show_vec(const vector<string>& input)
{
    cout<<endl;
    for(int i = 0;i<input.size();i++) cout<<input[i]<<" ";
    cout<<endl;
}