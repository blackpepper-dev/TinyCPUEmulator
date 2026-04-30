#include "include/emu_loader.h"
#include "include/emu_cpu.h"



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
        Logger.LogError("Error while opening file " + filename);
        return;
    }

   
} 

std::string trim(const std::string& s)
{
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n'))
        ++start;

    size_t end = s.size();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\r' || s[end - 1] == '\n'))
        --end;

    return s.substr(start, end - start);
}


Emu_Program* Emu_Loader::Parse(const std::string& source, size_t& outCount)
{
    std::istringstream iss(source);
    std::string line;

    Emu_Program* program = new Emu_Program[source.size()];
    size_t count = 0;

    bool inData = false;    

    while (std::getline(iss, line) && count < source.size()) 
    {
       
        line = trim(line);
        if (line.empty()) continue;
        
        if (line == ".data") { inData = true; continue; }
        if (line == ".code") { inData = false; continue; }

        std::istringstream ls(line);

        if (inData) 
        {
            char reg; char eq; int val;
            ls >> reg >> eq >> val;

            switch(reg) 
            {
                case 'A': _cpu.A = val; break;
                case 'B': _cpu.B = val; break;
                case 'C': _cpu.C = val; break;
                case 'D': _cpu.D = val; break;
            }
        }
        else {
            
            std::string op;
            ls >> op;

            if (op == "NOP") {
                program[count++] = Emu_Program(NOP);
            }
            else if (op == "HLT") {
                program[count++] = Emu_Program(HLT);
            }
            else if (op == "PRN") {
                int addr;
                ls >> addr;
                program[count++] = Emu_Program(PRN, addr);
            }
            else if (op == "JMP") {
                int addr;
                ls >> addr;
                program[count++] = Emu_Program(JMP, addr);
            }
            else if (op == "MOV") {
                char r1; char r2;
                ls >> r1 >> r2;
                program[count++] = Emu_Program(MOV,
                    (r1 == 'A' ? A : (r1 == 'B' ? B : (r1 == 'C' ? C : D))),
                    (r2 == 'A' ? A : (r2 == 'B' ? B : (r2 == 'C' ? C : D))));
            }
            else if (op == "MVI") {
                char r; int val;
                ls >> r >> val;
                program[count++] = Emu_Program(MVI,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    val);
            }
            else if (op == "ADD") {
                char r1, r2;
                ls >> r1 >> r2;
                program[count++] = Emu_Program(ADD,
                    (r1 == 'A' ? A : (r1 == 'B' ? B : (r1 == 'C' ? C : D))),
                    (r2 == 'A' ? A : (r2 == 'B' ? B : (r2 == 'C' ? C : D))));
            }
            else if (op == "ADI") {
                char r; int val;
                ls >> r >> val;
                program[count++] = Emu_Program(ADI,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    val);
            }
            else if (op == "SUB") {
                char r1, r2;
                ls >> r1 >> r2;
                program[count++] = Emu_Program(SUB,
                    (r1 == 'A' ? A : (r1 == 'B' ? B : (r1 == 'C' ? C : D))),
                    (r2 == 'A' ? A : (r2 == 'B' ? B : (r2 == 'C' ? C : D))));
            }
            else if (op == "SUI") {
                char r; int val;
                ls >> r >> val;
                program[count++] = Emu_Program(SUI,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    val);
            }
            else if (op == "MUL") {
                char r1, r2;
                ls >> r1 >> r2;
                program[count++] = Emu_Program(MUL,
                    (r1 == 'A' ? A : (r1 == 'B' ? B : (r1 == 'C' ? C : D))),
                    (r2 == 'A' ? A : (r2 == 'B' ? B : (r2 == 'C' ? C : D))));
            }
            else if (op == "MLI") {
                char r; int val;
                ls >> r >> val;
                program[count++] = Emu_Program(MLI,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    val);
            }
            else if (op == "DIV") {
                char r1, r2;
                ls >> r1 >> r2;
                program[count++] = Emu_Program(DIV,
                    (r1 == 'A' ? A : (r1 == 'B' ? B : (r1 == 'C' ? C : D))),
                    (r2 == 'A' ? A : (r2 == 'B' ? B : (r2 == 'C' ? C : D))));
            }
            else if (op == "DVI") {
                char r; int val;
                ls >> r >> val;
                program[count++] = Emu_Program(DVI,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    val);
            }
            else if (op == "SAV") {
                char r; int addr;
                ls >> r >> addr;
                program[count++] = Emu_Program(SAV,
                    (r == 'A' ? A : (r == 'B' ? B : (r == 'C' ? C : D))),
                    addr);
            }
            else {
                Logger.LogError("Unknown opcode: " + op);
            }
        }
    }

    outCount = count;
    return program;
}

