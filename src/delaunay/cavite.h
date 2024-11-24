#include "include.h"

#include "../src/maths/maths.h"


void ajouterAreteACavite(Mesh *mesh, vector<Arete> *cavite, Arete arete);

void ajouterTriangleACavite(Mesh *mesh, vector<Arete> *cavite, unsigned int t);

vector<Arete> idCavite(Mesh *mesh, Point *pt);

void reconnectionCavite(Point p, int ptID, Cavite cav, vector<Triangle> *triangulation);