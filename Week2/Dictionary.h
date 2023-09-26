#ifndef ASE_SOLUTIONS_DICTIONARY_H
#define ASE_SOLUTIONS_DICTIONARY_H

#include <iostream>
#include <utility>

struct Node
{
public:
    Node(int key, std::string* item, Node* next = nullptr)
    {
        this->key = key;
        this->item = item;
        this->next = next;
    }

    int key;
    std::string* item;
    Node* next;
};

class Dictionary
{
public:
    Dictionary()
    {
        head = nullptr;
        size = 0;
    }

    void insert(int key, std::string* item);
    std::string* lookup(int key);

private:
    Node* head;
    int size;
};

void Dictionary::insert(int key, std::string* item)
{
    if (head == nullptr)
    {
        head = new Node(key, item);
    }
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            if (key == current->key)
            {
                current->item = item;
            }
            else
            {
                current = current->next;
            }
        }
        current->next = new Node(key, item);
    }
}

std::string* Dictionary::lookup(int key)
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current->item;
        }
        current = current->next;
    }
    return nullptr;
}

#endif //ASE_SOLUTIONS_DICTIONARY_H
