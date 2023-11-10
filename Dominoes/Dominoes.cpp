#include "Dominoes.h"

Dominoes::Dominoes(const DominoNode& startingDomino, const std::list<DominoNode> &inputDominoes) {
    head = new DominoNode(startingDomino.leftSymbol, startingDomino.rightSymbol);
    tail = head;

    dominoLine[startingDomino.leftSymbol] = head;
    dominoLine[startingDomino.rightSymbol] = head;

    // Populate hash map with nullptrs for each symbol in the input dominoes 
    // so that it can be checked if a symbol has been used
    for (const DominoNode& domino : inputDominoes) {
        if (dominoLine.find(domino.leftSymbol) == dominoLine.end()) {
            dominoLine[domino.leftSymbol] = nullptr;
        }
        if (dominoLine.find(domino.rightSymbol) == dominoLine.end()) {
            dominoLine[domino.rightSymbol] = nullptr;
        }
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

    std::string matchingSymbol = head->leftSymbol;
    DominoNode* matchingNode = dominoLine[matchingSymbol];

    // If there is a matching domino that is not already in the line
    if (matchingNode != nullptr && !matchingNode->isPlaced) {
        DominoNode* newNode = new DominoNode(matchingNode->leftSymbol, matchingNode->rightSymbol);

        // Shift the current head to the right and assign the new node as the new head
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        newNode->isPlaced = true;

        dominoLine[newNode->leftSymbol] = newNode;
        dominoLine[newNode->rightSymbol] = newNode;

        return newNode;
    } else {
        return nullptr;
    }
}

DominoNode* Dominoes::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    std::string matchingSymbol = tail->rightSymbol;
    DominoNode* matchingNode = dominoLine[matchingSymbol];

    // If there is a matching domino that is not already in the line
    if (matchingNode != nullptr && !matchingNode->isPlaced) {
        DominoNode* newNode = new DominoNode(matchingNode->leftSymbol, matchingNode->rightSymbol);

        // Shift the current tail to the left and assign the new node as the new tail
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        newNode->isPlaced = true;

        dominoLine[newNode->leftSymbol] = newNode;
        dominoLine[newNode->rightSymbol] = newNode;

        return newNode;
    } else {
        return nullptr;
    }
}

bool Dominoes::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void Dominoes::displayDominoLine() {
    DominoNode* current = head;
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
