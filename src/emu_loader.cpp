#include "include/emu_loader.h"



void Emu_Loader::LoadSource(const std::string filename)
{
    std::ifstream srcFile(filename,std::ios::in | std::ios::binary);
    std::string line;

    if(srcFile.is_open())
    {
        while(std::getline(srcFile,line))
            srcData += line + '\n';
    }
    else
    {
        std::cout << "Error while opening file " << filename << std::endl;
        return;
    }

   
}
  


Emu_Program* Emu_Loader::Parse(std::string source)
{
    
    Emu_Program *program = new Emu_Program(source.size());

    std::replace(source.begin(), source.end(), ' ', '\n');  
    
    
}