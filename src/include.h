#ifndef INCLUDE_H
#define INCLUDE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>

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
    array<Arete,3> aretes;
    array<int, 3> triVoisins; // voisins[i] = place du triangle voisin dans mesh.triangles par l'arete aretes[i]

    int couleur;
    // -1 : non def
    // 0 : exterieur
    // 1 : interieur

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
    vector<int> voisins;
};

#endif // INCLUDE_H