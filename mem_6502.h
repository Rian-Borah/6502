/******************************************************************************
 * @author:     Rian Borah
 * @date:       23 Aug, 2023
 ******************************************************************************/

/******************************************************************************
 * @file:       mem_6502.h
 * @desc:       Header file for 6502 microprocessor Memory
 *****************************************************************************/

#ifndef INC_6502_MEM_6502_H
#define INC_6502_MEM_6502_H

#include "6502.h"

class mem_6502 {
private:
    /*
     *  struct Mem
     *  @date:      22 Aug, 2023
     *  @desc:      Memory blocks for the 6502 processor
     *  @note:      Processor is little endian
     *              Addresses stored in memory using LSB
    */

    // Memory Fields
    static constexpr uint32_t MAX_MEM = 1024 * 64;
    byte data[MAX_MEM];

public:
    // Class Constructors & Destructors ----------------------------------------

    // Creates new mem_6502 in the empty state.
    mem_6502();

    // Copy constructor.
    mem_6502(const mem_6502& Mem);

    // Manipulation procedures -------------------------------------------------
    /*
     *  init()
     *
     *  @desc:      Initializes memory blocks
     *  @param:     None
     *  @return:    None
     * */
    void init();

    // Overloaded Operators ----------------------------------------------------
    /*
     *  operator[]
     *
     *  @desc:      Operator overload to read 1 byte from memory block
     *  @param:     addr - Address to read from
     *  @return:    1 byte from memory block
     * */
    byte operator[](uint32_t addr) const;

    /*
     *  operator[]
     *
     *  @desc:      Operator overload to write 1 byte to memory block
     *  @param:     addr - Address to write to
     *  @return:    1 byte from memory block
     * */
    byte& operator[](uint32_t addr);

    /*
     *  writeword()
     *
     *  @desc:      Writes a word to memory
     *  @param:     cycles - Number of cycles to write based on instruction
     *              writedata - 16bit data to write to memory
     *              memory - 6502 memory
     *  @return:    None
     * */
    void writeword(uint32_t& cycles, word writedata, uint32_t addr);
};

#endif //INC_6502_MEM_6502_H
