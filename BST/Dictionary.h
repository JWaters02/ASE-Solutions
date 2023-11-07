#ifndef ASE_SOLUTIONS_DICTIONARY_H
#define ASE_SOLUTIONS_DICTIONARY_H

#include <iostream>
#include <utility>
#include <functional>

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
    // Constructor
    Dictionary()
    {
        root = nullptr;
    }

    // Destructor
    ~Dictionary()
    {
        deepDeleteWorker(root);
    }

    // Copy constructor
    Dictionary(const Dictionary& source)
    {
        root = deepCopyWorker(source.root);
    }

    // Move constructor
    Dictionary(Dictionary&& source)
    {
        root = source.root;
        source.root = nullptr;
    }

    // Copy assignment
    Dictionary& operator=(const Dictionary& source)
    {
        if (this != &source)
        {
            deepDeleteWorker(root);
            root = deepCopyWorker(source.root);
        }
        return *this;
    }

    // Move assignment
    Dictionary& operator=(Dictionary&& source)
    {
        if (this != &source)
        {
            deepDeleteWorker(root);
            root = source.root;
            source.root = nullptr;
        }
        return *this;
    }

    void insert(KeyType key, const ItemType& item);
    void insertIterative(KeyType key, const ItemType& item);
    ItemType* lookup(KeyType key);
    ItemType* lookupIterative(KeyType key);
    void remove(KeyType key);
    void removeIf(std::function<bool(KeyType)>);
    void displayEntries(std::ostream& stream = std::cout, TraversalType traversalType = TraversalType::IN_ORDER);
    void displayTree(std::ostream& stream = std::cout, TraversalType traversalType = TraversalType::IN_ORDER);

