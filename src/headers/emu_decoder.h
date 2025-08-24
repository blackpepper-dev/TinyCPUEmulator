#pragma once

/*
    Author: Artem Yahniuk
    Descriptrion: Implementation of 8-bit CPU asm decoder
    and functions to work with it
*/

#include <iostream>
#include <cstdint>
#include "emu_memory.h"

struct Emu_CPU;

struct Emu_Decoder
{
    Emu_Memory* mem = nullptr;

    uint8_t CC = 0x00; //CC - Command counter


    void BindMemory(Emu_Memory& memory) { mem = &memory; };
    void CommandRow(uint8_t opcode,uint8_t reg,uint8_t operand);
    void CommandRow(uint8_t opcode,uint8_t operand);
    void CommandRow(uint8_t opcode);    
    void Decode(Emu_CPU& cpu);
};

