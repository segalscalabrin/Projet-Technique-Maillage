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
    bool areteBord;
    bool areteValide;
};

struct Triangle
{
    array<int,3> sommetsID;
    array<int,3> aretesID;

    Point centre_circ;
    double rayon_circ;

    bool triangleValide;
};

struct Mesh
{
    int nbVertices;
    int nbEdges;
    int nbEdgesAll;
    int nbTriangles;

    vector<Point> Vertices;
    vector<Arete> EdgesMesh;
    vector<Arete> EdgeAll;
    vector<Triangle> Triangles;
};

struct Cavite
{
    vector<Arete> aretes;
    vector<int> areteID;
};

#endif // INCLUDE_H