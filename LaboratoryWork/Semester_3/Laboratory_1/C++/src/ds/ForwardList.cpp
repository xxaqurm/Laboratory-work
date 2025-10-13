#include "ForwardList.hpp"
using namespace std;

void ForwardList::Init() {
    head = nullptr;
}

void ForwardList::PushHead(string obj) {
    ForwardNode* newNode = new ForwardNode{obj, head};
    head = newNode;
}

void ForwardList::PushTail(string obj) {
    ForwardNode* newNode = new ForwardNode{obj, nullptr};
    ForwardNode* currentNode = head;

    if (!currentNode) {
        head = newNode;
        return;
    }

    while (currentNode->next) {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

void ForwardList::InsertBefore(string obj, int pos) {
    if (pos == 0) {
        PushHead(obj);
        return;
    }

    ForwardNode* newNode = new ForwardNode{obj, nullptr};
    ForwardNode* currentNode = head;

    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos - 1) {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            return;
        }
        currentPos++;
        currentNode = currentNode->next;
    }
    throw invalid_argument("InsertBefore: invalid index!");
}

void ForwardList::InsertAfter(string obj, int pos) {
    ForwardNode* newNode = new ForwardNode{obj, nullptr};
    ForwardNode* currentNode = head;

    if (!head) {
        throw invalid_argument("InsertAfter: forward list is empty!");
        return;
    }

    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos) {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            return;
        }
        currentPos++;
        currentNode = currentNode->next;
    }
    throw invalid_argument("InsertAfter: invalid index!");
}

void ForwardList::DelElm(string obj) {
    if (!head) {
        return;
    }

    if (head->data == obj) {
        ForwardNode* nextNode = head->next;
        delete head;
        head = nextNode;
        return;
    }

    ForwardNode* currentNode = head;
    while (currentNode->next) {
        if (currentNode->next->data == obj) {
            ForwardNode* nextNode = currentNode->next;
            currentNode->next = currentNode->next->next;
            delete nextNode;
            return;
        }
        currentNode = currentNode->next;
    }
    throw invalid_argument("Remove: element not found!");
}

int ForwardList::Find(string obj) {
    ForwardNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        if (currentNode->data == obj) {
            return currentPos;
        }
        currentPos++;
        currentNode = currentNode->next;
    }
    return -1;
}

int ForwardList::GetSize() {
    ForwardNode* currentNode = head;
    int currentSize = 0;
    while (currentNode) {
        currentNode = currentNode->next;
        currentSize++;
    }
    return currentSize;
}

void ForwardList::Print() {
    ForwardNode* currentNode = head;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    cout << endl;
}

void ForwardList::PrintReverse(ForwardNode* head) {
    if (!head) {
        return;
    }
    PrintReverse(head->next);
    cout << head->data << " ";
}

string ForwardList::GetElm(int pos) {
    ForwardNode* currentNode = head;
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

void ForwardList::Destroy() {
    ForwardNode* currentNode = head;
    while (currentNode) {
        ForwardNode* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = nullptr;
}

ForwardList::~ForwardList() {
    Destroy();
}
