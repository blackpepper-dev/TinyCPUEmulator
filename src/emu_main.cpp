#include <iostream>
#include "include/emu_loader.h"
#include "include/emu_program.h"
#include "include/emu_disasm.h"
#include "include/emu_cpu.h"
#include "include/Logger.h"




int main()
{
    
    //Logger.LogToConsole = true;
    Logger.LogToFile = true;    
    Logger.Init();

    Emu_Program ops[] = 
    {
        {MVI, A, 20},
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
        {SAV, B, 1}, //#13
        {SAV, C, 2},
        {SAV, D, 3},
        {PRN, 0},
        {PRN, 1},
        {PRN, 2},
        {PRN, 3},
        {HLT}
    };

    _cpu.InitCPU();    

    LoadProgram(ops, sizeof(ops) / sizeof(Emu_Program));

    
    Logger.LogInfo("=== Program Disassembly ===");
    for (size_t i = 0; i < sizeof(ops) / sizeof(Emu_Program); ++i)
    {
        Logger.LogInfo(Emu_Disasm::Format(ops[i], i));
    }

    _cpu.Execute();    
    _cpu.DUMP_CPU();


    Emu_Loader loader;
    loader.LoadSource("1.txt");

    std::cin.get();

    return 0;
}
