#include "../cpu/cpu.h"
#pragma once

// Class Stack abstraction of real nes stack
// Using Singleton pattern

class Stack {

    protected:
        Stack(const std::string value): value_(value) {}
        static Stack* stack_;

        std::string value_;
    
    public:
        Stack(Stack &other) = delete;

        CPU* cpu = CPU::GetInstance("main");
        Memory* memory = Memory::GetInstance("main");

        void operator = (const Stack &) = delete;

        static Stack *GetInstance(const std::string &value);
        
        void dump();
        void pushStack(u8 value);
        u8 popStack();
};