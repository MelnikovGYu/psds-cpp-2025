#include <string>


class UniquePtr {
public:
    UniquePtr() = default;
    UniquePtr(std::string* str);
    UniquePtr(const UniquePtr&) = delete; // Уникальное владение: нельзя копировать
    UniquePtr& operator=(const UniquePtr&) = delete; // Уникальное владение: нельзя копировать
    UniquePtr(UniquePtr&& other);
    UniquePtr& operator=(UniquePtr&& other);
    std::string& operator*() const;
    std::string* operator->() const;
    operator bool() const;
    ~UniquePtr();
    std::string* Get();
    std::string* Release();
    void Reset(std::string* new_str = nullptr);
    void Swap(UniquePtr& other);
private:
    std::string* raw_ptr_ = nullptr;
};

UniquePtr::UniquePtr(std::string* str) : raw_ptr_(str) {}
UniquePtr::UniquePtr(UniquePtr&& other) {
    raw_ptr_ = other.raw_ptr_;
    other.raw_ptr_ = nullptr;
}
UniquePtr& UniquePtr::operator=(UniquePtr&& other) {
    if (raw_ptr_ != other.raw_ptr_) {
        delete raw_ptr_;
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = nullptr;
    }
    return (*this);
}
std::string& UniquePtr::operator*() const {return *raw_ptr_;}
std::string* UniquePtr::operator->() const {return raw_ptr_;}
UniquePtr::~UniquePtr() {
    delete raw_ptr_;
}
std::string* UniquePtr::Get() {
    return raw_ptr_;
}
std::string* UniquePtr::Release() {
    std::string* new_ptr = raw_ptr_;
    raw_ptr_ = nullptr;
    return new_ptr;
}
void UniquePtr::Reset(std::string* new_str) {
    if (raw_ptr_ != new_str) {
        delete raw_ptr_;
        raw_ptr_ = new_str;
    }
}
void UniquePtr::Swap(UniquePtr& other) {
    if (this != &other) {
        std::string* new_ptr = raw_ptr_;
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = new_ptr;
    }
}
UniquePtr::operator bool() const {
    return raw_ptr_ != nullptr;
}

// внешние функции
void Swap(UniquePtr& lhs, UniquePtr& rhs) {
    UniquePtr temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}
UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}
