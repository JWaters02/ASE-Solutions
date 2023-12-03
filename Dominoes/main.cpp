#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "DominoesInterface.h"
#include "DominoesWorstCase.h"
#include "DominoesAverageCase.h"

DominoNode* getStartingDomino(const std::string& filename);
std::list<DominoNode*> getInputDominoes(const std::string& filename);
void createDominoLine(DominoesWorstCase& dominoLine);

int main() {
    try {
        DominoNode* startingDomino = getStartingDomino("dominoes-test_data/example/example-starting-domino.txt");
        const std::list<DominoNode*> inputDominoes = getInputDominoes("dominoes-test_data/example/example-input-uncoloured.txt");
        
        DominoesWorstCase dominoLine(startingDomino, inputDominoes);
        createDominoLine(dominoLine);
        dominoLine.displayDominoLine();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}

std::list<DominoNode*> getInputDominoes(const std::string& filename) {
    std::list<DominoNode*> dominoes;
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string leftSymbol, rightSymbol;
        if (getline(iss, leftSymbol, ':') && getline(iss, rightSymbol)) {
            dominoes.push_back(new DominoNode(leftSymbol, rightSymbol));
        }
    }

    file.close();
    return dominoes;
}

DominoNode* getStartingDomino(const std::string& filename) {
    std::string line;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::getline(file, line);

    if (const size_t colonPos = line.find(':'); colonPos != std::string::npos) {
        const std::string leftSymbol = line.substr(0, colonPos);
        const std::string rightSymbol = line.substr(colonPos + 1);
        return new DominoNode(leftSymbol, rightSymbol);
    }

    throw std::runtime_error("Invalid starting domino");
}

void createDominoLine(DominoesWorstCase& dominoLine) {
    int i = 0;
    while (!dominoLine.checkLineCompleted()) {
        i++;
        if (i == 10) break;
        dominoLine.addLeftDomino();
        dominoLine.displayDominoLine();
        if (dominoLine.checkLineCompleted()) break;
        dominoLine.addRightDomino();
        dominoLine.displayDominoLine();
    }
}