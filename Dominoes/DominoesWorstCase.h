#pragma once

#include <map>
#include <unordered_set>

#include "DominoesInterface.h"

class DominoesWorstCase final : public DominoesInterface {
private:
    DominoNode* head; // Leftmost domino
    DominoNode* tail; // Rightmost domino

    int placedDominoes;
    int totalDominoes;

    std::multimap<std::string, DominoNode*> dominoMap;
    std::unordered_set<DominoNode*> unplacedDominoes;
    std::list<DominoNode*> dominoLine;

    DominoNode* placeDomino(DominoNode* domino);

public:
    DominoesWorstCase(DominoNode* startingDomino, const std::list<DominoNode*>& inputDominoes);
    ~DominoesWorstCase() override;

    DominoNode* addLeftDomino() override;
    DominoNode* addRightDomino() override;

    bool checkLineCompleted() const override;
    void displayDominoLine(std::ostream& stream) const override;
};