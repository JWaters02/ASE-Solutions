#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "DominoesWorstCase.h"
#include "DominoesAverageCase.h"

class DominoUtils {
public:
    static DominoNode* getStartingDomino(const std::string& filename);
    static std::list<DominoNode*> getInputDominoes(const std::string& filename);
    static std::string getOutputDominoes(const std::string& filename);

    template<class T>
    static void createDominoLine(T& dominoLine);
};

DominoNode* DominoUtils::getStartingDomino(const std::string& filename) {
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

std::list<DominoNode*> DominoUtils::getInputDominoes(const std::string& filename) {
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

std::string DominoUtils::getOutputDominoes(const std::string &filename) {
    std::string outputDominoes = "";
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);
    outputDominoes += line;

    file.close();
    return outputDominoes;
}

template<class T>
void DominoUtils::createDominoLine(T& dominoLine) {
    int i = 0;
    while (!dominoLine.checkLineCompleted()) {
        i++;
        //if (i == 10) break;
        dominoLine.addLeftDomino();
        if (dominoLine.checkLineCompleted()) break;
        dominoLine.addRightDomino();
    }
}
