#include <string>

struct Node {
    std::string str_;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node() = default;
    Node(const std::string& str) : str_(str) {}
    Node(std::string&& str) : str_(std::move(str)) {}
};

class SimpleList {
public:
    SimpleList() {}
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other);
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other);
    ~SimpleList();
    void Swap(SimpleList& other);
    size_t Size() const;
    bool Empty() const;
    void PushBack(const std::string& str);
    void PushBack(std::string&& str);
    void PopBack();
    void PushFront(const std::string& str);
    void PushFront(std::string&& str);
    void PopFront();
    std::string& Back();
    const std::string& Back() const;
    std::string& Front();
    const std::string& Front() const;
    void Clear();

private:
    Node* first_ = nullptr;
    Node* last_ = nullptr;
    size_t size_ = 0;
    void Link(Node* new_node, Node* prev);
    void Unlink(Node* node);
};

void SimpleList::Link(Node* new_node, Node* position) { // связываем узел
    if (!position) { // вставка в начало
        new_node -> next = first_;
        new_node -> prev = nullptr;
        if (first_) first_ -> prev = new_node; // добавление new_node перед first
        else last_ = new_node; // при отсутсвии first добавление new_node
        first_ = new_node;
        return;
    }
    // вставка после position
    new_node -> next = (position -> next);
    new_node -> prev = position;
    if (!(position -> next)) last_ = new_node;
    else (position -> next) -> prev = new_node;
    position -> next = new_node;
}
void SimpleList::Unlink(Node *node) { // отвязываем узел
    if (node) {
        if (node -> prev) (node -> prev) -> next = (node -> next);
        else first_ = (node -> next); // если сзади node пусто, то следующий после node узел первый
        if (node -> next) (node -> next) -> prev = (node -> prev);
        else last_ = (node -> prev); // если спереди node пусто, то предыдущий перед node узел последний
    }
}
void SimpleList::PushBack(const std::string& str) {
    Node* new_node = new Node(str);
    SimpleList::Link(new_node, last_);
    ++size_;
}
void SimpleList::PushBack(std::string&& str) {
    Node* new_node = new Node(std::move(str));
    SimpleList::Link(new_node, last_);
    ++size_;
}
void SimpleList::PushFront(const std::string& str) {
    Node* new_node = new Node(str);
    SimpleList::Link(new_node, nullptr);
    ++size_;
}
void SimpleList::PushFront(std::string&& str) {
    Node* new_node = new Node(std::move(str));
    SimpleList::Link(new_node, nullptr);
    ++size_;
}

void SimpleList::PopBack() {
    if (!last_) return;
    Node* temp = last_;
    SimpleList::Unlink(last_);
    delete temp;
    --size_;
}
void SimpleList::PopFront() {
    if (!first_) return;
    Node* temp = first_;
    SimpleList::Unlink(first_);
    delete temp;
    --size_;
}

SimpleList::SimpleList(const SimpleList& other) {
    Node* temp_node = other.first_;
    while (temp_node) {
        PushBack(temp_node -> str_);
        temp_node = temp_node -> next;
    }
}

SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        Clear(); // Очищаем старые данные
        // Создаем новые узлы
        Node* temp_node = other.first_;
        while (temp_node) {
            PushBack(temp_node -> str_);
            temp_node = temp_node -> next;
        }
    }
    return *this;
}

SimpleList::SimpleList(SimpleList&& other) {
    size_ = other.size_;
    first_ = other.first_;
    last_ = other.last_;
    other.size_ = 0;
    other.first_ = nullptr;
    other.last_ = nullptr;
}

SimpleList::~SimpleList() {
    Clear();
}

SimpleList& SimpleList::operator=(SimpleList&& other) {
    if (this != &other) {
        Clear(); // Очищаем старые данные
        size_ = other.size_;
        first_ = other.first_;
        last_ = other.last_;
        other.size_ = 0;
        other.first_ = nullptr;
        other.last_ = nullptr;
    }
    return *this;
}
size_t SimpleList::Size() const {
    return size_;
}
bool SimpleList::Empty() const {
    return (size_ == 0);
}
void SimpleList::Clear() {
    while (last_) {
        PopBack();
    }
}
std::string& SimpleList::Back() {
    return const_cast<std::string&>(
        static_cast<const SimpleList&>(*this).Back()
        );
}
const std::string& SimpleList::Back() const {
    return (last_ -> str_);
}
std::string& SimpleList::Front() {
    return const_cast<std::string&>(
        static_cast<const SimpleList&>(*this).Front()
        );
}
const std::string& SimpleList::Front() const {
    return (first_ -> str_);
}
void SimpleList::Swap(SimpleList& other) {
    if (this != &other) {
        SimpleList buffer = std::move(*this);
        (*this) = std::move(other);
        other = std::move(buffer);
    }
}
// внешние функции
void Swap(SimpleList& lhs, SimpleList& rhs) {
    SimpleList temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}
