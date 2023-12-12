#include <iostream>
#include <string>
#include <chrono>
#include <utility>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include "DominoUtils.h"

DominoUtils dominoUtils;

template<class DominoImplementation>
std::chrono::nanoseconds timingCreateLineTest(int numTests, std::string path) {
    DominoNode* startingDomino = dominoUtils.getStartingDomino(path + "starting-domino.txt");
    const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes(path + "input-uncoloured.txt");

    DominoImplementation dominoLine(startingDomino, inputDominoes);

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < numTests; ++i) dominoUtils.createDominoLine(dominoLine);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::chrono::nanoseconds meanTimePerLookup = timeTaken / numTests;

    return meanTimePerLookup;
}

template<class DominoImplementation>
std::chrono::nanoseconds timingFullTest(int numTests, std::string path) {
    DominoNode* startingDomino = dominoUtils.getStartingDomino(path + "starting-domino.txt");
    const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes(path + "input-uncoloured.txt");

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < numTests; ++i) {
        DominoImplementation dominoLine(startingDomino, inputDominoes);
        dominoUtils.createDominoLine(dominoLine);
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::chrono::nanoseconds meanTimePerLookup = timeTaken / numTests;

    return meanTimePerLookup;
}

std::chrono::nanoseconds timingFullTestConvoluted(int numTests, std::string path) {
    std::pair<std::string, std::string> startingDomino = dominoUtils.getStartingDominoConvoluted(path + "starting-domino.txt");
    std::list<std::pair<std::string, std::string>> inputDominoes = dominoUtils.getInputDominoesConvoluted(path + "input-coloured.txt");

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < numTests; ++i) {
        DominoesConvoluted dominoLine(startingDomino, inputDominoes);
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::chrono::nanoseconds meanTimePerLookup = timeTaken / numTests;

    return meanTimePerLookup;
}

void iterateTests() {
    std::vector<std::string> testSizes = {
            "10", "30", "60",
            "100", "300", "600",
            "1K", "3K", "6K",
            "10K", "30K", "60K",
            "100K", "300K", "600K",
            "1M"
    };
    int numTests = 1;

    std::vector<std::chrono::nanoseconds> timesWorstCaseCreateLine;
    std::vector<std::chrono::nanoseconds> timesAverageCaseCreateLine;
    std::vector<std::chrono::nanoseconds> timesWorstCaseFull;
    std::vector<std::chrono::nanoseconds> timesAverageCaseFull;
    std::vector<std::chrono::nanoseconds> timesConvolutedFull;

    for (std::string testSize : testSizes) {
        std::cout << "Running tests for " << testSize << " dominoes" << std::endl;
        std::string path = "dominoes-test_data/" + testSize + "/" + testSize + "-";
        timesWorstCaseCreateLine.push_back(timingCreateLineTest<DominoesWorstCase>(numTests, path));
        timesAverageCaseCreateLine.push_back(timingCreateLineTest<DominoesAverageCase>(numTests, path));
//        timesWorstCaseFull.push_back(timingFullTest<DominoesWorstCase>(numTests, path));
//        timesAverageCaseFull.push_back(timingFullTest<DominoesAverageCase>(numTests, path));
//        timesConvolutedFull.push_back(timingFullTestConvoluted(numTests, path));
    }

    std::cout << "Writing results to file" << std::endl;
    std::ofstream file;
    file.open("benchmarkCreateLineTest2.csv");
    file << "testSize,worstCaseTime,averageCaseTime\n";
    for (int i = 0; i < testSizes.size(); ++i) {
        file << testSizes[i] << "," << timesWorstCaseCreateLine[i].count() << ","
             << timesAverageCaseCreateLine[i].count() << "\n";
    }
    file.close();

//    file.open("benchmarkFullTest.csv");
//    file << "testSize,worstCaseTime,averageCaseTime,convolutedTime\n";
//    for (int i = 0; i < testSizes.size(); ++i) {
//        file << testSizes[i] << ","
//             << timesWorstCaseFull[i].count() << ","
//             << timesAverageCaseFull[i].count() << ","
//             << timesConvolutedFull[i].count() << "\n";
//    }
//    file.close();
}

int main() {
    //iterateTests();

    Py_Initialize();
//    PyRun_SimpleString("exec(open(\"benchmarkCreateLineTest.py\").read())");
    PyRun_SimpleString("exec(open(\"benchmarkFullTest.py\").read())");
    Py_Finalize();

    return 0;
}