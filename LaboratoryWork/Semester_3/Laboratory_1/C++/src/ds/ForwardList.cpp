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

void ForwardList::DelHead() {
    if (!head) {
        throw invalid_argument("DelHead: list is empty!");
    }

    ForwardNode* prevHead = head;
    head = head->next;
    delete prevHead;
}

void ForwardList::DelTail() {
    if (!head) {
        throw invalid_argument("DelTail: list is empty!");
    }

    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    ForwardNode* currentNode = head;
    while (currentNode->next->next) {
        currentNode = currentNode->next;
    }

    delete currentNode->next;
    currentNode->next = nullptr;
}

void ForwardList::DelBefore(int pos) {
    if (pos <= 0) {
        throw invalid_argument("DelBefore: invalid position!");
    }
    if (!head || !head->next) {
        throw invalid_argument("DelBefore: list too short!");
    }

    if (pos == 1) {
        DelHead();
        return;
    }

    ForwardNode* currentNode = head;
    int currentPos = 0;
    while (currentNode->next && currentNode->next->next) {
        if (currentPos == pos - 2) {
            ForwardNode* temp = currentNode->next;
            currentNode->next = temp->next;
            delete temp;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("DelBefore: invalid index!");
}

void ForwardList::DelAfter(int pos) {
    if (!head) {
        throw invalid_argument("DelAfter: list is empty!");
    }

    ForwardNode* currentNode = head;
    int currentPos = 0;

    while (currentNode) {
        if (currentPos == pos) {
            if (!currentNode->next) {
                throw invalid_argument("DelAfter: no element after given position!");
            }
            ForwardNode* temp = currentNode->next;
            currentNode->next = temp->next;
            delete temp;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("DelAfter: invalid index!");
}

void ForwardList::DelElm(string obj) {
    if (!head) {
        throw invalid_argument("DelElm: list is empty!");
    }

    if (head->data == obj) {
        ForwardNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ForwardNode* currentNode = head;
    while (currentNode->next) {
        if (currentNode->next->data == obj) {
            ForwardNode* temp = currentNode->next;
            currentNode->next = temp->next;
            delete temp;
            return;
        }
        currentNode = currentNode->next;
    }

    throw invalid_argument("DelElm: invalid value!");
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
