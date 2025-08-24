#pragma once

enum _opcodes : uint8_t
{
    NOP   = 0x00, //do nothing
    MVI   = 0x01, //Move value to register (A,B,C,D)
    MOV   = 0x02, //Move from register #2 to register #1 
    ADI   = 0x03, //Register + literal 
    ADD   = 0x04, //Register + register
    SUI   = 0x05, //Register - literal    
    SUB   = 0x06, //Register #1 - register #2
    MLI   = 0x07, //Register * literal
    MUL   = 0x08, //Register #1 * register #2
    DVI   = 0x09, //Register / literal
    DIV   = 0xA, //Register / register
    SAV   = 0xB, // Save in memory DS(0x200) + literal -> 0x??  
    OUT   = 0xC, // Output from memory DS(0x200) + literal - > res
    CMP   = 0xD, // Compare A & literal
    JMP   = 0xF, // Jump to _cpu.memory[_cpu.CS + literal] (go to)
    HLT   = 0xFF //Halt execution
};

enum _registrs : uint8_t 
{
    A = 0x00,
    B = 0x01,
    C = 0x02,
    D = 0x03
};

enum _alu_ops : uint8_t
{
    ALU_OP_ADD = 0x00,
    ALU_OP_SUB = 0x01,
    ALU_OP_MUL = 0x02,
    ALU_OP_DIV = 0x03
};