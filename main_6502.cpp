/*
 *  @author:    Rian Borah
 *  @date:      22 Aug, 2023
 *
 *  @desc:      An emulator for the 6502 microprocessor
 *
 *  @ref:       http://www.6502.org/users/obelisk/
 * */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <cerrno>

using byte = uint8_t;
using word = uint16_t;

/*
 *  struct Mem
 *  @date:      22 Aug, 2023
 *  @desc:      Memory blocks for the 6502 processor
 *  @note:      Processor is little endian
 *              Addresses stored in memory using LSB
 * */
struct Mem{
    static constexpr uint32_t MAX_MEM = 1024 * 64;
    byte data[MAX_MEM];

public:
    /*
     *  init()
     *
     *  @desc:      Initializes memory blocks
     *  @param:     None
     *  @return:    None
     * */
    void init(){
        memset(data, 0, sizeof(data));
        return;
    }

    /*
     *  operator[]
     *
     *  @desc:      Operator overload to read 1 byte from memory block
     *  @param:     addr - Address to read from
     *  @return:    1 byte from memory block
     * */
    byte operator[](uint32_t addr) const{
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
    byte& operator[](uint32_t addr){
        if(addr >= MAX_MEM){
            fprintf(stderr, "ERROR: Invalid write address %d", addr);
            perror("");
            exit(EXIT_FAILURE);
        }
        return data[addr];
    }
};

/*
 *  struct CPU
 *
 *  @date:      22 Aug, 2023
 *  @desc:      CPU internal registers for the 6502 processor
 * */
struct CPU{
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
        SP = 0xFF;  // decremented 3 times from 0xFF for three fake push operations
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0x00;
        memory.init();
        return;
    }

    /*
     *  fetch()
     *
     *  @desc:      Fetches a single instruction from memory
     *  @param:     cycles - Number of cycles to fetch based on instruction
     *              memory - 6502 memory
     *  @return:    Instruction byte
     * */
    byte fetch(uint32_t& cycles, Mem& memory){
        byte data = memory[PC];
        PC++;
        cycles--;
        return data;
    }

    /*
     *  read()
     *
     *  @desc:      Read a single instruction from memory
     *  @param:     cycles - Number of cycles to fetch based on instruction
     *              memory - 6502 memory
     *  @return:    Instruction byte
     * */
    byte read(uint32_t& cycles, uint32_t addr, Mem& memory){
        byte data = memory[addr];
        cycles--;
        return data;
    }

    /*
     *  LDASetStatus()
     *
     *  @desc:      Set status flags for LDA instructions
     * */
    void LDASetStatus(){
        Z = (A == 0);               // set if A = 0
        N = (A & (0b1 << 7)) == 1;  // set if bit 7 in A is set
        return;
    }

    // opcodes
    static constexpr byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5;


    /*
     *  execute()
     *
     *  @desc:      Executes a single instruction
     *  @param:     cycles - Number of cycles to fetch based on instruction
     *              memory - 6502 memory
     *  @return:    None
     * */
    void execute(uint32_t cycles, Mem& memory){
        while(cycles > 0){
            byte inst = fetch(cycles, memory);
            switch (inst) {

            case INS_LDA_IM:{
                byte val = fetch(cycles, memory);
                A = val;
                LDASetStatus();
            } break;

            case INS_LDA_ZP:{
                byte zpaddr = fetch(cycles, memory);
                A = read(cycles, zpaddr, memory);
                LDASetStatus();
            } break;

            default:{
                printf("ERROR: Instruction not recognized: %d", inst);
            } break;
            }
        }
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
    Mem mem6502;
    CPU cpu6502;

    cpu6502.reset(mem6502);

    // hardcoded inline program to test
    // start
    mem6502[0xFFFC] = CPU::INS_LDA_ZP;
    mem6502[0xFFFD] = 0x42;
    mem6502[0x42] = 0x84;
    // end

    cpu6502.execute(3, mem6502);

    exit(EXIT_SUCCESS);
}
