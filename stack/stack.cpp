#include "../cpu/cpu.cpp"

// Class Stack abstraction of real nes stack
// Using Singleton pattern

class Stack {

    protected:
        Stack(const std::string value): value_(value) {}
        static Stack* stack_;

        std::string value_;
    
    public:
        Stack(Stack &other) = delete;

        CPU s_cpu;
        CPU* cpu = &s_cpu;
        Memory* memory = Memory::GetInstance("main");

        void operator = (const Stack &) = delete;

        static Stack *GetInstance(const std::string &value);

        void dump() {
            for (int i = 0; i < MEMORY_SIZE; ++i) {
                std::cout << "Stack address 0x" << std::hex << i << ": " << std::hex << static_cast<int>(memory->raw[i]) << std::endl;
            }
        }       

        void pushStack(u8 value) {
            if (cpu->S >= STACK_BASE_ADDRESS) {
                memory->raw[cpu->S] = value;
                cpu->S--;
            } else {
                std::cerr << "Error: Stack overflow" << std::endl;
            }
        }

        u8 popStack() {
            if (cpu->S < STACK_BASE_ADDRESS + STACK_SIZE) {
                cpu->S++;
                return memory->raw[cpu->S];
            } else {
                return 0xFF;
            }
        }
};