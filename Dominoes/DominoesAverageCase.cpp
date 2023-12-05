#include "DominoesAverageCase.h"

DominoesAverageCase::DominoesAverageCase(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes) {
    startingDomino->isPlaced = true;
    head = tail = startingDomino;
    dominoLine.push_back(startingDomino);

    // Populate the dominoMap hash map with DominoNode objects
    for (auto& domino : inputDominoes) {
        dominoMap[domino->leftSymbol].push_back(domino);
        dominoMap[domino->rightSymbol].push_back(domino);
    }

    placedDominoes = 1;
    totalDominoes = inputDominoes.size() + 1;
}

DominoesAverageCase::~DominoesAverageCase() {
    for (const auto& domino : dominoLine) {
        delete domino;
    }
}

DominoNode* DominoesAverageCase::addLeftDomino() {
    if (head == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    const auto& dominoList = dominoMap[head->leftSymbol];
    for (auto& domino : dominoList) {
        if (!domino->isPlaced) {
            if (domino->leftSymbol == head->leftSymbol) {
                std::swap(domino->leftSymbol, domino->rightSymbol); // Flip domino
            }
            domino->isPlaced = true;
            head = domino;
            dominoLine.push_front(domino);
            placedDominoes++;
            return domino;
        }
    }
    return nullptr;
}

DominoNode* DominoesAverageCase::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    const auto& dominoList = dominoMap[tail->rightSymbol];
    for (auto& domino : dominoList) {
        if (!domino->isPlaced) {
            if (domino->rightSymbol == tail->rightSymbol) {
                std::swap(domino->leftSymbol, domino->rightSymbol); // Flip domino
            }
            domino->isPlaced = true;
            tail = domino;
            dominoLine.push_back(domino);
            placedDominoes++;
            return domino;
        }
    }
    return nullptr;
}

bool DominoesAverageCase::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void DominoesAverageCase::displayDominoLine(std::ostream& stream) const {
    for (const auto& domino : dominoLine) {
        stream << domino->leftSymbol << ":" << domino->rightSymbol << " ";
    }
}
