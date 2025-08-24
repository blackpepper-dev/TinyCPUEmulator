#include "emu_cpu.h"

//<========================================CPU FUNCTIONS========================================>

Emu_CPU _cpu; //Global struct variable

void Emu_CPU::ALU_OP(uint8_t &regref, uint8_t op, uint8_t value)
{
    uint16_t res = 0;

    switch (op)
    {
        case ALU_OP_ADD: res = regref + value;break;
        case ALU_OP_SUB: res = regref - value;break;
        case ALU_OP_MUL: res = regref * value;break;
        case ALU_OP_DIV:
        {
            if(value == 0) 
            {
                std::cout << "Error: divison by zero!!!\n";
                return;
            }

            res = regref / value;
            break;        
        }
            
        default:
            break;
    }

    regref = static_cast<uint8_t>(res & 0xFF);
    SR.overflow = (res > 0xFF) ? 0x01 : 0x00; //set flag if res > 0xFF  

}

uint8_t Emu_CPU::GetRegisterValue(uint8_t reg)
{
    switch(reg) 
    {
        case _registrs::A: return A;
        case _registrs::B: return B;
        case _registrs::C: return C;
        case _registrs::D: return D;
        default: std::cout << "Unknown register\n"; return 0;
    }
}

uint8_t& Emu_CPU::GetRegisterRef(uint8_t reg_id) {
   switch (reg_id)
   {
        case _registrs::A: return A;
        case _registrs::B: return B;
        case _registrs::C: return C;
        case _registrs::D: return D;
        default: std::cout << "Unknown register!!!";
         return A;
        break;
   }
};

void Emu_CPU::InitCPU()
{
    A = 0x00;
    B = 0x00;
    C = 0x00;
    D = 0x00;    
    PC = 0x00;   
    halted = false;

    for (size_t i = 0; i < sizeof(Memory.memory);i++)
        Memory.memory[i] = 0x00;

    Decoder.BindMemory(Memory);

}

void Emu_CPU::DUMP_CPU()
{

    std::cout << "\n================== CPU DUMP ==================\n";

    // Registers
    std::cout << "Registers:\n";
    std::cout << "  A: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)A;
    std::cout << "  B: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)B;
    std::cout << "  C: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)C;
    std::cout << "  D: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)D << "\n";

    // Counters and status
    std::cout << "\nCounters & Flags:\n";    
    std::cout << " PC (Program Counter): 0x" << std::hex << (int)PC << "\n";
    std::cout << " SR (Status Register):\n";
    std::cout << "  | Overflow Flag : " << ((SR.overflow & 0x01) ? "OVERFLOW" : "OK") << "\n";
    std::cout << "  | Carry Flag    : " << ((SR.carry & 0x01)    ? "CARRY"    : "OK") << "\n";
    std::cout << "  | Zero Flag     : " << ((SR.zero & 0x01)     ? "ZERO"     : "OK") << "\n";

    std::cout << "\nSegments:\n";
    std::cout << " Code Segment (CS): 0x" << std::hex << (int)_cpu.Memory.CS << "\n";
    std::cout << " Data Segment (DS): 0x" << std::hex << (int)_cpu.Memory.DS << "\n";

    // Short memory dump
    std::cout << "\nCode Segment Snapshot (0x00 - 0x3F):\n";
    for (int i = 0x00; i < 0x40; i += 8) {
        std::cout << "  0x" << std::hex << std::setw(3) << i << ": ";
        for (int j = 0; j < 8; ++j) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)_cpu.Memory.Read(i + j) << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nData Segment Snapshot (0x100 - 0x13F):\n";
    for (int i = _cpu.Memory.DS; i < _cpu.Memory.DS + 0x40; i += 8) {
        std::cout << "  0x" << std::hex << std::setw(3) << i << ": ";
        for (int j = 0; j < 8; ++j) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)_cpu.Memory.Read(i + j) << " ";
        }
        std::cout << "\n";
    }

    // Last three instructions
    std::cout << "\nLast Instructions at PC:\n";
    for (int i = 0; i < 3; ++i) {
        int addr = PC + i;
        std::cout << "  [0x" << std::hex << addr << "] = 0x"
                  << std::setw(2) << std::setfill('0') << (int)_cpu.Memory.Read(addr) << "\n";
    }

    std::cout << "=============================================\n\n";

}

void Emu_CPU::Execute()
{
    while(!Tick())
        Decoder.Decode(*this);
}

//<=============================================================================================>