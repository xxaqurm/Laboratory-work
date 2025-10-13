#include "DynamicArray.hpp"
using namespace std;

void DynamicArray::Init() {
    Size = 0;
    Capacity = 10;
    Data = new string[Capacity];
}

void DynamicArray::PushBack(string obj) {
    if (Size == Capacity) {
        ResizeToRight();
    }
    Data[Size++] = obj;
}

void DynamicArray::Insert(string obj, int pos) {
    if (pos < 0 || pos > Size) {
        throw invalid_argument ("Invalid index!");
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

string DynamicArray::GetElm(int pos) {
    if (pos < 0 || pos >= Size) {
        throw invalid_argument ("Invalid index!");
    }
    return Data[pos];
}

void DynamicArray::DelElm(int pos) {
    if (pos < 0 || pos >= Size) {
        throw invalid_argument ("Invalid index!");
    }

    for (int i = pos; i < Size - 1; i++) {
        Data[i] = Data[i + 1];
    }

    Size--;
    if (Size == Capacity - 10) {
        ResizeToLeft();
    }
}

void DynamicArray::Replace(string obj, int pos) {
    if (pos < 0 || pos >= Size) {
        throw invalid_argument ("Invalid index!");
    }

    Data[pos] = obj;
}

int DynamicArray::GetSize() {
    return Size;
}

void DynamicArray::Print() {
    for (int i = 0; i < Size; i++) {
        cout << Data[i] << " ";
    }
    cout << endl;
}

void DynamicArray::Destroy() {
    delete[] Data;
    Size = 0;
    Capacity = 0;
}

void DynamicArray::ResizeToRight() {
    int newCapacity = Capacity + 10;
    string* newData = new string[newCapacity];

    for (int i = 0; i < Size; i++) {
        newData[i] = Data[i];
    }

    delete[] Data;
    Data = newData;
    Capacity = newCapacity;
}

void DynamicArray::ResizeToLeft() {
    int newCapacity = Capacity - 10;
    string* newData = new string[newCapacity];

    for (int i = 0; i < Size; i++) {
        newData[i] = Data[i];
    }

    delete[] Data;
    Data = newData;
    Capacity = newCapacity;
}

DynamicArray::~DynamicArray() {
    Destroy();
}