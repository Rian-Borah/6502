/******************************************************************************
 * @author:     Rian Borah
 * @date:       23 Aug, 2023
 ******************************************************************************/

/******************************************************************************
 * @file:       cpu_6502.h
 * @desc:       Header file for 6502 microprocessor CPU
 *****************************************************************************/

#ifndef INC_6502_CPU_6502_H
#define INC_6502_CPU_6502_H

#include "6502.h"
#include "mem_6502.h"

class cpu_6502 {
private:
    /*
     *  private CPU struct
     *
     *  @date:      22 Aug, 2023
     *  @desc:      CPU internal registers for the 6502 processor
     */
    // CPU Fields
    word PC;        // program counter - 16bit
    byte SP;        // stack pointer - 8bit

    byte A, X, Y;   // registers

    // processor status bitflags : using C++ bitfields
    byte C : 1;     // carry
    byte Z : 1;     // zero
    byte I : 1;     // interrupt disable
    byte D : 1;     // decimal
    byte B : 1;     // break
    byte V : 1;     // overflow
    byte N : 1;     // negative


public:
    // Class Constructors & Destructors ----------------------------------------
    // Creates new cpu_6502 in the empty state.
    cpu_6502();

    // Manipulation procedures -------------------------------------------------
    /*
     *  reset()
     *
     *  @desc:      Resets the computer to the default state
     *  @param:     memory - 6502 memory
     *  @return:    None
     *  @ref:       https://www.c64-wiki.com/wiki/Reset_(Process)
     * */
    void reset(mem_6502& memory);

    /*
     *  LDASetStatus()
     *
     *  @desc:      Set status flags for LDA instructions
     * */
    void LDASetStatus();

    // Access functions --------------------------------------------------------
    /*
     *  fetchbyte()
     *
     *  @desc:      Fetches a single byte from memory
     *  @param:     cycles - Number of cycles to fetch based on instruction
     *              memory - 6502 memory
     *  @return:    Fetched byte
     * */
    byte fetchbyte(uint32_t& cycles, mem_6502& memory);

    /*
     *  fetchword()
     *
     *  @desc:      Fetches a single byte from memory
     *  @param:     cycles - Number of cycles to fetch based on instruction
     *              memory - 6502 memory
     *  @return:    Fetched byte
     * */
    word fetchword(uint32_t& cycles, mem_6502& memory);

    /*
     *  readbyte()
     *
     *  @desc:      Read a single instruction from memory
     *  @param:     cycles - Number of cycles to read based on instruction
     *              memory - 6502 memory
     *  @return:    Read byte
     * */
    static byte readbyte(uint32_t& cycles, uint32_t addr, mem_6502& memory);

    // Other Functions ---------------------------------------------------------
    /*
     *  execute()
     *
     *  @desc:      Executes a single instruction
     *  @param:     cycles - Number of cycles to fetchbyte based on instruction
     *              memory - 6502 memory
     *  @return:    None
     * */
    void execute(uint32_t cycles, mem_6502& memory);
};

#endif //INC_6502_CPU_6502_H
