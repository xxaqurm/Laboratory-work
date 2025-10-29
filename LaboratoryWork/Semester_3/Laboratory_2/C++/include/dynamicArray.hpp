#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class DynamicArray {
private:
    T* Data;
    int Size;
    int Capacity;

    void ResizeToRight() {
        int newCapacity = Capacity + 10;
        T* newData = new T[newCapacity];

        for (int i = 0; i < Size; i++) {
            newData[i] = Data[i];
        }

        delete[] Data;
        Data = newData;
        Capacity = newCapacity;
    }
    
    void ResizeToLeft() {
        if (Capacity <= 10) return;
        
        int newCapacity = Capacity - 10;
        T* newData = new T[newCapacity];

        for (int i = 0; i < Size; i++) {
            newData[i] = Data[i];
        }

        delete[] Data;
        Data = newData;
        Capacity = newCapacity;
    }

public:
    DynamicArray() {
        Init();
    }
    
    DynamicArray(const DynamicArray& other) {
        Size = other.Size;
        Capacity = other.Capacity;
        Data = new T[Capacity];
        for (int i = 0; i < Size; i++) {
            Data[i] = other.Data[i];
        }
    }
    
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] Data;
            Size = other.Size;
            Capacity = other.Capacity;
            Data = new T[Capacity];
            for (int i = 0; i < Size; i++) {
                Data[i] = other.Data[i];
            }
        }
        return *this;
    }

    ~DynamicArray() {
        Destroy();
    }

    void Init() {
        Size = 0;
        Capacity = 10;
        Data = new T[Capacity];
    }
    
    void PushBack(T obj) {
        if (Size == Capacity) {
            ResizeToRight();
        }
        Data[Size++] = obj;
    }
    
    void Insert(T obj, int pos) {
        if (pos < 0 || pos > Size) {
            throw invalid_argument("Invalid index!");
        }
        if (Size == Capacity) {
            ResizeToRight();
        }

        for (int i = Size; i > pos; i--) {
            Data[i] = Data[i - 1];
        }
        Data[pos] = obj;
        Size++;
    }
    
    T GetElm(int pos) const {
        if (pos < 0 || pos >= Size) {
            throw invalid_argument("Invalid index!");
        }
        return Data[pos];
    }
    
    T& operator[](int pos) {
        if (pos < 0 || pos >= Size) {
            throw invalid_argument("Invalid index!");
        }
        return Data[pos];
    }
    
    const T& operator[](int pos) const {
        if (pos < 0 || pos >= Size) {
            throw invalid_argument("Invalid index!");
        }
        return Data[pos];
    }
    
    void DelElm(int pos) {
        if (pos < 0 || pos >= Size) {
            throw invalid_argument("Invalid index!");
        }

        for (int i = pos; i < Size - 1; i++) {
            Data[i] = Data[i + 1];
        }

        Size--;
        if (Size <= Capacity - 10) {
            ResizeToLeft();
        }
    }
    
    void Replace(T obj, int pos) {
        if (pos < 0 || pos >= Size) {
            throw invalid_argument("Invalid index!");
        }

        Data[pos] = obj;
    }
    
    int GetSize() const {
        return Size;
    }
    
    void Print() const {
        cout << "{";
        for (int i = 0; i < Size; i++) {
            cout << Data[i];
            if (i != Size - 1) cout << ", ";
        }
        cout << "}";
    }
    
    void Destroy() {
        delete[] Data;
        Data = nullptr;
        Size = 0;
        Capacity = 0;
    }
    
    void Clear() {
        Size = 0;
    }
    
    bool IsEmpty() const {
        return Size == 0;
    }
};

template <typename T>
void PrintNestedArray(const DynamicArray<DynamicArray<T>>& arr) {
    cout << "[ ";
    for (int i = 0; i < arr.GetSize(); i++) {
        arr[i].Print();
        if (i != arr.GetSize() - 1) cout << " ";
    }
    cout << " ]" << endl;
}