#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_C.h"
#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_DC.h"
int main(int argc, char** argv) {
//input.txt output.lz78 decomp.txt
    const char* ch = (const char* )argv[1];
    string s;
    int Size;
    while (ch[Size] != '\0') {
        s.push_back(ch[Size]);
        Size++;
    }
    //cout<<s;

    //string s = string(ch);
    if(s=="--compress")
    {
        string inp = string(argv[2]),otp = string(argv[3]);
        cout<<inp<<endl<<otp;
        LZ78_C comp(inp, otp);

        comp.init();
    }
    if(s=="--decompress")
    {
        string inp = string(argv[2]),otp = string(argv[3]);
        LZ78_DC decomp(inp, otp);
        decomp.init();
    }

    return 0 ;
}