#include "Dominoes.h"

Dominoes::Dominoes(const DominoNode &startingDomino, const std::list<DominoNode> &dominoes) {
    this->head = new DominoNode(startingDomino.leftSymbol, startingDomino.rightSymbol);
    this->tail = this->head;
    this->dominoLine[startingDomino.leftSymbol] = this->head;
    this->dominoLine[startingDomino.rightSymbol] = this->head;
    this->startingDominoes = dominoes;
}

DominoNode Dominoes::addLeftDomino(const DominoNode domino) {
    return domino;
}

DominoNode Dominoes::addRightDomino(const DominoNode domino) {
    return domino;
}

bool Dominoes::checkLineCompleted() {
    return false;
}

void Dominoes::displayDominoLine() {

}
