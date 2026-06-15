#include <iostream>
#include "include/emu_loader.h"
#include "include/emu_program.h"
#include "include/emu_disasm.h"
#include "include/emu_cpu.h"
#include "include/Logger.h"


int main()
{    
    
    Logger.LogToFile = true;    
    Logger.Init();

    _cpu.InitCPU();

    Emu_Loader loader;
    loader.LoadSource("source.asm");
    size_t progSize = 0;
    Emu_Program* prog = loader.Parse(loader.srcData,progSize);
    LoadProgram(prog,progSize);

    _cpu.Execute();    

    std::cin.get();

    return 0;
}
