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

        void dump() {
            for (int i = 0; i < MEMORY_SIZE; ++i) {
                std::cout << "Stack address 0x" << std::hex << i << ": " << std::hex << static_cast<int>(memory->raw[i]) << std::endl;
            }
        }       

        void pushStack(u8 value) {
            if (cpu->registers->S >= STACK_BASE_ADDRESS) {
                memory->raw[cpu->registers->S] = value;
                cpu->registers->S--;
            } else {
                std::cerr << "Error: Stack overflow" << std::endl;
            }
        }

        u8 popStack() {
            if (cpu->registers->S < STACK_BASE_ADDRESS + STACK_SIZE) {
                cpu->registers->S++;
                return memory->raw[cpu->registers->S];
            } else {
                return 0xFF;
            }
        }
};