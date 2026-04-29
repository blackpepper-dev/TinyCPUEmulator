#include "include/emu_memory.h"


uint8_t Emu_Memory::Read(uint16_t address)
{
    if (address >= sizeof(memory)) {
        Logger.LogError("Out of memory buffer bounds in Emu_Memory::Rea");
        throw std::out_of_range("Memory read out of bounds in Emu_Memory::Read");
    }

    return memory[address];
}

void Emu_Memory::Write(uint16_t address, uint8_t value)
{
    if (address >= sizeof(memory)) {
        Logger.LogError("Out of memory buffer bounds in Emu_Memory::Write");
        throw std::out_of_range("Memory write out of bounds in Emu_Memory::Write");
    }

    memory[address] = value;
}
