#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "emu_program.h"


struct Emu_Program;

struct Emu_Loader
{

   std::string srcData; 

   void LoadSource(const std::string filename);
   Emu_Program* Parse(std::string source);  
    
};
