#include <iostream>
#include <fstream>
#include <unistd.h>
#include "stack/stack.h"

using namespace std;

int main(int argc, const char* argv[]) {

    Memory* memory = Memory::GetInstance("main");
    memory->loadRom("chrono.smc");

    CPU* cpu = CPU::GetInstance("main");
    cpu->memory = memory;
    cpu->reset();

    Stack* stack = Stack::GetInstance("main");

    return 0;

}   