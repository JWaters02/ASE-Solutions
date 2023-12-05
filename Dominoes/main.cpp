#include <iostream>
#include <string>

#include "DominoUtils.h"

int main() {
    try {
        DominoUtils dominoUtils;
        /*DominoNode* startingDomino = dominoUtils.getStartingDomino("dominoes-test_data/100/100-starting-domino.txt");
        const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes("dominoes-test_data/100/100-input-uncoloured.txt");
        DominoesAverageCase dominoLine(startingDomino, inputDominoes);
        dominoUtils.createDominoLine(dominoLine);
        dominoLine.displayDominoLine(std::cerr);*/

        std::pair<std::string, std::string> startingDomino = dominoUtils.getStartingDominoConvoluted("dominoes-test_data/example/example-starting-domino.txt");
        const std::list<std::pair<std::string, std::string>> inputDominoes = dominoUtils.getInputDominoesConvoluted("dominoes-test_data/example/example-input-uncoloured.txt");

        DominoesConvoluted dominoLine(startingDomino, inputDominoes);
        dominoLine.displayDominoLine(std::cout);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}