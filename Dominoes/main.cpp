#include <iostream>
#include <string>
#include <fstream>

#include "Dominoes.h"

DominoNode getStartingDomino(const std::string& filename);
std::list<DominoNode> getDominoes(const std::string& filename);

int main() {
    DominoNode startingDomino = getStartingDomino("dominoes.txt");
    std::list<DominoNode> dominoes = getDominoes("dominoes.txt");

    Dominoes dominoesLine(startingDomino, dominoes);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}

std::list<DominoNode> getDominoes(const std::string& filename) {
    std::list<DominoNode> dominoes;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        size_t colonPos = line.find(':');
        std::string leftSymbol = line.substr(0, colonPos);
        std::string rightSymbol = line.substr(colonPos + 1);
        dominoes.emplace_back(leftSymbol, rightSymbol);
    }

    return dominoes;
}

DominoNode getStartingDomino(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);
    size_t colonPos = line.find(':');
    std::string leftSymbol = line.substr(0, colonPos);
    std::string rightSymbol = line.substr(colonPos + 1);

    return {leftSymbol, rightSymbol};
}