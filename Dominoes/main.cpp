#include <iostream>
#include <string>

#include "DominoUtils.h"

int main() {
    try {
        DominoUtils dominoUtils;
        DominoNode* startingDomino = dominoUtils.getStartingDomino("dominoes-test_data/example/example-starting-domino.txt");
        const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes("dominoes-test_data/example/example-input-uncoloured.txt");
        DominoesWorstCase dominoLine(startingDomino, inputDominoes);
        dominoUtils.createDominoLine(dominoLine);
        dominoLine.displayDominoLine();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}