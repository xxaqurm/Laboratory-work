#include "LinkedList.hpp"
using namespace std;

void LinkedList::Init() {
    head = nullptr;
}

void LinkedList::PushHead(string obj) {
    LinkedNode* newNode = new LinkedNode{obj, nullptr, head};
    if (!head) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    head->prev = newNode;
    head = newNode;
}

void LinkedList::PushTail(string obj) {
    LinkedNode* newNode = new LinkedNode{obj, nullptr, nullptr};
    
    if (!tail) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void LinkedList::InsertBefore(string obj, int pos) {
    if (pos == 0) {
        PushHead(obj);
        return;
    }

    LinkedNode* newNode = new LinkedNode{obj, nullptr, nullptr};
    LinkedNode* currentNode = head;
    int currentPos = 0;

    while (currentNode) {
        if (currentPos == pos) {
            newNode->prev = currentNode->prev;
            newNode->next = currentNode;
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("InsertBefore: invalid index!");
}

void LinkedList::InsertAfter(string obj, int pos) {
    LinkedNode* newNode = new LinkedNode{obj, nullptr, nullptr};
    LinkedNode* currentNode = head;
    int currentPos = 0;

    if (!head) {
        throw invalid_argument("InsertAfter: linked list is empty!");
        return;
    }

    while (currentNode) {
        if (currentPos == pos) {
            newNode->prev = currentNode;
            newNode->next = currentNode->next;
            if (currentNode->next) currentNode->next->prev = newNode;
            currentNode->next = newNode;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("InsertAfter: something went wrong!");
}

int LinkedList::Find(string obj) {
    LinkedNode* currentNode = head;
    int currentPos = 0;

    while (currentNode) {
        if (currentNode->data == obj) return currentPos;
        currentNode = currentNode->next;
        currentPos++;
    }
    return -1;
}

int LinkedList::GetSize() {
    LinkedNode* currentNode = head;
    int size = 0;
    while (currentNode) {
        size++;
        currentNode = currentNode->next;
    }
    return size;
}

void LinkedList::DelHead() {
    if (!head) {
        throw invalid_argument("DelHead: list is empty!");
    }

    LinkedNode* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    delete temp;
}

void LinkedList::DelTail() {
    if (!tail) {
        throw invalid_argument("DelTail: list is empty");
    }

    LinkedNode* temp = tail;
    if (tail->prev) {
        tail->prev->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }

    delete temp;
}

void LinkedList::DelBefore(int pos) {
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

    LinkedNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos) {
            LinkedNode* nodeToDelete = currentNode->prev;
            if (!nodeToDelete) {
                throw invalid_argument("DelBefore: no element before given position!");
            }
            if (nodeToDelete->prev) {
                nodeToDelete->prev->next = currentNode;
            } else {
                head = currentNode;
            }
            currentNode->prev = nodeToDelete->prev;
            delete nodeToDelete;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("DelBefore: invalid index!");
}

void LinkedList::DelAfter(int pos) {
    if (!head) {
        throw invalid_argument("DelAfter: invalid index!");
    }

    LinkedNode* currentNode = head;
    int currentPos = 0;
    while (currentNode) {
        if (currentPos == pos) {
            LinkedNode* nodeToDelete = currentNode->next;
            if (!nodeToDelete) {
                throw invalid_argument("DelAfter: no element after given position!");
            }
            currentNode->next = nodeToDelete->next;
            if (nodeToDelete->next) {
                nodeToDelete->next->prev = currentNode;
            }
            delete nodeToDelete;
            return;
        }
        currentNode = currentNode->next;
        currentPos++;
    }
    throw invalid_argument("DelAfter: invalid index!");
}

void LinkedList::DelElm(string obj) {
    if (!head) {
        throw invalid_argument("DelElm: list is empty!");
    }

    if (obj == head->data) {
        DelHead();
        return;
    }

    LinkedNode* currentNode = head;
    while (currentNode) {
        if (obj == currentNode->data) {
            LinkedNode* deletedNode = currentNode;
            currentNode->prev->next = currentNode->next;
            if (currentNode->next) {
                currentNode->next->prev = currentNode->prev;
            } else {
                tail = currentNode->prev;
            }
            delete deletedNode;
            return;
        }
        currentNode = currentNode->next;
    }

    throw invalid_argument("DelElm: element not found!");
}

void LinkedList::Print() {
    LinkedNode* currentNode = head;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    cout << endl;
}

void LinkedList::PrintReverse() {
    LinkedNode* currentNode = tail;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->prev;
    }
    cout << endl;
}

string LinkedList::GetElm(int pos) {
    LinkedNode* currentNode = head;
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

void LinkedList::Destroy() {
    LinkedNode* currentNode = head;
    while (currentNode) {
        LinkedNode* deletedNode = currentNode;
        currentNode = currentNode->next;
        delete deletedNode;
    }
    head = nullptr;
}

LinkedList::~LinkedList() {
    Destroy();
}