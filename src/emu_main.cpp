#include <iostream>
#include "include/emu_loader.h"
#include "include/emu_program.h"
#include "include/emu_disasm.h"
#include "include/emu_cpu.h"
#include "include/Logger.h"


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


int main()
{    
    
    Logger.LogToFile = true;    
    Logger.Init();

    _cpu.InitCPU();

    Emu_Loader loader;
    loader.LoadSource("1.txt");
    size_t progSize = 0;
    Emu_Program* prog = loader.Parse(loader.srcData,progSize);
    LoadProgram(prog,progSize);

    _cpu.Execute();    

    std::cin.get();

    return 0;
}
