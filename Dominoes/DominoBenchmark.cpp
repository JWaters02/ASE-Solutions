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
std::chrono::nanoseconds timingTest(int numTests, std::string path) {
    DominoNode* startingDomino = dominoUtils.getStartingDomino(path + "starting-domino.txt");
    const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes(path + "input-uncoloured.txt");
    const std::string expectedDominoes = dominoUtils.getOutputDominoes(path + "output-left_right_turns.txt");

    DominoImplementation dominoLine(startingDomino, inputDominoes);

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < numTests; ++i) dominoUtils.createDominoLine(dominoLine);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::chrono::nanoseconds meanTimePerLookup = timeTaken / numTests;

    return meanTimePerLookup;
}

void iterateTests() {
    std::vector<std::string> testSizes = {
            /*"10", "30", "60",
            "100", "300", "600",
            "1K", "3K", "6K",*/
            "10K", "30K", "60K",
            "100K", "300K", "600K",
            "1M"
    };
    int numTests = 1;

    std::vector<std::chrono::nanoseconds> times_worst_case;
    std::vector<std::chrono::nanoseconds> times_average_case;

    for (std::string testSize : testSizes) {
        std::cout << "Running tests for " << testSize << " dominoes" << std::endl;
        std::string path = "dominoes-test_data/" + testSize + "/" + testSize + "-";
        times_worst_case.push_back(timingTest<DominoesWorstCase>(numTests, path));
        times_average_case.push_back(timingTest<DominoesAverageCase>(numTests, path));
    }

    std::ofstream file;
    file.open("benchmarkGraphGen.csv");
    file << "testSize,worstCaseTime,averageCaseTime\n";
    for (int i = 0; i < testSizes.size(); ++i) {
        file << testSizes[i] << "," << times_worst_case[i].count() << "," << times_average_case[i].count() << "\n";
    }
    file.close();
}

int main() {
    //iterateTests();

    Py_Initialize();
    PyRun_SimpleString("exec(open(\"benchmarkGraphGen.py\").read())");
    Py_Finalize();

    return 0;
}