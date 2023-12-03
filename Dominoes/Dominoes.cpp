#include "Dominoes.h"

Dominoes::Dominoes(DominoNode* startingDomino, const std::vector<DominoNode*>& inputDominoes) {
    startDomino = startingDomino;
    head = tail = startDomino;
    startDomino->isPlaced = true;

    for (auto& domino : inputDominoes) {
        insertInMap(domino);
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
    auto it = rightSymbolMap.find(head->leftSymbol);
    if (it != rightSymbolMap.end() && !it->second->isPlaced) {
        DominoNode* newDomino = it->second;
        newDomino->isPlaced = true;
        newDomino->next = head;
        head->prev = newDomino;
        head = newDomino;
        placedDominoes++;
        return newDomino;
    }
    return nullptr;
}

DominoNode* Dominoes::addRightDomino() {
    auto it = leftSymbolMap.find(tail->rightSymbol);
    if (it != leftSymbolMap.end() && !it->second->isPlaced) {
        DominoNode* newDomino = it->second;
        newDomino->isPlaced = true;
        newDomino->prev = tail;
        tail->next = newDomino;
        tail = newDomino;
        return newDomino;
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
