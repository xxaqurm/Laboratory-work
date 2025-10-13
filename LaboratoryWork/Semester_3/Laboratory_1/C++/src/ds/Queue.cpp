#include "Queue.hpp"
using namespace std;

void Queue::Init() {
    head = nullptr;
    tail = nullptr;
}

void Queue::Push(string obj) {
    QueueNode* newNode = new QueueNode{obj, nullptr};
    if (!tail) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

string Queue::Pop() {
    if (!head) {
        cerr << "Pop: queue is empty!" << endl;
        return "";
    }

    QueueNode* removedNode = head;
    string removedValue = head->data;
    head = head->next;

    if (!head) {
        tail = nullptr;
    }

    delete removedNode;
    return removedValue;
}

void Queue::Print() {
    QueueNode* currentNode = head;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    cout << endl;
}

int Queue::GetSize() {
    QueueNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        currentNode = currentNode->next;
        currentPos++;
    }
    return currentPos;
}

string Queue::GetElm(int pos) {
    QueueNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos) {
            return currentNode->data;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("GetElm: invalid position!");
}

void Queue::Destroy() {
    while (head) {
        QueueNode* deletedNode = head;
        head = head->next;
        delete deletedNode;
    }
    tail = nullptr;
}

Queue::~Queue() {
    Destroy();
}