#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::string BlueSymbol;
typedef std::string RedSymbol;
typedef int PositionNumber;

class DominoesConvoluted {
private:
    std::list<std::pair<BlueSymbol, RedSymbol>> dominoLine;

public:
    DominoesConvoluted(std::pair<BlueSymbol, RedSymbol> startingDomino,
                       std::list<std::pair<BlueSymbol, RedSymbol>> inputDominoes);

    void displayDominoLine(std::ostream& stream = std::cout) const;
};

// Usage Example:
// std::list<std::pair<Symbol, Symbol>> dominoes = {{'A', 'B'}, {'C', 'D'}, ...};
// DominoLine dl({'X', 'Y'}, dominoes);
// dl.displayLine();
