#include <iostream>
#include <fstream>
#include <unistd.h>
#include "stack/stack.h"
#include "cpu/cpu.h"
#include "memory/memory.h"

using namespace std;

int main(int argc, const char* argv[]) {

    Memory* memory = Memory::GetInstance("main");
    memory->loadRom("chrono.smc");

    CPU* cpu = CPU::GetInstance("main");
    cpu->memory = memory;

    Stack* stack = Stack::GetInstance("main");
    
    cpu->memory->write(0x1000, 0x10);
    cpu->registers->A = 0x20;
    cpu->executeInstruction(0x6D, {0x1000});
    cpu->showRegisters();

    return 0;

}   