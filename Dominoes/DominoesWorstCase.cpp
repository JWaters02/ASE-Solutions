#include "DominoesWorstCase.h"

DominoesWorstCase::DominoesWorstCase(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes) {
    startingDomino->isPlaced = true;
    head = tail = startingDomino;
    dominoLine.push_back(startingDomino);

    for (auto& domino : inputDominoes) {
        dominoMap.insert({domino->leftSymbol, domino});
        dominoMap.insert({domino->rightSymbol, domino});
    }

    placedDominoes = 1;
    totalDominoes = inputDominoes.size() + 1;
}

DominoesWorstCase::~DominoesWorstCase() {
    for (const auto& domino : dominoLine) {
        delete domino;
    }
}

DominoNode* DominoesWorstCase::addDomino(DominoNode*& end, bool addToLeft) {
    if (end == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    std::string symbol = addToLeft ? end->leftSymbol : end->rightSymbol;
    auto range = dominoMap.equal_range(symbol);
    DominoNode* matchingDomino = nullptr;

    if (range.first != range.second) {
        DominoNode* domino = range.first->second;
        if (!domino->isPlaced) {
            if ((addToLeft && domino->leftSymbol == symbol) ||
                (!addToLeft && domino->rightSymbol == symbol)) {
                std::swap(domino->leftSymbol, domino->rightSymbol);
            }
            matchingDomino = domino;
            dominoMap.erase(range.first);
        }
    }

    if (matchingDomino) {
        end = matchingDomino;
        addToLeft ? dominoLine.push_front(matchingDomino) : dominoLine.push_back(matchingDomino);
        matchingDomino->isPlaced = true;
        placedDominoes++;

        // Correctly erase the placed domino from the multimap - as it can contain multiple elements with the same key
        // And it only ever does two iterations to erase the correct symbol
        // But with equal_range it is O(log n + m) anyway
        range = addToLeft ? dominoMap.equal_range(matchingDomino->leftSymbol)
                          : dominoMap.equal_range(matchingDomino->rightSymbol);
        for (auto it = range.first; it != range.second;) {
            if (it->second == matchingDomino) {
                it = dominoMap.erase(it);
            } else {
                ++it;
            }
        }
        return matchingDomino;
    }

    return nullptr;
}

DominoNode* DominoesWorstCase::addLeftDomino() {
    return addDomino(head, true);
}

DominoNode* DominoesWorstCase::addRightDomino() {
    return addDomino(tail, false);
}

bool DominoesWorstCase::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void DominoesWorstCase::displayDominoLine(std::ostream& stream) const {
    for (const auto& domino : dominoLine) {
        stream << domino->leftSymbol << ":" << domino->rightSymbol << " ";
    }
}