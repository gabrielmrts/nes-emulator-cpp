#include "stack.h"

Stack *Stack::stack_ = nullptr;

Stack *Stack::GetInstance(const std::string &value) {
    
    if (stack_ == nullptr) {
        stack_ = new Stack(value);
    }

    return stack_;
}

void Stack::dump() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        std::cout << "Stack address 0x" << std::hex << i << ": " << std::hex << static_cast<int>(memory->raw[i]) << std::endl;
    }
}       

void Stack::pushStack(u8 value) {
    if (cpu->registers->S >= STACK_BASE_ADDRESS) {
        memory->raw[cpu->registers->S] = value;
        cpu->registers->S--;
    } else {
        std::cerr << "Error: Stack overflow" << std::endl;
    }
}

u8 Stack::popStack() {
    if (cpu->registers->S < STACK_BASE_ADDRESS + STACK_SIZE) {
        cpu->registers->S++;
        return memory->raw[cpu->registers->S];
    } else {
        return 0xFF;
    }
}