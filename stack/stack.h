#include "stack.cpp"

Stack *Stack::stack_ = nullptr;

Stack *Stack::GetInstance(const std::string &value) {
    
    if (stack_ == nullptr) {
        stack_ = new Stack(value);
    }

    return stack_;
}