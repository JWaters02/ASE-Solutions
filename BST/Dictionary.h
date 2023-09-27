#ifndef ASE_SOLUTIONS_DICTIONARY_H
#define ASE_SOLUTIONS_DICTIONARY_H

#include <iostream>
#include <utility>

enum class TraversalType
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
};

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
    void displayEntries(TraversalType traversalType = TraversalType::IN_ORDER);
    void displayTree(TraversalType traversalType = TraversalType::IN_ORDER);

private:
    struct Node;
    Node* root = nullptr;
    KeyType size = 0;

    void insertWorker(KeyType key, const ItemType& item, Node* node = nullptr);
    ItemType* lookupWorker(KeyType key, Node* node = nullptr);
    void displayEntriesWorker(Node* node, TraversalType traversalType);
    void displayTreeStructure(Node* node, int depth);
    void displayTreeWorker(Node* node, int depth, TraversalType traversalType);
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
    insertWorker(key, item, root);
    /*if (isLeaf(root))
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
    }*/
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::insertWorker(KeyType key, const ItemType& item, Dictionary::Node* node)
{
    if (isLeaf(root))
    {
        root = new Node(key, item);
    }
    else
    {
        if (node->key == key)
        {
            node->item = item;
        }
        else if (node->key > key)
        {
            if (isLeaf(node->right))
            {
                node->right = new Node(key, item);
            }
            else
            {
                insertWorker(key, item, node->right);
            }
        }
        else if (node->key < key)
        {
            if (isLeaf(node->left))
            {
                node->left = new Node(key, item);
            }
            else
            {
                insertWorker(key, item, node->left);
            }
        }
    }
}

template <typename KeyType, typename ItemType>
ItemType* Dictionary<KeyType, ItemType>::lookup(KeyType key)
{
    return lookupWorker(key, root);
    /*Node* current = root;
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
    return nullptr;*/
}

template <typename KeyType, typename ItemType>
ItemType* Dictionary<KeyType, ItemType>::lookupWorker(KeyType key, Dictionary::Node* node)
{
    if (isLeaf(node)) return nullptr;

    if (node->key == key) return &node->item;
    if (node->key > key && !isLeaf(node->right)) return lookupWorker(key, node->right);
    if (node->key < key && !isLeaf(node->left)) return lookupWorker(key, node->left);

    return nullptr;
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayEntries(TraversalType traversalType)
{
    displayEntriesWorker(root, traversalType);
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTree(TraversalType traversalType)
{
    displayTreeWorker(root, 0, traversalType);
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayEntriesWorker(Dictionary::Node* node, TraversalType traversalType)
{
    if (isLeaf(node)) return;

    if (traversalType == TraversalType::PRE_ORDER) std::cout << node->key << " " << node->item << std::endl;

    displayEntriesWorker(node->left, TraversalType::PRE_ORDER);

    if (traversalType == TraversalType::IN_ORDER) std::cout << node->key << " " << node->item << std::endl;

    displayEntriesWorker(node->right, TraversalType::PRE_ORDER);

    if (traversalType == TraversalType::POST_ORDER) std::cout << node->key << " " << node->item << std::endl;
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTreeStructure(Dictionary::Node* node, int depth) {
    for (int i = 0; i < depth; i++) { std::cout << "- "; }
    std::cout << node->key << " " << node->item << std::endl;
    if (isLeaf(node->left) && isLeaf(node->right))
    {
        for (int i = 0; i < depth; i++) { std::cout << "- "; }
        std::cout << "*" << std::endl;
    }
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTreeWorker(Dictionary::Node* node, int depth, TraversalType traversalType)
{
    if (isLeaf(node)) return;

    if (traversalType == TraversalType::PRE_ORDER) displayTreeStructure(node, depth);

    displayTreeWorker(node->right, depth + 1, TraversalType::PRE_ORDER);

    if (traversalType == TraversalType::IN_ORDER) displayTreeStructure(node, depth);

    displayTreeWorker(node->left, depth + 1, TraversalType::PRE_ORDER);

    if (traversalType == TraversalType::POST_ORDER) displayTreeStructure(node, depth);
}

#endif //ASE_SOLUTIONS_DICTIONARY_H
