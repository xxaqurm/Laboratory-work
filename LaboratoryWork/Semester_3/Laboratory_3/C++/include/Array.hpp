#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>

using namespace std;

template<typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resizeToLeft();
    void resizeToRight();

public:
    Array();
    explicit Array(int initialCapasity);
    Array(int initialCapacity, const T& value);
    Array(const Array& other);
    Array(initializer_list<T> list);

    ~Array();
    
    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    T& front() const;
    T& back() const;

    void push_back(const T& value);
    void pop_back();
    void insert(int index, const T& value);
    void erase(int index);
    void clear();
    void display() const;

    T& at(int index) const;
    T& operator[](int index) const;

    Array& operator=(const Array& other);
};

template<typename T>
Array<T>::Array() : size(0), capacity(10), data(new T(capacity)) {}

template<typename T>
Array<T>::Array(int initialCapasity) {
    if (initialCapasity < 0) {
        throw invalid_argument("capacity cannot be negative");
    }

    size = 0;
    capacity = initialCapasity;
    data = new T[capacity];
}

template<typename T>
Array<T>::Array(int initialSize, const T& value) {
    if (initialSize < 0) {
        throw invalid_argument("size cannot be negative");
    }

    size = initialSize;
    capacity = initialSize;
    data = new T[capacity];
    
    for (size_t i = 0; i < size; i++) {
        data[i] = value;
    }
}

template<typename T>
Array<T>::Array(const Array& other) : size(other.size), capacity(other.capacity), data(new T[other.capacity]) {
    for (size_t i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
Array<T>::Array(initializer_list<T> list) : size(list.size()), capacity(list.size()), data(new T[capacity]) {
    size_t i = 0;
    for (const T& item : list) {
        data[i++] = item;
    }
}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
size_t Array<T>::size() const {
    return size;
}

template<typename T>
size_t Array<T>::capacity() const {
    return capacity;
}

template<typename T>
bool Array<T>::empty() const {
    return true ? size == 0 : false;
}

template<typename T>
T& Array<T>::front() const {
    return data[0];
}

template<typename T>
T& Array<T>::back() const {
    return data[size-1];
}

template<typename T>
void Array<T>::resizeToRight() {
    size_t newCapacity = (capacity == 0 ? 1 : capacity * 2);
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
void Array<T>::resizeToLeft() {
    size_t newCapacity = (size == 0) ? 1 : size * 2;

    if (newCapacity >= capacity) return;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
void Array<T>::push_back(const T& value) {
    if (size == capacity) {
        resizeToRight();
    }

    data[size++] = value;
}

template<typename T>
void Array<T>::pop_back() {
    if (size == 0) {
        throw out_of_range("Array is empty");
    }

    size--;

    if (size > 0 && size <= capacity / 4) {
        resizeToLeft();
    }
}

template<typename T>
void Array<T>::insert(int index, const T& value) {
    if (index < 0 || index > static_cast<int>(size)) {
        throw out_of_range("Index out of range");
    }

    if (size == capacity) {
        resizeToRight();
    }

    for (size_t i = size; i > static_cast<size_t>(index); i--) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    size++;
}

template<typename T>
void Array<T>::erase(int index) {
    if (index < 0 || index >= static_cast<int>(size)) {
        throw out_of_range("Index out of range");
    }

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;

    if (size > 0 && size <= capacity / 4) {
        resizeToLeft();
    }
}

template<typename T>
void Array<T>::clear() {
    delete[] data;
    size = 0;
    capacity = 10;
    data = new T[capacity];
}

template<typename T>
void Array<T>::display() const {
    cout << "[";
    for (size_t i = 0; i < size; i++) {
        cout << data[i];
        if (i != size - 1) {
            cout << ",";
        }
        cout << " ";
    }
    cout << "]" << endl;
}

template<typename T>
T& Array<T>::at(int index) const {
    if (index < 0 || index >= static_cast<int>(size)) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

template<typename T>
T& Array<T>::operator[](int index) const {
    return data[index];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}