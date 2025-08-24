#include <iostream>
#include "headers/emu_program.h"
#include "headers/emu_disasm.h"
#include "headers/emu_cpu.h"


int main()
{
    Emu_Program ops[] = 
    {
        {MVI, A, 10},
        {MVI, B, 20},
        {JMP, 12}, // jump to row #12
        {ADD, A, B},
        {ADD, B, A},
        {DVI, A, 2},
        {DVI, B, 2},
        {MOV, C, A},
        {MOV, D, B},
        {ADI, C, 10},
        {ADI, D, 10},        
        {SAV, A, 0}, //#12
        {SAV, B, 1},
        {SAV, C, 2},
        {SAV, D, 3},
        {OUT, 0},
        {OUT, 1},
        {OUT, 2},
        {OUT, 3},
        {HLT}
    };

    _cpu.InitCPU();    

    LoadProgram(ops, sizeof(ops) / sizeof(Emu_Program));

    
    std::cout << "=== Program Disassembly ===\n";
    for (size_t i = 0; i < sizeof(ops) / sizeof(Emu_Program); ++i)
    {
        std::cout << Emu_Disasm::Format(ops[i], i) << std::endl;
    }

    _cpu.Execute();    
    
    _cpu.DUMP_CPU();

    std::cin.get();

    return 0;
}
