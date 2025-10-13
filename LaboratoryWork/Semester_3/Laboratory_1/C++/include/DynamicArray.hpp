#pragma once
#include <iostream>
#include <string>

using namespace std;

struct DynamicArray {
private:
    std::string* Data;
    int Size;
    int Capacity;

    void ResizeToRight();
    void ResizeToLeft();

public:
    DynamicArray() {
        Init();
    }
    ~DynamicArray();

    void Init();
    void PushBack(string obj);
    void Insert(string obj, int pos);
    string GetElm(int pos);
    void DelElm(int pos);
    void Replace(string obj, int pos);
    int GetSize();
    void Print();
    void Destroy();
};