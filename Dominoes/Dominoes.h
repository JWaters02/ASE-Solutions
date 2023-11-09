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
    std::list<DominoNode> startingDominoes;

public:
    Dominoes(const DominoNode& startingDomino, const std::list<DominoNode>& dominoes);
    ~Dominoes();

    // When called, the next domino in the startingDominoes list is added to the dominoLine on the left
    DominoNode addLeftDomino(DominoNode domino);
    // When called, the next domino in the startingDominoes list is added to the dominoLine on the right
    DominoNode addRightDomino(DominoNode domino);

    bool checkLineCompleted();
    void displayDominoLine();
};


#endif //ASE_SOLUTIONS_DOMINOES_H
