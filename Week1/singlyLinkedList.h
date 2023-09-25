#ifndef ASE_SOLUTIONS_SINGLYLINKEDLIST_H
#define ASE_SOLUTIONS_SINGLYLINKEDLIST_H

#include <iostream>

struct Node
{
    Node(char data, Node* next = nullptr);

    char data;
    Node* next;
};

class SinglyLinkedList
{
public:
    SinglyLinkedList();

    void insert(char data);
    void insert_back(char data);
    void display() const;
    bool search(char data) const;

private:
    Node* head;
    int size;
};

#endif //ASE_SOLUTIONS_SINGLYLINKEDLIST_H
