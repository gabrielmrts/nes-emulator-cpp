#include "cpu.h"

CPU* CPU::cpu_ = nullptr;

CPU* CPU::GetInstance(const std::string &value) {
    if (cpu_ == nullptr) {
        cpu_ = new CPU(value);
    }

    return cpu_;
}

void CPU::executeInstruction(u8 opcode) {
    switch (opcode) {
        case 0x00:
            this->registers->PC += 2;
            break;
        default:
            break;
    }
}

void CPU::setFlag(u8 flag, bool value) {
    if (value) {
        this->registers->P |= flag;
    } else {
        this->registers->P &= ~flag;
    }
}

void CPU::ADC(u16 address)
{
    u8 value = this->memory->read(address); 
    u16 sum = this->registers->A + value + (this->registers->P & this->registers->FLAG_C); 
    
    setFlag(this->registers->FLAG_N, sum & 0x80); 
    setFlag(this->registers->FLAG_V, (~(this->registers->A ^ value) & (this->registers->A ^ sum)) & 0x80); 
    setFlag(this->registers->FLAG_Z, (sum & 0xFF) == 0);  
    setFlag(this->registers->FLAG_C, sum > 0xFF);

    this->registers->A = sum & 0xFF; 
    this->registers->PC += 2; 
}
