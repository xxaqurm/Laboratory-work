#pragma once
#include <iostream>
#include <string>

using namespace std;

struct LinkedNode {
    string data;
    LinkedNode* prev;
    LinkedNode* next;
};

struct LinkedList {
    LinkedNode* head;
    LinkedNode* tail;

    void Init();
    void PushHead(string obj);
    void PushTail(string obj);
    void InsertBefore(string obj, int pos);
    void InsertAfter(string obj, int pos);
    void DelHead();
    void DelTail();
    void DelBefore(int pos);
    void DelAfter(int pos);
    void DelElm(string obj);
    int Find(string obj);
    int GetSize();
    void Print();
    void PrintReverse();
    string GetElm(int pos);
    void Destroy();

    ~LinkedList();
};