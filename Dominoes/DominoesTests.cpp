#include <gtest/gtest.h>
#include <iostream>

#include "DominoUtils.h"

DominoUtils dominoUtils;
std::string startingDominoFilename = "dominoes-test_data/";

template<class DominoImplementation>
void testDominoLineScenario(std::string path) {
    DominoNode* startingDomino = dominoUtils.getStartingDomino(path + "starting-domino.txt");
    const std::list<DominoNode*> inputDominoes = dominoUtils.getInputDominoes(path + "input-uncoloured.txt");
    const std::string expectedDominoes = dominoUtils.getOutputDominoes(path + "output-left_right_turns.txt");

    DominoImplementation dominoLine(startingDomino, inputDominoes);
    dominoUtils.createDominoLine(dominoLine);
    std::stringstream ss;
    dominoLine.displayDominoLine(ss);
    std::string actualDominoes = ss.str();

    EXPECT_EQ(expectedDominoes, actualDominoes);
}

TEST(DominoesWorstCase, Example) {
    std::string path = startingDominoFilename + "example/example-";
    testDominoLineScenario<DominoesWorstCase>(path);
}

TEST(DominoesAverageCase, Example) {
    std::string path = startingDominoFilename + "example/example-";
    testDominoLineScenario<DominoesAverageCase>(path);
}

TEST(DominoesWorstCase, 10) {
    std::string path = startingDominoFilename + "10/10-";
    testDominoLineScenario<DominoesWorstCase>(path);
}

TEST(DominoesAverageCase, 10) {
    std::string path = startingDominoFilename + "10/10-";
    testDominoLineScenario<DominoesAverageCase>(path);
}

TEST(DominoesWorstCase, 600) {
    std::string path = startingDominoFilename + "600/600-";
    testDominoLineScenario<DominoesWorstCase>(path);
}

TEST(DominoesAverageCase, 600) {
    std::string path = startingDominoFilename + "600/600-";
    testDominoLineScenario<DominoesAverageCase>(path);
}

TEST(DominoesWorstCase, 10K) {
    std::string path = startingDominoFilename + "10K/10K-";
    testDominoLineScenario<DominoesWorstCase>(path);
}

TEST(DominoesAverageCase, 10K) {
    std::string path = startingDominoFilename + "10K/10K-";
    testDominoLineScenario<DominoesAverageCase>(path);
}