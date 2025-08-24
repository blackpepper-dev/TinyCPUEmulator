#pragma once

#include <sstream>
#include <iomanip>
#include "emu_program.h"
#include "emu_enums.h"

struct Emu_Disasm
{
    static std::string Format(const Emu_Program& instr, size_t index);
    static std::string OpcodeToStr(uint8_t opcode);
    static std::string RegToStr(uint8_t reg);
};
