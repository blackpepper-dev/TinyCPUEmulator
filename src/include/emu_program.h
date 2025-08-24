#pragma once


/*
    Author: Artem Yahniuk
    Descriptrion: Implementation of program loader to decoder

*/

#include <cstdint>
#include "emu_decoder.h"

struct Emu_CPU;

struct Emu_Program
{

    uint8_t opcode;
    uint8_t operand1 = 0x00;
    uint8_t operand2 = 0x00;

    Emu_Program(uint8_t op, uint8_t op1 = 0x00, uint8_t op2 = 0x00): opcode(op), operand1(op1), operand2(op2) {}

};


void LoadProgram(Emu_Program* instruction,size_t prog_size);