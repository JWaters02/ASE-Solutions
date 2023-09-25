#include "Coordinate.h"

Coordinate::Coordinate(int x, int y)
{
    this->xco = x;
    this->yco = y;
}

void Coordinate::display() const
{
    std::cout << '(' << xco << ',' << yco << ')' << std::endl;
}