#include "singlyLinkedList.h"

Node::Node(char data, Node *next)
{
    this->data = data;
    this->next = next;
}

SinglyLinkedList::SinglyLinkedList()
{
    head = nullptr;
    size = 0;
}

void SinglyLinkedList::insert(char data)
{
    Node* nextNode = new Node(data, head);
    head = nextNode;
    size++;
}

void SinglyLinkedList::insert_back(char data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new Node(data);
    }
}

void SinglyLinkedList::display() const
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->data << ' ';
        current = current->next;
    }
    std::cout << std::endl;
}

bool SinglyLinkedList::search(char data) const
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
