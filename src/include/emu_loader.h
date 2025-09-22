#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "emu_enums.h"
#include "emu_program.h"
#include "emu_memory.h"

struct Emu_Program;

struct Emu_Loader
{

   std::string srcData; 

   void LoadSource(const std::string filename);
   Emu_Program* Parse(std::string source);  
    
};
