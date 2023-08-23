/*
 *  @author:    Rian Borah
 *  @date:      22 Aug, 2023
 *
 *  @desc:      An emulator for the 6502 microprocessor
 *
 *  @ref:       http://www.6502.org/users/obelisk/
 * */

#include "6502.h"
#include "cpu_6502.h"
#include "mem_6502.h"

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
    mem_6502 mem{};
    cpu_6502 cpu{};

    cpu.reset(mem);

    // hardcoded inline program to test
    // start
    mem[0xFFFC] = cpu_6502::LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x42] = 0x84;
    // end

    cpu.execute(3, mem);

    exit(EXIT_SUCCESS);
}
