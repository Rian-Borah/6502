/******************************************************************************
 * @author:     Rian Borah
 * @date:       23 Aug, 2023
 ******************************************************************************/

/******************************************************************************
 * @file:       cpu_6502.cpp
 * @desc:       Source file for 6502 microprocessor CPU
 *****************************************************************************/

#include "cpu_6502.h"

// Class Constructors & Destructors ----------------------------------------

// Creates new cpu_6502 in the empty state.
cpu_6502::cpu_6502(){
    PC = 0xFFFC;
    SP = 0xFF;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0x00;
}

// Manipulation procedures -------------------------------------------------
/*
 *  reset()
 *
 *  @desc:      Resets the computer to the default state
 *  @param:     memory - 6502 memory
 *  @return:    None
 *  @ref:       https://www.c64-wiki.com/wiki/Reset_(Process)
 * */
void cpu_6502::reset(mem_6502& memory){
    PC = 0xFFFC;
    SP = 0xFF;  // decremented 3 times from 0xFF for three fake push operations
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0x00;
    memory.init();
}

/*
 *  LDASetStatus()
 *
 *  @desc:      Set status flags for LDA instructions
 * */
void cpu_6502::LDASetStatus(){
    Z = (A == 0);               // set if A = 0
    N = ((A >> 7) & 0b1) == 1;     }


// Access functions --------------------------------------------------------
/*
 *  fetchbyte()
 *
 *  @desc:      Fetches a single byte from memory
 *  @param:     cycles - Number of cycles to fetch based on instruction
 *              memory - 6502 memory
 *  @return:    Fetched byte
 * */
byte cpu_6502::fetchbyte(uint32_t& cycles, mem_6502& memory){
    byte data = memory[PC];
    PC++;
    cycles--;
    return data;
}

/*
 *  fetchword()
 *
 *  @desc:      Fetches a single byte from memory
 *  @param:     cycles - Number of cycles to fetch based on instruction
 *              memory - 6502 memory
 *  @return:    Fetched byte
 * */
word cpu_6502::fetchword(uint32_t& cycles, mem_6502& memory){
    // 6502 is little endian
    word data = memory[PC];
    PC++;
    data |= (memory[PC] << 8);
    PC++;
    cycles -= 2;
    return data;
}

/*
 *  readbyte()
 *
 *  @desc:      Read a single instruction from memory
 *  @param:     cycles - Number of cycles to read based on instruction
 *              memory - 6502 memory
 *  @return:    Read byte
 * */
byte cpu_6502::readbyte(uint32_t& cycles, uint32_t addr, mem_6502& memory){
    byte data = memory[addr];
    cycles--;
    return data;
}

// Other Functions ---------------------------------------------------------
/*
 *  execute()
 *
 *  @desc:      Executes a single instruction
 *  @param:     cycles - Number of cycles to fetchbyte based on instruction
 *              memory - 6502 memory
 *  @return:    None
 * */
void cpu_6502::execute(uint32_t cycles, mem_6502& memory){
    while(cycles > 0){
        byte inst = fetchbyte(cycles, memory);
        switch (inst) {

            case LDA_IM:{
                byte val = fetchbyte(cycles, memory);
                A = val;
                LDASetStatus();
            } break;

            case LDA_ZP:{
                byte zpaddr = fetchbyte(cycles, memory);
                A = readbyte(cycles, zpaddr, memory);
                LDASetStatus();
            } break;

            case LDA_ZPX:{
                byte zpaddr = fetchbyte(cycles, memory);
                // TODO: Add overflow handling logic
                zpaddr += X;
                cycles--;
                A = readbyte(cycles, zpaddr, memory);
                LDASetStatus();
            } break;

            case JSR:{
                word subaddr = fetchword(cycles, memory);
                memory.writeword(cycles, PC - 1, SP);
                PC = subaddr;
                cycles--;
            } break;

            default:{
                printf("ERROR: Instruction not recognized: %d", inst);
            } break;
        }
    }
}