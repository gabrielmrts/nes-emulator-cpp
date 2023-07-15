#include "memory.h"

Memory *Memory::memory_ = nullptr;

Memory *Memory::GetInstance(const std::string &value) {
    
    if (memory_ == nullptr) {
        memory_ = new Memory(value);
    }

    return memory_;
}

void Memory::dump() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        std::cout << "Address: 0x" << std::hex << i << ", Value: 0x" << std::hex << static_cast<int>(raw[i]) << std::endl;
    }
}

void Memory::write(u16 address, u8 value) {
    raw[address] = value;
}

u8 Memory::read(u16 address) {
    return raw[address];
}

void Memory::loadRom(const std::string& romFilename) {
    std::ifstream romFile(romFilename, std::ios::binary);
    
    if (!romFile) {
        std::cerr << "Erro ao abrir o arquivo ROM." << std::endl;
        return;
    }

    romFile.read(reinterpret_cast<char*>(raw), MEMORY_SIZE);
}

std::string Memory::value() const {
    return value_;
}