#include <iostream>
#include <fstream>
#include <cstring>
#include "cmake-build-debug/Archiver.cpp"
using namespace std;

void fileopening(string ,string ,string);
void RunLenght_archiver(ofstream &, ifstream &);
void RunLenght_dearchiver(ofstream &,ifstream &);
int main() {
    //for tests
    /*ifstream fin;
    ofstream fout;
    fout.open("test.bin",ios::binary|ios::out|ios::app);
    fin.open("test.bin",ios::binary|ios::in|ios::app);
    string x="ab";
    fout.write(x.data(), x.size());
    fout.close();
    std::string y(std::istreambuf_iterator<char>(fin), {});
    cout<<y;
    fin.close();*/
    /*string data="aaaabbbaaccce   ",ndata;
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

    cout<<ndata[ndata.size()-2];*/
    fileopening("input","output","archive");
    return 0;
}
void fileopening(string input,string output,string mode)
{
    ifstream fin(output+".bin",ios::binary|ios::in|ios::app);
    ofstream fout(input+".bin",ios::binary|ios::in|ios::app);
    if(mode=="archive")
        RunLenght_archiver(fout,fin);
    if(mode=="dearchive")
        RunLenght_dearchiver(fout,fin);


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
    fout.write( (char *)&ndata, sizeof(ndata));
}

/*class User
        {
public:
            char * name;
            int age;
            User(char* name,int age)
            {
                this->name = name;
                this->age = age;
            }
            User(){}
        };
*/

/*fout.write((char *)&buf,sizeof (buf));
   while(fin.read((char *)&b,sizeof (b)))
   {
       cout<<b;
   }*/

/* if(fin.is_open())
   {
      char ch;
      while(fin.read(ch))
          {
          cout<<ch<< " ";
          }
    }
   else
       {
       cout<<"File wasn't open\n";
       }
   fout.close();
   fin.close();*/

/*
u16 ReadU16(istream& file)
{
u16 val;
u8 bytes[2];

file.read( (char*)bytes, 2 );  // read 2 bytes from the file
val = bytes[0] | (bytes[1] << 8);  // construct the 16-bit value from those bytes

return val;
}

void WriteU16(ostream& file, u16 val)
{
    u8 bytes[2];

    // extract the individual bytes from our value
    bytes[0] = (val) & 0xFF;  // low byte
    bytes[1] = (val >> 8) & 0xFF;  // high byte

    // write those bytes to the file
    file.write( (char*)bytes, 2 );
}*/