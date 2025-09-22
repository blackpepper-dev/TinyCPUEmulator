#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "include/emu_program.h"

struct Emu_Program;

struct Emu_Loader
{

   std::string srcData; 

   void LoadSource(const std::string filename);
   Emu_Program* Parse(const std::string source);  

   void NormStr(std::string source)
   {
     std::replace(source.begin(), source.end(), ' ', '\n');
     std::cout << source;
   }
   
    
};
