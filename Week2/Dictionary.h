#ifndef ASE_SOLUTIONS_DICTIONARY_H
#define ASE_SOLUTIONS_DICTIONARY_H

#include <iostream>
#include <utility>

struct Node
{
public:
    Node(int key, std::string item, Node* right = nullptr, Node* left = nullptr)
    {
        this->key = key;
        this->item = std::move(item);
        this->right = right;
        this->left = left;
    }

    int key;
    std::string item;
    
    Node* left;
    Node* right;
};

class Dictionary
{
public:
    Dictionary()
    {
        root = nullptr;
        size = 0;
    }

    void insert(int key, const std::string& item);
    std::string* lookup(int key);

private:
    Node* root;
    int size;
};

void Dictionary::insert(int key, const std::string& item)
{
    if (root == nullptr)
    {
        root = new Node(key, item);
    }
    else
    {
        Node* current = root;

        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->item = item;
                break;
            }
            else if (current->key > key)
            {
                if (current->right == nullptr)
                {
                    current->right = new Node(key, item);
                    break;
                }
                else
                {
                    current = current->right;
                }
            }
            else if (current->key < key)
            {
                if (current->left == nullptr)
                {
                    current->left = new Node(key, item);
                    break;
                }
                else
                {
                    current = current->left;
                }
            }
        }
    }
}

std::string* Dictionary::lookup(int key)
{
    Node* current = root;
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return &current->item;
        }
        else if (current->key > key)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return nullptr;
}

#endif //ASE_SOLUTIONS_DICTIONARY_H
