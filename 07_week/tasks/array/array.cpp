#include <initializer_list>
#include <utility>
template<typename T, size_t N>
class Array {
public:
    Array() = default;
    ~Array() = default;
    Array(std::initializer_list<T> list);
    Array(const Array& other);
    Array(Array&& other);
    Array& operator=(const Array& other);
    Array& operator=(Array&& other);
    size_t Size() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    const T& Front() const;
    T& Front();
    const T& Back() const;
    T& Back();
    const T* Data() const;
    T* Data();
    bool Empty() const;
    void Fill(T&& element);
    void Swap(Array& other);
    T* begin();
    T* end();
    const T* cbegin() const;
    const T* cend() const;
private:
    T data[N];
};
// Конструктор от initializer_list
template<typename T, size_t N>
Array<T,N>::Array(std::initializer_list<T> list) {
    size_t i = 0;
    for (const T& item : list) {
        if (i >= N) break;
        data[i++] = item;
    }
}
// Конструктор копирования
template<typename T, size_t N>
Array<T,N>::Array(const Array& other) {
    for (size_t i = 0; i < N; ++i) {
        data[i] = other.data[i];
    }
}
// Конструктор перемещения
template<typename T, size_t N>
Array<T,N>::Array(Array&& other) {
    for (size_t i = 0; i < N; ++i) {
        data[i] = std::move(other.data[i]);
    }
}
// Оператор присваивания копированием
template<typename T, size_t N>
Array<T,N>& Array<T, N>::operator=(const Array& other) {
    if (this != &other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = other.data[i];
        }
    }
    return (*this);
}
// Оператор присваивания перемещением
template<typename T, size_t N>
Array<T,N>& Array<T, N>::operator=(Array&& other) {
    if (this != &other) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = std::move(other.data[i]);
        }
    }
    return (*this);
}

//Операторы индексирования
template<typename T, size_t N>
T& Array<T,N>::operator[](size_t index) {
    return const_cast<T&>(
        static_cast<const Array&>(*this).data[index]
        );
}

template<typename T, size_t N>
const T& Array<T,N>::operator[](size_t index) const {
        return data[index];
}
// Метод Size
template<typename T, size_t N>
size_t Array<T, N>::Size() const {
    return N;
}
// Метод Front
template<typename T, size_t N>
T& Array<T, N>::Front() {
    return const_cast<T&>(
        static_cast<const Array&>(*this).data[0]
        );
}

template<typename T, size_t N>
const T& Array<T, N>::Front() const {
    return data[0];
}
// Метод Back
template<typename T, size_t N>
T& Array<T, N>::Back() {
    return const_cast<T&>(
        static_cast<const Array&>(*this).data[N - 1]
        );
}

template<typename T, size_t N>
const T& Array<T, N>::Back() const {
    return data[N - 1];
}

// Метод Data
template<typename T, size_t N>
T* Array<T, N>::Data() {
    return const_cast<T*>(
        static_cast<const Array&>(*this).Data()
        );
}
template<typename T, size_t N>
const T* Array<T, N>::Data() const {
    return data;
}
// Метод Empty
template<typename T, size_t N>
bool Array<T, N>::Empty() const {
    return (N == 0);
}
// Метод Fill
template<typename T, size_t N>
void Array<T, N>::Fill(T&& element) {
    for (size_t i = 0; i < N; ++i) {
        data[i] = element;
    }
}
// Метод Swap
template<typename T, size_t N>
void Array<T, N>::Swap(Array& other) {
    Array temp = std::move(*this);
    (*this) = std::move(other);
    other = std::move(temp);
}
// Методы begin и end (для range-based for)
template<typename T, size_t N>
T* Array<T, N>::begin() {
    return data;
}
template<typename T, size_t N>
T* Array<T, N>::end() {
    return data + N;
}
template<typename T, size_t N>
const T* Array<T, N>::cbegin() const {
    return data;
}
template<typename T, size_t N>
const T* Array<T, N>::cend() const {
    return data + N;
}
// Внешние функции
// Оператор сравнения
template<typename T, size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}
// Оператор неравенства
template<typename T, size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}
// Операторы сравнения
//<
template<typename T, size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (size_t i = 0; i < N; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (rhs[i] < lhs[i]) return false;
    }
    return false;
}
//<=
template<typename T, size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}
//>
template<typename T, size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return (rhs < lhs);
}
//>=
template<typename T, size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs > lhs);
}
// swap
template<typename T, size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) {
    lhs.Swap(rhs);
}
// get
template<size_t I, typename T, size_t N>
T&& get(Array<T, N>&& arr) {
    return std::move(arr[I]);
}
template<size_t I, typename T, size_t N>
T& get(Array<T, N>& arr) {
    return arr[I];
}
template<size_t I, typename T, size_t N>
const T& get(const Array<T, N>& arr) {
    return arr[I];
}


