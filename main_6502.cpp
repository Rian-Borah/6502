/*
 *  @author:    Rian Borah
 *  @date:      22 Aug, 2023
 *
 *  @desc:      An emulator for the 6502 microprocessor
 *
 *  @ref:       http://www.6502.org/users/obelisk/
 * */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>

using Byte = unsigned char;
using Word = unsigned short;

/*
 *  struct Mem
 *  @date:      22 Aug, 2023
 *  @desc:      Memory blocks for the 6502 processor
 * */
struct Mem{
    static constexpr uint32_t MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

public:
    /*
     *  init()
     *
     *  @desc:      Initializes memory blocks
     *  @param:     None
     *  @return:    None
     * */
    void init(){
        memset(Data, 0, sizeof(Data));
        return;
    }
};

/*
 *  struct CPU
 *
 *  @date:      22 Aug, 2023
 *  @desc:      CPU internal registers for the 6502 processor
 * */
struct CPU{
    Word PC;        // program counter - 16bit
    Byte SP;        // stack pointer - 8bit

    Byte A, X, Y;   // registers

    // processor status bitflags : using C++ bitfields
    Byte C : 1;     // carry
    Byte Z : 1;     // zero
    Byte I : 1;     // interrupt disable
    Byte D : 1;     // decimal
    Byte B : 1;     // break
    Byte V : 1;     // overflow
    Byte N : 1;     // negative

public:
    /*
     *  reset()
     *
     *  @desc:      Resets the computer to the default state
     *  @param:     memory - 6502 memory
     *  @return:    None
     *  @ref:       https://www.c64-wiki.com/wiki/Reset_(Process)
     * */
    void reset(Mem& memory){
        PC = 0xFFFC;
        SP = 0xFD;  // decremented 3 times from 0xFF for three fake push operations
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0x00;
        memory.init();
        return;
    }
};


/*
 *  main()
 *
 *  @author:    Rian Borah
 *  @desc:      Main for 6502 project
 *  @date:      22 Aug, 2023
 *  @param:     None
 *  @return:    EXIT_SUCCESS or EXIT_FAILURE, based on runtime
 * */
int main() {
    // processor is little endian
    // addresses stored in memory using LSB
    Mem mem6502;
    CPU cpu6502;

    return EXIT_SUCCESS;
}
