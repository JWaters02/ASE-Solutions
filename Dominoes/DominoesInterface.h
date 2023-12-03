#ifndef ASE_SOLUTIONS_DOMINOES_H
#define ASE_SOLUTIONS_DOMINOES_H

#include <iostream>
#include <unordered_map>

struct DominoNode {
    std::string leftSymbol;
    std::string rightSymbol;
    bool isPlaced;

    DominoNode(const std::string& leftSymbol, const std::string& rightSymbol) {
        this->leftSymbol = leftSymbol;
        this->rightSymbol = rightSymbol;
        this->isPlaced = false;
    }
};

class DominoesInterface {
public:
    virtual ~DominoesInterface() = default;

    // When called, determines and returns the next domino to be placed in the line to the left
    virtual DominoNode* addLeftDomino() = 0;
    // When called, determines and returns the next domino to be placed in the line to the right
    virtual DominoNode* addRightDomino() = 0;

    virtual bool checkLineCompleted() const = 0;
    virtual void displayDominoLine() const = 0;
};


#endif //ASE_SOLUTIONS_DOMINOES_H
