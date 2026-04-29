#include "include/emu_cpu.h"

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
                Logger.LogError("Error: divison by zero!!!");
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
        default:
            Logger.LogError("Invalid register reference in Emu_CPU::GetRegisterValue");
            throw std::invalid_argument("Invalid register reference in Emu_CPU::GetRegisterValue");

    }
}

uint8_t& Emu_CPU::GetRegisterRef(uint8_t reg_id) {
    switch (reg_id) {
        case _registrs::A: return A;
        case _registrs::B: return B;
        case _registrs::C: return C;
        case _registrs::D: return D;
        default:
            Logger.LogError("Invalid register reference in Emu_CPU::GetRegisterRef");
            throw std::invalid_argument("Invalid register reference in Emu_CPU::GetRegisterRef");
    }

}

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
    std::ostringstream oss;

    oss << "\n================== CPU DUMP ==================\n";
    Logger.LogInfo(oss.str());

    // Registers
    oss.str(""); oss.clear();
    oss << "\nRegisters:\n"
        << "  A: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)A << "\n"
        << "  B: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)B << "\n"
        << "  C: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)C << "\n"
        << "  D: 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)D;
    Logger.LogInfo(oss.str());

    // Counters
    oss.str(""); oss.clear();
    oss << " PC (Program Counter): 0x"
        << std::hex << std::setw(2) << std::setfill('0') << (int)PC;
    Logger.LogInfo(oss.str());

    // Flags
    oss.str(""); oss.clear();
    oss << " SR (Status Register):\n"
        << "  | Overflow Flag : " << ((SR.overflow & 0x01) ? "OVERFLOW" : "OK") << "\n"
        << "  | Carry Flag    : " << ((SR.carry & 0x01)    ? "CARRY"    : "OK") << "\n"
        << "  | Zero Flag     : " << ((SR.zero & 0x01)     ? "ZERO"     : "OK");
    Logger.LogInfo(oss.str());

    // Segments
    oss.str(""); oss.clear();
    oss << " Code Segment (CS): 0x" << std::hex << (int)_cpu.Memory.CS << "\n"
        << " Data Segment (DS): 0x" << std::hex << (int)_cpu.Memory.DS;
    Logger.LogInfo(oss.str());

    // Code Segment Snapshot
    Logger.LogInfo("\nCode Segment Snapshot (0x00 - 0x3F):");
    for (int i = 0x00; i < 0x40; i += 8) {
        oss.str(""); oss.clear();
        oss << "  0x" << std::hex << std::setw(2) << i << ": ";
        for (int j = 0; j < 8; ++j) {
            oss << "0x" << std::hex << std::setw(2) << std::setfill('0')
                << (int)_cpu.Memory.Read(i + j) << " ";
        }
        Logger.LogInfo(oss.str());
    }

    // Data Segment Snapshot
    Logger.LogInfo("\nData Segment Snapshot (0x100 - 0x13F):");
    for (int i = _cpu.Memory.DS; i < _cpu.Memory.DS + 0x40; i += 8) {
        oss.str(""); oss.clear();
        oss << "  0x" << std::hex << std::setw(3) << i << ": ";
        for (int j = 0; j < 8; ++j) {
            oss << "0x" << std::hex << std::setw(2) << std::setfill('0')
                << (int)_cpu.Memory.Read(i + j) << " ";
        }
        Logger.LogInfo(oss.str());
    }

    // Last Instructions
    Logger.LogInfo("\nLast Instructions at PC:");
    for (int i = 0; i < 3; ++i) {
        int addr = PC + i;
        oss.str(""); oss.clear();
        oss << "  [0x" << std::hex << addr << "] = 0x"
            << std::setw(2) << std::setfill('0') << (int)_cpu.Memory.Read(addr);
        Logger.LogInfo(oss.str());
    }

    Logger.LogInfo("=============================================\n\n");
}


void Emu_CPU::Execute()
{
    while(!Tick())
        Decoder.Decode(*this);
}

//<=============================================================================================>