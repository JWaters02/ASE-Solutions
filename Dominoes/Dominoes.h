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
    DominoNode* startDomino;

    int placedDominoes;
    int totalDominoes;

    std::unordered_map<std::string, DominoNode*> leftSymbolMap;
    std::unordered_map<std::string, DominoNode*> rightSymbolMap;

    void insertInMap(DominoNode* domino) {
        leftSymbolMap[domino->leftSymbol] = domino;
        rightSymbolMap[domino->rightSymbol] = domino;
    }

public:
    Dominoes(DominoNode* startingDomino, const std::vector<DominoNode*>& inputDominoes);
    ~Dominoes();

    // When called, determines and returns the next domino to be placed in the line to the left
    DominoNode* addLeftDomino();
    // When called, determines and returns the next domino to be placed in the line to the right
    DominoNode* addRightDomino();

    bool checkLineCompleted() const;
    void displayDominoLine() const;
};


#endif //ASE_SOLUTIONS_DOMINOES_H