private:
    struct Node;
    Node* root = nullptr;

    void insertWorker(KeyType key, const ItemType& item, Dictionary::Node*& node = nullptr);
    ItemType* lookupWorker(KeyType key, Node* node = nullptr);
    void removeWorker(KeyType key, Node*& node = nullptr);
    void removeIfWorker(std::function<bool(KeyType)> predicate, Node*& node = nullptr);

    /* Tree rotations
     * Pre-conditions:
     * 1. The node is not a leaf - i.e. is an internal node.
     * 2. For rotateRight - The left node has a right child.
     *    For rotateLeft  - The right node has a left child.
    */
    void rotateLeft(Dictionary::Node*& A);
    void rotateRight(Dictionary::Node*& B);

    void deepDeleteWorker(Node* node);
    Node* deepCopyWorker(Node* node);
    void displayEntriesWorker(Node* node, std::ostream& stream, TraversalType traversalType);
    void displayTreeStructure(Dictionary::Node* node, int depth, std::ostream& stream);
    void displayTreeWorker(Dictionary::Node* node, int depth, std::ostream& stream,
                           TraversalType traversalType);

    friend void accessLeftRotator(Dictionary<KeyType, ItemType>& dictionary);
    friend void accessRightRotator(Dictionary<KeyType, ItemType>& dictionary);

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
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::insertWorker(KeyType key, const ItemType& item, Dictionary::Node*& node)
{
    if (isLeaf(node)) node = new Node(key, item);
    else {
        if (node->key == key) node->item = item;
        else if (node->key > key) insertWorker(key, item, node->right);
        else if (node->key < key) insertWorker(key, item, node->left);
    }
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::insertIterative(KeyType key, const ItemType &item)
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
    return lookupWorker(key, root);
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

template<typename KeyType, typename ItemType>
ItemType *Dictionary<KeyType, ItemType>::lookupIterative(KeyType key)
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

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::remove(KeyType key)
{
    removeWorker(key, root);
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::removeWorker(KeyType key, Dictionary::Node*& node)
{
    if (isLeaf(node)) return;

    if (node->key == key)
    {
        if (isLeaf(node->left) && isLeaf(node->right))
        {
            delete node;
            node = nullptr;
        }
        else if (isLeaf(node->left)) node = node->right;
        else if (isLeaf(node->right)) node = node->left;
        else {
            Node *current = node->right;
            while (!isLeaf(current->left)) current = current->left;
            node->key = current->key;
            node->item = current->item;
            removeWorker(current->key, node->right);
        }
    }
    else if (node->key > key) removeWorker(key, node->right);
    else if (node->key < key) removeWorker(key, node->left);
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::removeIf(std::function<bool(KeyType)> predicate)
{
    removeIfWorker(predicate, root);
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::removeIfWorker(std::function<bool(KeyType)> predicate, Node*& node)
{
    if (isLeaf(node)) return;

    removeIfWorker(predicate, node->left);
    removeIfWorker(predicate, node->right);

    if (predicate(node->key))
    {
        removeWorker(node->key, node);
    }
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::rotateRight(Dictionary::Node *&B)
{
    assert(isLeaf(B) == false);

    assert(B->left);
    Node* beta = B->left;

    assert(beta->right);
    B->left = beta->right;

    beta->right = B;
    B = beta;
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::rotateLeft(Dictionary::Node *&A)
{
    assert(isLeaf(A) == false);

    assert(A->right);
    Node* beta = A->right;

    assert(beta->left);
    A->right = beta->left;

    beta->left = A;
    A = beta;
}

template<typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::deepDeleteWorker(Dictionary::Node* node)
{
    if (isLeaf(node)) return;

    deepDeleteWorker(node->left);
    deepDeleteWorker(node->right);
    delete node;
}

template <typename KeyType, typename ItemType>
typename Dictionary<KeyType, ItemType>::Node* Dictionary<KeyType, ItemType>::deepCopyWorker(Dictionary::Node* node)
{
    if (isLeaf(node)) return nullptr;

    Node* newNode = new Node(node->key, node->item);
    newNode->left = deepCopyWorker(node->left);
    newNode->right = deepCopyWorker(node->right);
    return newNode;
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayEntries(std::ostream& stream, TraversalType traversalType)
{
    displayEntriesWorker(root, stream, traversalType);
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayEntriesWorker(Dictionary::Node* node, std::ostream& stream, TraversalType traversalType)
{
    if (isLeaf(node)) return;

    if (traversalType == TraversalType::PRE_ORDER) stream << node->key << " " << node->item << std::endl;

    displayEntriesWorker(node->left, stream, traversalType);

    if (traversalType == TraversalType::IN_ORDER) stream << node->key << " " << node->item << std::endl;

    displayEntriesWorker(node->right, stream, traversalType);

    if (traversalType == TraversalType::POST_ORDER) stream << node->key << " " << node->item << std::endl;
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTreeStructure(Dictionary::Node* node, int depth, std::ostream& stream) {
    for (int i = 0; i < depth; i++) { stream << "- "; }
    stream << node->key << " " << node->item << std::endl;
    if (isLeaf(node->left) && isLeaf(node->right))
    {
        for (int i = 0; i < depth; i++) { stream << "- "; }
        stream << "*" << std::endl;
    }
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTree(std::ostream& stream, TraversalType traversalType)
{
    displayTreeWorker(root, 0, stream, traversalType);
}

template <typename KeyType, typename ItemType>
void Dictionary<KeyType, ItemType>::displayTreeWorker(Dictionary::Node* node, int depth, std::ostream& stream,
                                                      TraversalType traversalType)
{
    if (isLeaf(node)) return;

    if (traversalType == TraversalType::PRE_ORDER) displayTreeStructure(node, depth, stream);

    displayTreeWorker(node->right, depth + 1, stream, traversalType);

    if (traversalType == TraversalType::IN_ORDER) displayTreeStructure(node, depth, stream);

    displayTreeWorker(node->left, depth + 1, stream, traversalType);

    if (traversalType == TraversalType::POST_ORDER) displayTreeStructure(node, depth, stream);
}

#endif //ASE_SOLUTIONS_DICTIONARY_H
