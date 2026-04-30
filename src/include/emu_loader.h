#pragma once



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "emu_program.h"
#include "emu_enums.h"

struct Emu_Program;
struct Emu_Cpu;

struct Emu_Loader
{

   std::string srcData; 

   void LoadSource(const std::string filename);
   Emu_Program* Parse(const std::string& source, size_t& outCount);
    
};
