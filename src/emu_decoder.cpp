#include "include/emu_decoder.h"
#include "include/emu_cpu.h"

void Emu_Decoder::CommandRow(uint8_t opcode, uint8_t reg, uint8_t operand)
{
    if(CC < mem->DS)
    {
        mem->Write(CC++, opcode);
        mem->Write(CC++, reg);
        mem->Write(CC++, operand);
    }
}

void Emu_Decoder::CommandRow(uint8_t opcode, uint8_t operand)
{
    if(CC < mem->DS)
    {
        mem->Write(CC++, opcode);
        mem->Write(CC++, 0x00);   
        mem->Write(CC++, operand);    
    }
}

void Emu_Decoder::CommandRow(uint8_t opcode)
{
    if(CC < mem->DS)
    {
        mem->Write(CC++, opcode);
        mem->Write(CC++, 0x00);  
        mem->Write(CC++, 0x00);              
    }
}

void Emu_Decoder::Decode(Emu_CPU& cpu)
{
   uint8_t opcode   = cpu.Memory.Read(cpu.PC);
   uint8_t operand1 = cpu.Memory.Read(cpu.PC + 1);
   uint8_t operand2 = cpu.Memory.Read(cpu.PC + 2);

   if(cpu.halted) return;   

   switch (opcode)
   {

    case MVI:
    {
        cpu.GetRegisterRef(operand1) = operand2;
        cpu.PC +=3;                     
        break;
    }

    case MOV:
    {

        cpu.GetRegisterRef(operand1) = cpu.GetRegisterValue(operand2);        
        cpu.PC +=3;                     
        break;
    }

    case ADI:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_ADD,operand2);         
        cpu.PC += 3;    
        break;
    }

    case ADD:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_ADD,cpu.GetRegisterValue(operand2)); break;            
        cpu.PC += 3;    
        break;
    }

    case SUI:
    { 
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_SUB,operand2); break;            
        cpu.PC += 3;    
        break;
    }

    case SUB:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_SUB,cpu.GetRegisterValue(operand2)); break;            
        cpu.PC += 3;    
        break;
    }

    case MLI:
    { 
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_MUL,operand2); break;            
        cpu.PC += 3;    
        break;     
    }

    case MUL:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_MUL,cpu.GetRegisterValue(operand2)); break;            
        cpu.PC += 3;    
        break;
    }

    case DVI:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_DIV,operand2); break;            
        cpu.PC += 3;    
        break;
    }

    case DIV:
    {
        cpu.ALU_OP(cpu.GetRegisterRef(operand1),ALU_OP_DIV,cpu.GetRegisterValue(operand2)); break;            
        cpu.PC += 3;    
        break;
    }
 
    case SAV:
    {
         cpu.Memory.Write(cpu.Memory.DS + operand2, cpu.GetRegisterValue(operand1));
         cpu.PC +=3;         
         break;
    }

    case OUT:
    {
         std::cout << "OUT:" << (int)cpu.Memory.Read(cpu.Memory.DS + operand2) << std::endl;
         cpu.PC += 3;
         break;
    }

    case JMP:cpu.PC = operand2 * 3;break; 

    case HLT:cpu.halted = true;break;

    case NOP:cpu.PC += 1;break;    
    
   default: std::cout << "Unknown opcode!!!!\n";
    break;
   }
    
}
