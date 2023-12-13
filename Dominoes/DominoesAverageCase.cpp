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

DominoNode* DominoesAverageCase::addDomino(DominoNode*& end, bool addToLeft) {
    if (end == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    std::string symbol = addToLeft ? end->leftSymbol : end->rightSymbol;
    const auto& dominoList = dominoMap[symbol];
    for (auto& domino : dominoList) {
        if (!domino->isPlaced) {
            if ((addToLeft && domino->leftSymbol == symbol) ||
                (!addToLeft && domino->rightSymbol == symbol)) {
                std::swap(domino->leftSymbol, domino->rightSymbol);
            }
            domino->isPlaced = true;
            end = domino;
            addToLeft ? dominoLine.push_front(domino) : dominoLine.push_back(domino);
            placedDominoes++;
            return domino;
        }
    }
    return nullptr;
}

DominoNode* DominoesAverageCase::addLeftDomino() {
    return addDomino(head, true);
}

DominoNode* DominoesAverageCase::addRightDomino() {
    return addDomino(tail, false);
}

bool DominoesAverageCase::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void DominoesAverageCase::displayDominoLine(std::ostream& stream) const {
    for (const auto& domino : dominoLine) {
        stream << domino->leftSymbol << ":" << domino->rightSymbol << " ";
    }
}