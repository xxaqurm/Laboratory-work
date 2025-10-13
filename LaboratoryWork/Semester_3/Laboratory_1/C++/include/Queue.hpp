#pragma once
#include <iostream>
#include <string>

using namespace std;

struct QueueNode {
    string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* head;
    QueueNode* tail;

    void Init();
    void Push(string obj);
    string Pop();
    void Print();
    int GetSize();
    string GetElm(int pos);
    void Destroy();

    ~Queue();
};