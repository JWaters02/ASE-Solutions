#ifndef ASE_SOLUTIONS_COORDINATE_H
#define ASE_SOLUTIONS_COORDINATE_H

#include <iostream>

struct Coordinate
{
public:
    int xco;
    int yco;

public:
    Coordinate(int, int);
    void display() const;
};

#endif //ASE_SOLUTIONS_COORDINATE_H
