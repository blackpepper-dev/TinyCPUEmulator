#include "include/emu_disasm.h"



std::string Emu_Disasm::Format(const Emu_Program& instr, size_t index)
{
    std::ostringstream oss;
    oss << index << ": ";
    std::string op = OpcodeToStr(instr.opcode);
    oss << op;

    switch (instr.opcode)
    {
        case MVI:
        case ADI:
        case SUI:
        case MLI:
        case DVI:
        case CMP: oss << " " << RegToStr(instr.operand1) << ", " << static_cast<int>(instr.operand2);
            break;

        case MOV:
        case ADD:
        case SUB:
        case MUL:
        case DIV: oss << " " << RegToStr(instr.operand1) << ", " << RegToStr(instr.operand2);
            break;

        case SAV: oss << " " << RegToStr(instr.operand1) << ", [" << static_cast<int>(instr.operand2) << "]";
            break;

        case OUT: oss << " [" << static_cast<int>(instr.operand1) << "]";
            break;

        case JMP: oss << " -> " << static_cast<int>(instr.operand1);
            break;

        case NOP:
        case HLT:
            
            break;

        default:
            oss << " 0x" << std::hex << static_cast<int>(instr.operand1)
                << ", 0x" << std::hex << static_cast<int>(instr.operand2);
            break;
    }

    return oss.str();
}

std::string Emu_Disasm::OpcodeToStr(uint8_t opcode)
{
    switch (opcode)
    {
        case NOP: return "NOP";
        case MVI: return "MVI";
        case MOV: return "MOV";
        case ADI: return "ADI";
        case ADD: return "ADD";
        case SUI: return "SUI";
        case SUB: return "SUB";
        case MLI: return "MLI";
        case MUL: return "MUL";
        case DVI: return "DVI";
        case DIV: return "DIV";
        case SAV: return "SAV";
        case OUT: return "OUT";
        case CMP: return "CMP";
        case JMP: return "JMP";
        case HLT: return "HLT";
        default:  return "???";
    }
}

std::string Emu_Disasm::RegToStr(uint8_t reg)
{
    switch (reg)
    {
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        default: return "?";
    }
}
