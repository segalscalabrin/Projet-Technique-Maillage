#include "include.h"

#include "../src/maths/maths.h"


void ajouterAreteACavite(Mesh *mesh, vector<Arete> *cavite, Arete arete);

void ajouterTriangleACavite(Mesh *mesh, vector<Arete> *cavite, unsigned int t);

vector<Arete> idCavite(Mesh *mesh, Point *pt);

void reconnectionCavite(vector<Arete> cavite, Mesh *mesh, Point pt, int IDpt);