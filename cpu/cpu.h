#include "../memory/memory.h"
#pragma once

struct Registers {
    u8 A; // Accumulator
    u16 X, Y; // General purpose registers
    u16 PC; // Program Counter
    u8 P; // Processor Status Register
    u8 IR; // Instruction Register
    u16 DBR; // Data Bank Register
    u16 PBR; // Program Bank Register
    u16 S; // Stack Pointer

    u8 FLAG_N;
    u8 FLAG_V;
    u8 FLAG_B; 
    u8 FLAG_D; 
    u8 FLAG_I; 
    u8 FLAG_Z; 
    u8 FLAG_C; 

    void reset() {
        A = P = IR = 0;
        X = Y = DBR = PBR = PC = 0;
        S = STACK_BASE_ADDRESS + STACK_SIZE - 1;
    }

    void resetFlags() {
        FLAG_N = 0x80;
        FLAG_V = 0x40;
        FLAG_B = 0x10;
        FLAG_D = 0x08;
        FLAG_I = 0x04;
        FLAG_Z = 0x02;
        FLAG_C = 0x01;
    }
};

class CPU {

    protected:
        CPU(const std::string value): value_(value) {}
        static CPU* cpu_;

        std::string value_;

    public:
        CPU(CPU &other) = delete;
        void operator = (const CPU &) = delete;
        static CPU *GetInstance(const std::string &value);

        Registers* registers;
        Memory* memory = Memory::GetInstance("main");

        CPU() {
            this->registers->reset();
            this->registers->resetFlags();
        }
        void executeInstruction(u8 opcode);
        void setFlag(u8 flag, bool value);

        // Instructions
        void ADC(u16 address);
};