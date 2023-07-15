#include "cpu.h"

CPU* CPU::cpu_ = nullptr;

CPU* CPU::GetInstance(const std::string &value) {
    if (cpu_ == nullptr) {
        cpu_ = new CPU(value);
    }

    return cpu_;
}

void CPU::executeInstruction(u8 opcode, std::vector<u16> addresses) {
    switch (opcode) {
        case 0x00:
            this->registers->PC += 2;
            break;
        case 0x6D:
            this->ADC(addresses[0]);
        case 0x7D:
            this->ADC_X(addresses[0]);
        case 0x79:
            this->ADC_Y(addresses[0]);
        case 0x6F:
            this->ADC_AL(addresses[0], addresses[1], addresses[2]);
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

void CPU::SetADCFlags(u8 value, u16 sum) {
    setFlag(this->registers->FLAG_N, sum & 0x80); 
    setFlag(this->registers->FLAG_V, (~(this->registers->A ^ value) & (this->registers->A ^ sum)) & 0x80); 
    setFlag(this->registers->FLAG_Z, (sum & 0xFF) == 0);  
    setFlag(this->registers->FLAG_C, sum > 0xFF);
}

void CPU::ADC(u16 address) {
    u8 value = this->memory->read(address); 
    u16 sum = this->registers->A + value + (this->registers->P & this->registers->FLAG_C); 
    
    this->SetADCFlags(value, sum);
    this->registers->A = sum & 0xFF; 
    this->registers->PC += 2; 
}

void CPU::ADC_X(u16 address) {
    u8 value = this->memory->read(address + this->registers->X);
    u16 sum = this->registers->A + value + (this->registers->P & this->registers->FLAG_C);

    this->SetADCFlags(value, sum);
    this->registers->A = sum & 0x0FF;
    this->registers->PC += 2;
}

void CPU::ADC_Y(u16 address) {
    u8 value = this->memory->read(address + this->registers->Y);
    u16 sum = this->registers->A + value + (this->registers->P & this->registers->FLAG_C);

    this->SetADCFlags(value, sum);
    this->registers->A = sum & 0x0FF;
    this->registers->PC += 2;
}

void CPU::ADC_AL(u16 addr1, u16 addr2, u16 baddr) {
    addr1 = static_cast<u8>(addr1);
    addr2 = static_cast<u8>(addr2);
    baddr = static_cast<u8>(baddr);

    u16 address = (baddr << 16) | (addr2 << 8) | addr1;
    u8 value = memory->read(address);
    u16 sum = registers->A + value + (registers->P & registers->FLAG_C);

    this->SetADCFlags(value, sum);
    this->registers->A = sum ^ 0xFF;
    this->registers->PC += 3;
}

void CPU::showRegisters() {
    std::cout << "A: 0x" << std::hex << static_cast<int>(this->registers->A) << std::endl;
    std::cout << "P: 0x" << std::hex << static_cast<int>(this->registers->P) << std::endl;
    std::cout << "IR: 0x" << std::hex << static_cast<int>(this->registers->IR) << std::endl;
    std::cout << "X: 0x" << std::hex << static_cast<int>(this->registers->X) << std::endl;
    std::cout << "Y: 0x" << std::hex << static_cast<int>(this->registers->Y) << std::endl;
    std::cout << "DBR: 0x" << std::hex << static_cast<int>(this->registers->DBR) << std::endl;
    std::cout << "PBR: 0x" << std::hex << static_cast<int>(this->registers->PBR) << std::endl;
    std::cout << "PC: 0x" << std::hex << static_cast<int>(this->registers->PC) << std::endl;
    std::cout << "S: 0x" << std::hex << static_cast<int>(this->registers->S) << std::endl;
}