#ifndef ASE_SOLUTIONS_DOMINOES_H
#define ASE_SOLUTIONS_DOMINOES_H

#include <iostream>
#include <unordered_map>

struct DominoNode {
    std::string leftSymbol;
    std::string rightSymbol;
    DominoNode* next;
    DominoNode* prev;
    bool isPlaced;

    DominoNode(const std::string& leftSymbol, const std::string& rightSymbol) {
        this->leftSymbol = leftSymbol;
        this->rightSymbol = rightSymbol;
        this->next = nullptr;
        this->prev = nullptr;
        this->isPlaced = false;
    }
};

class Dominoes {
private:
    DominoNode* head; // Leftmost domino
    DominoNode* tail; // Rightmost domino

    int placedDominoes;
    int totalDominoes;

    std::unordered_map<std::string, DominoNode*> dominoLine;

public:
    Dominoes(const DominoNode& startingDomino, const std::list<DominoNode>& inputDominoes);
    ~Dominoes();

    // When called, determines and returns the next domino to be placed in the line to the left
    DominoNode* addLeftDomino();
    // When called, determines and returns the next domino to be placed in the line to the right
    DominoNode* addRightDomino();

    bool checkLineCompleted() const;
    void displayDominoLine();
};


#endif //ASE_SOLUTIONS_DOMINOES_H
