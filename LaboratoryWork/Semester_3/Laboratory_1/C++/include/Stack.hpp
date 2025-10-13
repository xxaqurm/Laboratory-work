#pragma once
#include <iostream>
#include <string>

using namespace std;

struct StackNode {
    string data;
    StackNode* next;
};

struct Stack {
    StackNode* head;

    void Init();
    void Push(string obj);
    string Pop();
    void Print();
    int GetSize();
    string GetElm(int pos);
    void Destroy();

    ~Stack();
};