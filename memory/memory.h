#include "memory.cpp"

Memory *Memory::memory_ = nullptr;

Memory *Memory::GetInstance(const std::string &value) {
    
    if (memory_ == nullptr) {
        memory_ = new Memory(value);
    }

    return memory_;
}
