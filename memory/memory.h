#include "../types.cpp"
#include "../constants.cpp"
#include <iomanip>
#pragma once

// Class Memory abstraction of real nes memory
// Using Singleton pattern 

class Memory {

    protected:
        Memory(const std::string value): value_(value) {}
        static Memory* memory_;

        std::string value_;

    public:

        Memory(Memory &other) = delete;
        void operator = (const Memory &) = delete;
        static Memory* GetInstance(const std::string &value);

        u8 raw[MEMORY_SIZE];

        void dump();

        void write(u16 address, u8 value);
        u8 read(u16 address);
        int readInt(u16 address);
        void loadRom(const std::string& romFilename);
        std::string value() const;
};