#pragma once
/*
    Author: Artem Yahniuk
    Description: Own implementation of 8-bit CPU with own asm
    and functions to work with it
*/

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "emu_enums.h"
#include "emu_memory.h"
#include "emu_decoder.h"


/*========================================================================*/
struct Emu_CPU
{
    
    uint8_t A; //Registr A
    uint8_t B; //Registr B
    uint8_t C; //Registr C
    uint8_t D; //Registr D
   
    
    uint8_t PC; //PC - Program counter    

    struct
    {
        uint8_t zero = 0x00;
        uint8_t carry = 0x00;
        uint8_t overflow = 0x00;
    } SR;
    

    bool halted; 

    Emu_Memory Memory;
    Emu_Decoder Decoder;

    void ALU_OP(uint8_t &regref, uint8_t op, uint8_t value);
    uint8_t GetRegisterValue(uint8_t reg);   
    uint8_t& GetRegisterRef(uint8_t reg_id);
    void InitCPU();
    void DUMP_CPU();

    bool Tick() {return halted;};
    
    void Execute();

};
/*========================================================================*/

extern Emu_CPU _cpu;

