/******************************************************************************
 * @author:     Rian Borah
 * @date:       22 Aug, 2023
 ******************************************************************************/

/******************************************************************************
 * @file:       6502.h
 * @desc:       Header file for 6502 microprocessor emulator
 * @ref:        http://www.6502.org/users/obelisk/
 *****************************************************************************/

#ifndef INC_6502_H
#define INC_6502_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cinttypes>
#include <cerrno>

typedef uint8_t byte;
typedef uint16_t word;

// opcodes for LDA
static constexpr byte
        LDA_IM  = 0xA9,
        LDA_ZP  = 0xA5,
        LDA_ZPX = 0xB5,
        JSR     = 0x20;

#endif //INC_6502_H