#include "LinkedList.hpp"
using namespace std;

void LinkedList::Init() {
    head = nullptr;
}

void LinkedList::PushHead(string obj) {
    LinkedNode* newNode = new LinkedNode{obj, nullptr, head};
    if (head) head->prev = newNode;
    head = newNode;
}

void LinkedList::PushTail(string obj) {
    LinkedNode* newNode = new LinkedNode{obj, nullptr, nullptr};
    LinkedNode* currentNode = head;

    if (!currentNode) {
        head = newNode;
        return;
    }

    while (currentNode->next) currentNode = currentNode->next;

    newNode->prev = currentNode;
    currentNode->next = newNode;
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

void LinkedList::DelElm(string obj) {
    LinkedNode* currentNode = head;

    while (currentNode) {
        if (currentNode->data == obj) {
            if (currentNode->prev) currentNode->prev->next = currentNode->next;
            else head = currentNode->next;

            if (currentNode->next) currentNode->next->prev = currentNode->prev;

            delete currentNode;
            return;
        }
        currentNode = currentNode->next;
    }
    throw invalid_argument("Remove: element not found!");
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

void LinkedList::Print() {
    LinkedNode* currentNode = head;
    while (currentNode) {
        cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    cout << endl;
}

void LinkedList::PrintReverse() {
    LinkedNode* currentNode = head;
    if (!currentNode) return;

    while (currentNode->next) currentNode = currentNode->next;

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