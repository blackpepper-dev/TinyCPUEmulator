#pragma once
/*
    Author: Artem Yahniuk
    Description: Memory struct and functions to work with
*/

#include <iostream>
#include <cstdint>

struct Emu_Memory
{
    const uint8_t CS = 0x00; //Code segment;
    const uint16_t DS = 0x200; //Data segment;

    uint8_t memory[1024];

    uint8_t Read(uint16_t address);
    void Write(uint16_t address,uint8_t value);
};
