#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "DominoesAverageCase.h"
#include "DominoesWorstCase.h"
#include "DominoesConvoluted.h"

class DominoUtils {
private:
    static std::string readFirstLine(const std::string& filename);

    template<typename ReturnType>
    static ReturnType createDomino(const std::string& line);

    template<typename ReturnType>
    static std::list<ReturnType> getInputDominoesGeneric(const std::string& filename);

public:
    static DominoNode* getStartingDomino(const std::string& filename);
    static std::pair<std::string, std::string> getStartingDominoConvoluted(const std::string& filename);
    static std::list<DominoNode*> getInputDominoes(const std::string& filename);
    static std::list<std::pair<std::string, std::string>> getInputDominoesConvoluted(const std::string& filename);
    static std::string getOutputDominoes(const std::string& filename);

    template<class DominoImplementation>
    static void createDominoLine(DominoImplementation& dominoLine);
};

DominoNode* DominoUtils::getStartingDomino(const std::string& filename) {
    std::string line = readFirstLine(filename);
    return createDomino<DominoNode*>(line);
}

std::pair<std::string, std::string> DominoUtils::getStartingDominoConvoluted(const std::string& filename) {
    std::string line = readFirstLine(filename);
    return createDomino<std::pair<std::string, std::string>>(line);
}

std::list<DominoNode*> DominoUtils::getInputDominoes(const std::string& filename) {
    return getInputDominoesGeneric<DominoNode*>(filename);
}

std::list<std::pair<std::string, std::string>> DominoUtils::getInputDominoesConvoluted(const std::string& filename) {
    return getInputDominoesGeneric<std::pair<std::string, std::string>>(filename);
}

std::string DominoUtils::getOutputDominoes(const std::string& filename) {
    return readFirstLine(filename);
}

template<class DominoImplementation>
void DominoUtils::createDominoLine(DominoImplementation& dominoLine) {
    while (!dominoLine.checkLineCompleted()) {
        dominoLine.addLeftDomino();
        if (dominoLine.checkLineCompleted()) break;
        dominoLine.addRightDomino();
    }
}

std::string DominoUtils::readFirstLine(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::string line;
    std::getline(file, line);
    return line;
}

template<typename ReturnType>
std::list<ReturnType> DominoUtils::getInputDominoesGeneric(const std::string& filename) {
    std::list<ReturnType> dominoes;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::string line;
    while (getline(file, line)) {
        dominoes.push_back(createDomino<ReturnType>(line));
    }
    return dominoes;
}

template<typename ReturnType>
ReturnType DominoUtils::createDomino(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) {
        throw std::runtime_error("Invalid domino format");
    }

    const std::string leftSymbol = line.substr(0, colonPos);
    const std::string rightSymbol = line.substr(colonPos + 1);

    if constexpr (std::is_same_v<ReturnType, DominoNode*>) {
        return new DominoNode(leftSymbol, rightSymbol);
    } else {
        return std::make_pair(leftSymbol, rightSymbol);
    }
}