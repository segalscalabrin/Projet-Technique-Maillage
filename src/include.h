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
    int IDpt1;
    int IDpt2;
    bool areteValide;
};

struct Triangle
{
    array<int,3> sommetsID;

    Point centre_circ;
    double rayon_circ;

    bool triangleValide;
};

struct Mesh
{
    int nbVertices;
    int nbEdges;
    int nbTriangles;

    vector<Point> Vertices;
    vector<Arete> EdgesMesh;
    vector<Triangle> Triangles;
};

struct Cavite
{
    vector<Arete> aretes;
};

#endif // INCLUDE_H