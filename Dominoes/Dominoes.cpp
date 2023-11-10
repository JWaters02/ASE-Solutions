#include "Dominoes.h"

Dominoes::Dominoes(const DominoNode& startingDomino, const std::list<DominoNode>& inputDominoes) {
    head = new DominoNode(startingDomino.leftSymbol, startingDomino.rightSymbol);
    tail = head;
    head->isPlaced = true;

    // Populate the dominoLine hash map with DominoNode objects
    // For each domino, create a new DominoNode and insert it into the map
    for (const auto& domino : inputDominoes) {
        dominoLine[domino.leftSymbol] = new DominoNode(domino.leftSymbol, domino.rightSymbol);
        dominoLine[domino.rightSymbol] = dominoLine[domino.leftSymbol];
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

    // Look up all nodes in the hash map to find a matching domino
    for (auto& entry : dominoLine) {
        DominoNode* node = entry.second;
        // If the domino is not already placed and has a matching symbol
        if (node && !node->isPlaced && (node->leftSymbol == matchingSymbol || node->rightSymbol == matchingSymbol)) {
            // If the left symbol matches, but the domino needs to be flipped
            if (node->leftSymbol == matchingSymbol) {
                std::swap(node->leftSymbol, node->rightSymbol);
            }

            // Link the new node to the doubly linked list
            node->next = head;
            node->isPlaced = true;
            head = node;
            placedDominoes++;

            return node;
        }
    }

    return nullptr;
}

DominoNode* Dominoes::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    const std::string& matchingSymbol = tail->rightSymbol;

    // Look up all nodes in the hash map to find a matching domino
    for (auto& entry : dominoLine) {
        DominoNode* node = entry.second;
        // If the domino is not already placed and has a matching symbol
        if (node && !node->isPlaced && (node->leftSymbol == matchingSymbol || node->rightSymbol == matchingSymbol)) {
            // If the right symbol matches, but the domino needs to be flipped
            if (node->rightSymbol == matchingSymbol) {
                std::swap(node->leftSymbol, node->rightSymbol);
            }

            // Link the new node to the doubly linked list
            tail->next = node;
            node->isPlaced = true;
            tail = node;
            placedDominoes++;

            return node;
        }
    }

    return nullptr;
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
