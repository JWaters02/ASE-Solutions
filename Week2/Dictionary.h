#ifndef ASE_SOLUTIONS_DICTIONARY_H
#define ASE_SOLUTIONS_DICTIONARY_H

#include <iostream>
#include <utility>

template <typename KeyType, typename ItemType>
class Dictionary
{
public:
    Dictionary()
    {
        root = nullptr;
        size = 0;
    }

    void insert(KeyType key, const ItemType& item);
    ItemType* lookup(KeyType key);

private:
    struct Node;
    Node* root = nullptr;
    KeyType size = 0;

    static bool isLeaf(Node* node)
    {
        return node == nullptr;
    }
};

template <typename KeyType, typename ItemType>
struct Dictionary<KeyType, ItemType>::Node
{
public:
    Node(KeyType key, ItemType item, Node* right = nullptr, Node* left = nullptr)
    {
        this->key = key;
        this->item = std::move(item);
        this->right = right;
        this->left = left;
    }

    KeyType key;
    ItemType item;

    Node* left = nullptr;
    Node* right = nullptr;
};

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::insert(KeyType key, const ItemType& item)
{
    if (isLeaf(root))
    {
        root = new Node(key, item);
    }
    else
    {
        Node* current = root;

        while (!isLeaf(current))
        {
            if (current->key == key)
            {
                current->item = item;
                break;
            }
            else if (current->key > key)
            {
                if (isLeaf(current->right))
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
                if (isLeaf(current->left))
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

template <typename KeyType, typename ItemType>
ItemType* Dictionary<KeyType, ItemType>::lookup(KeyType key)
{
    Node* current = root;
    while (!isLeaf(current))
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
