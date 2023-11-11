#include "Dominoes.h"

Dominoes::Dominoes(const DominoNode& startingDomino, const std::list<DominoNode>& inputDominoes) {
    head = new DominoNode(startingDomino.leftSymbol, startingDomino.rightSymbol);
    tail = head;
    head->isPlaced = true;

    leftSymbolMap[startingDomino.leftSymbol] = head;
    rightSymbolMap[startingDomino.rightSymbol] = head;

    for (const auto& domino : inputDominoes) {
        auto* node = new DominoNode(domino.leftSymbol, domino.rightSymbol);
        leftSymbolMap[domino.leftSymbol] = node;
        rightSymbolMap[domino.rightSymbol] = node;
    }

    placedDominoes = 1;
    totalDominoes = inputDominoes.size() + 1;
}

Dominoes::~Dominoes() {
    DominoNode* current = head;
    while (current != nullptr) {
        DominoNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

DominoNode* Dominoes::addLeftDomino() {
    if (head == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    const std::string& matchingSymbol = head->leftSymbol;

    if (rightSymbolMap.count(matchingSymbol) == 0) {
        return nullptr; // No dominoes with the matching symbol on the right
    }

    DominoNode* node = rightSymbolMap[matchingSymbol];

    if (node == nullptr || node->isPlaced) {
        return nullptr; // No matching domino found or it's already placed
    }

    // If the right symbol matches, no need to flip
    // Link the new node to the left of the current head
    node->next = head;
    head->prev = node;
    node->isPlaced = true;
    head = node;
    placedDominoes++;

    // Remove from the maps to prevent reuse
    leftSymbolMap.erase(node->leftSymbol);
    rightSymbolMap.erase(node->rightSymbol);

    return node;
}

DominoNode* Dominoes::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    const std::string& matchingSymbol = tail->rightSymbol;

    if (leftSymbolMap.count(matchingSymbol) == 0) {
        return nullptr; // No dominoes with the matching symbol on the left
    }

    DominoNode* node = leftSymbolMap[matchingSymbol];

    if (node == nullptr || node->isPlaced) {
        return nullptr; // No matching domino found or it's already placed
    }

    // If the left symbol matches, no need to flip
    // Link the new node to the right of the current tail
    node->prev = tail;
    tail->next = node;
    node->isPlaced = true;
    tail = node;
    placedDominoes++;

    // Remove from the maps to prevent reuse
    leftSymbolMap.erase(node->leftSymbol);
    rightSymbolMap.erase(node->rightSymbol);

    return node;
}

bool Dominoes::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void Dominoes::displayDominoLine() const {
    const DominoNode* current = head;
    std::string line;
    while (current != nullptr) {
        line += current->leftSymbol + ":" + current->rightSymbol;
        current = current->next;
        if (current != nullptr) {
            line += " ";
        }
    }

    std::cout << line << std::endl;
}
