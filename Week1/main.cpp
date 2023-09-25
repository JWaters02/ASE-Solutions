#include <iostream>

#include "Coordinate.h"

int main() {
    Coordinate p1 = Coordinate(1,2); // stack allocation
    Coordinate p2(3,7); // stack allocation
    p1.xco = 4;
    p2.yco = p2.yco + 5;
    p1.display();
    p2.display();

    Coordinate* coPtr = new Coordinate(7,8);  // heap allocation
    coPtr->display(); // same as (*coPtr).display();

    Coordinate co2 = *coPtr;
    Coordinate* coPtr2 = &co2;

    delete coPtr; // heap deallocation
    coPtr = nullptr; // set to null pointer to avoid dangling pointer
    return 0;
}
