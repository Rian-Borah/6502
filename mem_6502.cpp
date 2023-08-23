/******************************************************************************
 * @author:  Rian Borah
 * @date:    23 Aug, 2023
 ******************************************************************************/

/******************************************************************************
 * @file:    mem_6502.cpp
 * @desc:    Source file for 6502 microprocessor Memory
 * @ref:
 *****************************************************************************/

#include "mem_6502.h"

// Class Constructors & Destructors ----------------------------------------

// Creates new mem_6502 in the empty state.
mem_6502::mem_6502(){
    memset(data, 0, sizeof(data));
}

// Copy constructor.
mem_6502::mem_6502(const mem_6502& Mem){
    memcpy(data, Mem.data, sizeof(MAX_MEM));
}

/*
 *  init()
 *
 *  @desc:      Initializes memory blocks
 *  @param:     None
 *  @return:    None
 * */
void mem_6502::init(){
    memset(data, 0, sizeof(data));
}

/*
 *  operator[]
 *
 *  @desc:      Operator overload to read 1 byte from memory block
 *  @param:     addr - Address to read from
 *  @return:    1 byte from memory block
 * */
byte mem_6502::operator[](uint32_t addr) const{
    if(addr >= MAX_MEM){
        fprintf(stderr, "ERROR: Invalid read address %d", addr);
        perror("");
        exit(EXIT_FAILURE);
    }
    return data[addr];
}

/*
 *  operator[]
 *
 *  @desc:      Operator overload to write 1 byte to memory block
 *  @param:     addr - Address to write to
 *  @return:    1 byte from memory block
 * */
byte& mem_6502::operator[](uint32_t addr){
    if(addr >= MAX_MEM){
        fprintf(stderr, "ERROR: Invalid write address %d", addr);
        perror("");
        exit(EXIT_FAILURE);
    }
    return data[addr];
}

/*
 *  writeword()
 *
 *  @desc:      Writes a word to memory
 *  @param:     cycles - Number of cycles to write based on instruction
 *              writedata - 16bit data to write to memory
 *              memory - 6502 memory
 *  @return:    None
 * */
void mem_6502::writeword(uint32_t& cycles, word writedata, uint32_t addr){
    data[addr] = writedata & 0xFF;
    data[addr + 1] = (writedata << 8);
    cycles -= 2;
}