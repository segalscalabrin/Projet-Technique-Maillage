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

struct Arete
{
    int pt1;
    int pt2;
    bool areteValide;
};


struct Triangle
{
    array<Point, 3> sommets;
    array<int,3> sommetID; // attention a initialiser 
    array<int, 3> voisins;

    Point centre_circ;
    double rayon_circ;

    bool valide;
};

struct Cavite
{
    vector<Point> sommets; 
    vector<int> sommetsID; 
    vector<Arete> aretes;
};

struct Mesh
{
    int nbVertices;
    int nbEdges;
    int nbTriangles;

    vector<double> Vertices;
    vector<double> Edges;
    vector<double> Triangles;
};

#endif // INCLUDE_H