#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_C.h"
#include "C:\Users\ramp8\Laboratorni_Z_OP\Laba4\cmake-build-debug\LZ78_DC.h"
int main() {
    LZ78_C comp("input.txt", "output.lz78");
    LZ78_DC decomp("output.lz78","decomp.txt");
    decomp.init();
    //comp.init();
    return 0 ;
}