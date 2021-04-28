#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_C.h"
#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_DC.h"
using namespace  std;
int main(int argc, char** argv) {
//input.txt output.lz78 decomp.txt
/*
    const char* ch = (const char* )argv[1];
    string s,ss,sss;
    int Size=0;
    while (ch[Size] != '\0') {
        s.push_back(ch[Size]);
        Size++;
    }

    const char* file2 = (const char* )argv[2];
    int Size1=0;
    while (file2[Size1] != '\0') {
        ss.push_back(file2[Size1]);
        Size1++;
    }

    const char* file3 = (const char* )argv[3];
    int Size2=0;
    while (file3[Size2] != '\0') {
        sss.push_back(file3[Size2]);
        Size2++;
    }
    //cout<<s;
*/
    //string s = string(ch);
    /*if(s=="--compress")
    {*/
//    string ss=  "input.txt", sss = "output.lz78";
//        LZ78_C comp(ss, sss);
//        comp.init();
    //}

    /*if(s=="--decompress")
    {
        string inp = string(argv[2]),otp = string(argv[3]);
*/
    string ss= "output.lz78" , sss = "decpmp.txt";
        LZ78_DC decomp(ss, sss);
        decomp.init();
   /* }*/

    return 0 ;
}//Laba4.exe --decompress output.lz78 decomp.txt
//out.lz78
//