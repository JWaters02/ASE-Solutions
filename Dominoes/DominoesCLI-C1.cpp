#include <iostream>
#include <string>
#include <list>

#include "DominoUtils.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <starting-domino-file> <domino-collection-file>" << std::endl;
        return 1;
    }

    try {
        DominoUtils dominoUtils;
        std::pair<std::string, std::string> startingDomino = dominoUtils.getStartingDominoConvoluted(argv[1]);
        const std::list<std::pair<std::string, std::string>> inputDominoes = dominoUtils.getInputDominoesConvoluted(argv[2]);

        DominoesConvoluted dominoLine(startingDomino, inputDominoes);
        dominoLine.displayDominoLine(std::cout);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
