#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* Data;
    size_t Size;
    size_t Capacity;

    void ResizeToRight() {
        size_t newCapacity = Capacity + 10;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < Size; i++)
            newData[i] = Data[i];
        delete[] Data;
        Data = newData;
        Capacity = newCapacity;
    }

    void ResizeToLeft() {
        if (Capacity <= 10) return;
        size_t newCapacity = Capacity - 10;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < Size; i++)
            newData[i] = Data[i];
        delete[] Data;
        Data = newData;
        Capacity = newCapacity;
    }

public:
    DynamicArray() : Data(new T[10]), Size(0), Capacity(10) {}
    DynamicArray(size_t initialSize) : Data(new T[initialSize * 2]), Size(initialSize), Capacity(initialSize * 2) {}
    DynamicArray(size_t initialSize, const T& defaultValue) : Data(new T[initialSize * 2]), Size(initialSize), Capacity(initialSize * 2) {
        for (size_t i = 0; i < Size; i++)
            Data[i] = defaultValue;
    }

    DynamicArray(const DynamicArray& other) : Data(new T[other.Capacity]), Size(other.Size), Capacity(other.Capacity) {
        for (size_t i = 0; i < Size; i++)
            Data[i] = other.Data[i];
    }

    DynamicArray(DynamicArray&& other) noexcept : Data(other.Data), Size(other.Size), Capacity(other.Capacity) {
        other.Data = nullptr;
        other.Size = 0;
        other.Capacity = 0;
    }

    DynamicArray(const T* begin, const T* end) {
        Size = end - begin;
        Capacity = Size * 2;
        Data = new T[Capacity];
        for (size_t i = 0; i < Size; i++) {
            Data[i] = begin[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] Data;
            Size = other.Size;
            Capacity = other.Capacity;
            Data = new T[Capacity];
            for (size_t i = 0; i < Size; i++)
                Data[i] = other.Data[i];
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] Data;
            Data = other.Data;
            Size = other.Size;
            Capacity = other.Capacity;
            other.Data = nullptr;
            other.Size = 0;
            other.Capacity = 0;
        }
        return *this;
    }

    ~DynamicArray() { delete[] Data; }

    void push_back(const T& obj) {
        if (Size == Capacity) ResizeToRight();
        Data[Size++] = obj;
    }

    void DelElm(size_t pos) {
        if (pos >= Size) throw std::invalid_argument("Invalid index");
        for (size_t i = pos; i < Size - 1; i++)
            Data[i] = Data[i + 1];
        Size--;
        if (Size <= Capacity - 10) ResizeToLeft();
    }

    T& operator[](size_t pos) {
        if (pos >= Size) throw std::invalid_argument("Invalid index");
        return Data[pos];
    }

    const T& operator[](size_t pos) const {
        if (pos >= Size) throw std::invalid_argument("Invalid index");
        return Data[pos];
    }

    size_t size() const { return Size; }

    void clear() { Size = 0; }

    void pop() {
        if (Size == 0) throw std::underflow_error("Array is empty");
        Size--;
        if (Size <= Capacity - 10) ResizeToLeft();
    }

    bool empty() const {
        return Size == 0;
    }

    const T* begin() const { return Data; }
    const T* end() const { return Data + Size; }

    // Для модифицируемого доступа
    T* begin() { return Data; }
    T* end() { return Data + Size; }
};