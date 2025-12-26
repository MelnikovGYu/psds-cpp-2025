#include <vector>



class Stack {
public:
    void Push(int value);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);
    bool operator==(const Stack& other) const{
        auto stack1 = (*this).stack_;
        auto stack2 = other.stack_;
        if (stack1.size() != stack2.size()) return false;
        for (size_t i = 0; i < stack1.size(); ++i){
            if (stack1[i] != stack2[i]) return false;
        }
        return true;
    }
    bool operator!=(const Stack& other) const{
        return !(*this == other);
    }
private:
    std::vector<int> stack_;
};

void Stack::Push(int value){
    stack_.push_back(value);
}
bool Stack::Pop(){
    if (stack_.empty()) return false;
    stack_.pop_back();
    return true;
}
const int& Stack::Top() const {
    return stack_.back();
}
int& Stack::Top() {
    return stack_.back();
}
bool Stack::Empty() const{
    return stack_.empty();
}
size_t Stack::Size() const{
    return stack_.size();
}
void Stack::Clear(){
    stack_.clear();
    stack_.shrink_to_fit();
}
void Stack::Swap(Stack& other){
    stack_.swap(other.stack_);
}

