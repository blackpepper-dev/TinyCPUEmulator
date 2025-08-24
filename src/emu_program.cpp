#include "include/emu_program.h"
#include "include/emu_cpu.h"


void LoadProgram(Emu_Program* instruction,size_t prog_size)
{
    for(size_t i = 0; i < prog_size; i++)
    {
        switch (instruction[i].opcode)
        {
            case NOP:
            case HLT:
                _cpu.Decoder.CommandRow(instruction[i].opcode);
                break;

            case OUT:
            case JMP:
                _cpu.Decoder.CommandRow(instruction[i].opcode,instruction[i].operand1);
                break;

            case MOV:
            case MVI:
            case ADD:
            case ADI:
            case MUL:
            case MLI:
            case SUB:
            case SUI:
            case DIV:
            case DVI:
            case SAV:            
                _cpu.Decoder.CommandRow(instruction[i].opcode,instruction[i].operand1,instruction[i].operand2);
                break;            

            default:
               
                break;
        }
        
    }
        
}