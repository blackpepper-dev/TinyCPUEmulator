#include "headers/emu_memory.h"


uint8_t Emu_Memory::Read(uint16_t address)
{
    if(address >= sizeof(memory))
    {    
        std::cout << "Memory access violation!!!!\n";
        return 0;
    }

    return memory[address];
}

void Emu_Memory::Write(uint16_t address,uint8_t value)
{
    if(address >= sizeof(memory))     
        std::cout << "Memory access violation!!!!\n";
    else
        memory[address] = value;
}