#include "cpu.cpp"

CPU* CPU::cpu_ = nullptr;

CPU* CPU::GetInstance(const std::string &value) {
    if (cpu_ == nullptr) {
        cpu_ = new CPU(value);
    }

    return cpu_;
}

void CPU::reset() {
    this->registers->reset();
}

void CPU::executeInstruction(u8 opcode) {
    switch (opcode) {
        case 0x00:
            this->registers->PC += 2;
            break;

        case 0x18:
            this->registers->P &= ~0x01;
            break;

        case 0x20:
            u16 address = 0x0;
            break;

        case 0x6D: // ADC a
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
