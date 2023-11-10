#ifndef ASE_SOLUTIONS_DOMINOES_H
#define ASE_SOLUTIONS_DOMINOES_H

#include <iostream>
#include <unordered_map>

struct DominoNode {
    std::string leftSymbol;
    std::string rightSymbol;
    DominoNode* next;
    DominoNode* prev;

    DominoNode(const std::string& leftSymbol, const std::string& rightSymbol) {
        this->leftSymbol = leftSymbol;
        this->rightSymbol = rightSymbol;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class Dominoes {
private:
    DominoNode* head;
    DominoNode* tail;

    std::unordered_map<std::string, DominoNode*> dominoLine;
    std::list<DominoNode> inputDominoes;

public:
    Dominoes(const DominoNode& startingDomino, const std::list<DominoNode>& inputDominoes);
    ~Dominoes();

    // When called, determines and returns the next domino to be placed in the line to the left
    DominoNode addLeftDomino();
    // When called, determines and returns the next domino to be placed in the line to the right
    DominoNode addRightDomino();

    bool checkLineCompleted();
    void displayDominoLine();
};


#endif //ASE_SOLUTIONS_DOMINOES_H
