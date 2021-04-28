#include "LZ78_C.h"
#include "LZ78_DC.h"
using namespace  std;
string get_name( const char* );
int main(int argc, char** argv) {

    string mode = get_name((const char* )argv[1]);
    string input_file = get_name((const char* )argv[2]);
    string output_file = get_name((const char* )argv[3]);

    if(mode=="--compress")
    {
       LZ78_C comp(input_file, output_file);
       comp.init();
    }

    if(mode=="--decompress")
    {
        LZ78_DC decomp(input_file, output_file);
        decomp.init();
    }

    return 0 ;
}

string get_name( const char* ch)
{
    int size=0;
    string s;
    while (ch[size] != '\0') {
        s.push_back(ch[size]);
        size++;}
    return s;
}