#include "Dominoes.h"

Dominoes::Dominoes(const DominoNode &startingDomino, const std::list<DominoNode> &inputDominoes) {
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

    this->inputDominoes = inputDominoes;
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

DominoNode Dominoes::addLeftDomino() {
    return DominoNode{nullptr, nullptr};
}

DominoNode Dominoes::addRightDomino() {
    return DominoNode{nullptr, nullptr};
}

bool Dominoes::checkLineCompleted() {
    return false;
}

void Dominoes::displayDominoLine() {

}
