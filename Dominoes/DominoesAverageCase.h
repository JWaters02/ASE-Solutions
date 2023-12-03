#pragma once

#include <unordered_map>

#include "DominoesInterface.h"

class DominoesAverageCase final : public DominoesInterface {
private:
    DominoNode* head; // Leftmost domino
    DominoNode* tail; // Rightmost domino

    int placedDominoes;
    int totalDominoes;

    std::unordered_map<std::string, std::list<DominoNode*>> dominoMap;
    std::list<DominoNode*> dominoLine;

public:
    DominoesAverageCase(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes);
    ~DominoesAverageCase() override;

    DominoNode* addLeftDomino() override;
    DominoNode* addRightDomino() override;

    bool checkLineCompleted() const override;
    void displayDominoLine(std::ostream& stream) const override;
};