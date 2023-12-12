#include "DominoesConvoluted.h"

DominoesConvoluted::DominoesConvoluted(std::pair<BlueSymbol, RedSymbol> startingDomino,
                                       std::list<std::pair<BlueSymbol, RedSymbol>> inputDominoes) {
    // 1. Initialize list A with the input dominoes.
    std::list<std::pair<BlueSymbol, RedSymbol>> listA = inputDominoes;

    // 2. Initialize positions with the starting domino's red symbol
    std::list<std::pair<RedSymbol, PositionNumber>> listP;
    listP.push_back({startingDomino.second, 0});

    // 3. Iteratively calculate the positions of the red symbols
    int distance = 1;
    while (distance < inputDominoes.size() + 1) {
        // a. Make a copy of List A called ListB
        std::list<std::pair<BlueSymbol, RedSymbol>> listB = listA;

        // b. Create an empty list of symbol pairs called ListC
        std::list<std::pair<BlueSymbol, RedSymbol>> listC;

        // c. Sort List A based on the second symbol, and sort List B based on the first symbol
        listA.sort([](const auto& a, const auto& b) {
            return a.second < b.second;
        });
        listB.sort([](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        // d. Sort List P based on the symbol
        listP.sort([](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        // e. Use iterators to advance through Lists A, B, and P
        auto itA = listA.begin();
        auto itB = listB.begin();
        auto itP = listP.begin();

        // Until we reach the end of List B
        // Skip the if-conditions involving Lists A or P if the end of that list has already been reached
        while (itB != listB.end()) {
            // If b1 = a2, append (a1, b2) to List C, and advance Lists A and B once
            if (itA != listA.end() && itB->first == itA->second) {
                listC.push_back({itA->first, itB->second});
                itA++;
                itB++;
            }
            // Else if b1 = p1, append (b2, p2+distance) to the front of List P, and advance Lists B and P once
            else if (itP != listP.end() && itB->first == itP->first) {
                listP.push_front({itB->second, itP->second + distance});
                itB++;
                itP++;
            }
            // Else if b1 > p1, advance List P once
            else if (itP != listP.end() && itB->first > itP->first) {
                itP++;
            }
            // Else if b1 > a2, advance List A once
            else if (itA != listA.end() && itB->first > itA->second) {
                itA++;
            }
        }

        // f. Overwrite List A with List C
        listA = listC;

        // Double the distance at each iteration
        distance *= 2;
    }

    // 4. Sort List P based on the position numbers
    listP.sort([](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // 5. Build the line of dominoes by iterating through List P
    BlueSymbol previousBlue = startingDomino.first;
    for (const auto& position : listP) {
        dominoLine.push_back({previousBlue, position.first});
        previousBlue = position.first;
    }
}

void DominoesConvoluted::displayDominoLine(std::ostream &stream) const {
    for (const auto &domino : dominoLine) {
        stream << domino.first << ":" << domino.second << " ";
    }
}
