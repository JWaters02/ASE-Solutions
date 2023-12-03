#include "Dominoes.h"

Dominoes::Dominoes(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes) {
    startingDomino->isPlaced = true;
    head = tail = startingDomino;
    dominoLine.push_back(startingDomino);

    // Populate the dominoLine hash map with DominoNode objects
    // For each domino, create a new DominoNode and insert it into the map
    for (auto& domino : inputDominoes) {
        dominoMap[domino->leftSymbol].push_back(domino);
        dominoMap[domino->rightSymbol].push_back(domino);
    }

    placedDominoes = 1;
    totalDominoes = inputDominoes.size() + 1;
}

Dominoes::~Dominoes() {
    for (auto& domino : dominoLine) {
        delete domino;
    }
}

DominoNode* Dominoes::addLeftDomino() {
    if (head == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    auto& dominoList = dominoMap[head->leftSymbol];
    for (auto& domino : dominoList) {
        if (!domino->isPlaced) {
            placedDominoes++;
            if (domino->rightSymbol == head->leftSymbol) {
                // No need to flip
                domino->isPlaced = true;
                head = domino;
                dominoLine.push_front(domino);
                return domino;
            } if (domino->leftSymbol == head->leftSymbol) {
                // Flip domino
                std::swap(domino->leftSymbol, domino->rightSymbol);
                domino->isPlaced = true;
                head = domino;
                dominoLine.push_front(domino);
                return domino;
            }
        }
    }
    return nullptr;
}

DominoNode* Dominoes::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    auto& dominoList = dominoMap[tail->rightSymbol];
    for (auto& domino : dominoList) {
        if (!domino->isPlaced) {
            placedDominoes++;
            if (domino->leftSymbol == tail->rightSymbol) {
                // No need to flip
                domino->isPlaced = true;
                tail = domino;
                dominoLine.push_back(domino);
                return domino;
            } if (domino->rightSymbol == tail->rightSymbol) {
                // Flip domino
                std::swap(domino->leftSymbol, domino->rightSymbol);
                domino->isPlaced = true;
                tail = domino;
                dominoLine.push_back(domino);
                return domino;
            }
        }
    }
    return nullptr;
}

bool Dominoes::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void Dominoes::displayDominoLine() const {
    for (const auto& domino : dominoLine) {
        std::cout << domino->leftSymbol << ":" << domino->rightSymbol << " ";
    }
    std::cout << std::endl;
}
