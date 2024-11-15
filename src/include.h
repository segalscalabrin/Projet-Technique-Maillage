#ifndef INCLUDE_H
#define INCLUDE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y; 
};

struct Triangle
{
    array<Point, 3> sommets;
    array<int, 3> voisins;

    Point centre_circ;
    double rayon_circ;

    bool valide;
};

#endif // INCLUDE_H