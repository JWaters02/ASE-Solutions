#ifndef ASE_SOLUTIONS_DOMINOESAVERAGECASE_H
#define ASE_SOLUTIONS_DOMINOESAVERAGECASE_H

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
    void displayDominoLine() const override;
};

#endif //ASE_SOLUTIONS_DOMINOESAVERAGECASE_H