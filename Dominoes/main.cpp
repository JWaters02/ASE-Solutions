#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Dominoes.h"

DominoNode* getStartingDomino(const std::string& filename);
std::list<DominoNode*> getInputDominoes(const std::string& filename);
void createDominoLine(Dominoes& dominoLine);

int main() {
    try {
        DominoNode* startingDomino = getStartingDomino("dominoes-test_data/10/10-starting-domino.txt");
        std::list<DominoNode*> inputDominoes = getInputDominoes("dominoes-test_data/10/10-input-uncoloured.txt");
        
        Dominoes dominoLine(startingDomino, inputDominoes);
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

    size_t colonPos = line.find(':');
    if (colonPos != std::string::npos) {
        std::string leftSymbol = line.substr(0, colonPos);
        std::string rightSymbol = line.substr(colonPos + 1);
        return new DominoNode(leftSymbol, rightSymbol);
    }

    throw std::runtime_error("Invalid starting domino");
}

void createDominoLine(Dominoes& dominoLine) {
    int i = 0;
    while (!dominoLine.checkLineCompleted()) {
        i++;
        if (i % 20 == 0) break;
        dominoLine.addLeftDomino();
        dominoLine.displayDominoLine();
        if (dominoLine.checkLineCompleted()) break;
        dominoLine.addRightDomino();
        dominoLine.displayDominoLine();
    }
}