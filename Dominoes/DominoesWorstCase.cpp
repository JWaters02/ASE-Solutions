#include "DominoesWorstCase.h"

DominoesWorstCase::DominoesWorstCase(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes) {
    startingDomino->isPlaced = true;
    head = tail = startingDomino;
    dominoLine.push_back(startingDomino);

    // Populate the dominoMap hash map with DominoNode objects
    // For each domino, create a new DominoNode and insert it into the map
    // Then track unplaced dominoes
    for (auto& domino : inputDominoes) {
        dominoMap.insert({domino->leftSymbol, domino});
        dominoMap.insert({domino->rightSymbol, domino});
        unplacedDominoes.insert(domino);
    }

    // Remove the starting domino from unplaced dominoes
    unplacedDominoes.erase(startingDomino);

    placedDominoes = 1;
    totalDominoes = inputDominoes.size() + 1;
}

DominoesWorstCase::~DominoesWorstCase() {
    for (const auto& domino : dominoLine) {
        delete domino;
    }
}

DominoNode* DominoesWorstCase::placeDomino(DominoNode* domino) {
    domino->isPlaced = true;
    placedDominoes++;
    dominoMap.erase(domino->leftSymbol);
    dominoMap.erase(domino->rightSymbol);
    unplacedDominoes.erase(domino);
    return domino;
}

DominoNode* DominoesWorstCase::addLeftDomino() {
    if (head == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    // Get all dominoes with the same left symbol as the head
    DominoNode* matchingDomino = nullptr;
    auto range = dominoMap.equal_range(head->leftSymbol);

    for (auto it = range.first; it != range.second; ++it) {
        DominoNode* domino = it->second;
        if (!domino->isPlaced && unplacedDominoes.find(domino) != unplacedDominoes.end()) {
            if (domino->leftSymbol == head->leftSymbol) {
                std::swap(domino->leftSymbol, domino->rightSymbol); // Flip domino
            }
            matchingDomino = domino;
            break;
        }
    }

    if (matchingDomino) {
        head = matchingDomino;
        dominoLine.push_front(matchingDomino);
        matchingDomino->isPlaced = true;
        placedDominoes++;
        // Correctly erase the placed domino from the multimap
        auto range = dominoMap.equal_range(matchingDomino->leftSymbol);
        for (auto it = range.first; it != range.second;) {
            if (it->second == matchingDomino) {
                it = dominoMap.erase(it); // Erase and move to the next element
            } else {
                ++it; // Move to the next element without erasing
            }
        }

        range = dominoMap.equal_range(matchingDomino->rightSymbol);
        for (auto it = range.first; it != range.second;) {
            if (it->second == matchingDomino) {
                it = dominoMap.erase(it); // Erase and move to the next element
            } else {
                ++it; // Move to the next element without erasing
            }
        }
        unplacedDominoes.erase(matchingDomino);
        return matchingDomino;
    }

    return nullptr;
}

DominoNode* DominoesWorstCase::addRightDomino() {
    if (tail == nullptr) {
        throw std::logic_error("No starting domino in the line");
    }

    // Get all dominoes with the same right symbol as the tail
    DominoNode* matchingDomino = nullptr;
    auto range = dominoMap.equal_range(tail->rightSymbol);

    for (auto it = range.first; it != range.second; ++it) {
        DominoNode* domino = it->second;
        if (!domino->isPlaced && unplacedDominoes.find(domino) != unplacedDominoes.end()) {
            if (domino->rightSymbol == tail->rightSymbol) {
                std::swap(domino->leftSymbol, domino->rightSymbol);
            }
            matchingDomino = domino;
            break;
        }
    }

    if (matchingDomino) {
        tail = matchingDomino;
        dominoLine.push_back(matchingDomino);
        matchingDomino->isPlaced = true;
        placedDominoes++;

        // Correctly erase the placed domino from the multimap
        auto range = dominoMap.equal_range(matchingDomino->leftSymbol);
        for (auto it = range.first; it != range.second;) {
            if (it->second == matchingDomino) {
                it = dominoMap.erase(it); // Erase and move to the next element
            } else {
                ++it; // Move to the next element without erasing
            }
        }

        range = dominoMap.equal_range(matchingDomino->rightSymbol);
        for (auto it = range.first; it != range.second;) {
            if (it->second == matchingDomino) {
                it = dominoMap.erase(it); // Erase and move to the next element
            } else {
                ++it; // Move to the next element without erasing
            }
        }

        unplacedDominoes.erase(matchingDomino);
        return matchingDomino;
    }

    return nullptr;
}

bool DominoesWorstCase::checkLineCompleted() const {
    return placedDominoes == totalDominoes;
}

void DominoesWorstCase::displayDominoLine() const {
    for (const auto& domino : dominoLine) {
        std::cout << domino->leftSymbol << ":" << domino->rightSymbol << " ";
    }
    std::cout << std::endl;
}