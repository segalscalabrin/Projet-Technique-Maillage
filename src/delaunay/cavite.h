#include "include.h"

#include "../src/maths/maths.h"


void ajouterAreteACavite(Triangle *triangle, Cavite *cavite, int currentEdgeID);

void ajouterTriangleACavite(Mesh *mesh, Cavite *cavite, unsigned int t);

Cavite idCavite(Mesh *mesh, Point *pt);

void addVoisins(Mesh *mesh, int triDebutID, int triFinID);

void reconnectionCavite(Cavite *cavite, Mesh *mesh, Point pt, int IDpt);