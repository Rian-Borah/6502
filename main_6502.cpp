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

/*
 *  struct CPU
 *  @date:      22 Aug, 2023
 *  @desc:      CPU registers for the 6502 processor
 * */
struct CPU{
    using Byte = unsigned char;
    using Word = unsigned short;

    Word PC;        // program counter
    Word SP;        // stack pointer

    Byte A, X, Y;   // registers

    // processor status bitflags : using C++ bitfields
    Byte C : 1;     // carry
    Byte Z : 1;     // zero
    Byte I : 1;     // interrupt disable
    Byte D : 1;     // decimal
    Byte B : 1;     // break
    Byte V : 1;     // overflow
    Byte N : 1;     // negative
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
    CPU cpu6502;

    return EXIT_SUCCESS;
}
