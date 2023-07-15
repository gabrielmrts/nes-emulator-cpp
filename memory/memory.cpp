#include "../types.cpp"
#include "../constants.cpp"
#include <iomanip>

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
        static Memory *GetInstance(const std::string &value);

        u8 raw[MEMORY_SIZE];

        void dump() {
            for (int i = 0; i < MEMORY_SIZE; ++i) {
                std::cout << "Address: 0x" << std::hex << i << ", Value: 0x" << std::hex << static_cast<int>(raw[i]) << std::endl;
            }
        }

        void write(u16 address, u8 value) {
            raw[address] = value;
        }

        u8 read(u16 address) {
            return raw[address];
        }

        void loadRom(const std::string& romFilename) {
            std::ifstream romFile(romFilename, std::ios::binary);
            
            if (!romFile) {
                std::cerr << "Erro ao abrir o arquivo ROM." << std::endl;
                return;
            }

            romFile.read(reinterpret_cast<char*>(raw), MEMORY_SIZE);
        }

        std::string value() const {
            return value_;
        }
};