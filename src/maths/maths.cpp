#include "maths.h"

void calculerCercleCirconscrit(Mesh *mesh, int idTriangle)
{
    Triangle *triangle;
    triangle = &(mesh->Triangles[idTriangle]);

    Point A = mesh->Vertices[triangle->sommetsID[0]];
    Point B = mesh->Vertices[triangle->sommetsID[1]];
    Point C = mesh->Vertices[triangle->sommetsID[2]];

    double mx1 = (A.x + B.x) / 2.0;
    double my1 = (A.y + B.y) / 2.0;
    double mx2 = (A.x + C.x) / 2.0;
    double my2 = (A.y + C.y) / 2.0;

    // Pentes des côtés
    double slopeAB = (B.y - A.y) / (B.x - A.x);
    double slopeAC = (C.y - A.y) / (C.x - A.x);

    // Pentes des médiatrices (perpendiculaires)
    double perpSlopeAB = -1.0 / slopeAB;
    double perpSlopeAC = -1.0 / slopeAC;

    // Résolution des équations pour trouver le centre
    double xCentre = (perpSlopeAC * mx2 - perpSlopeAB * mx1 + my1 - my2) / (perpSlopeAC - perpSlopeAB);
    double yCentre = perpSlopeAB * (xCentre - mx1) + my1;

    // Calcul du rayon
    double dx = xCentre - A.x;
    double dy = yCentre - A.y;
    double r = sqrt(dx * dx + dy * dy);

    // Affectation des résultats
    triangle->centre_circ.x = xCentre;
    triangle->centre_circ.y = yCentre;

    triangle->rayon_circ = r;
}


bool pointDansCercleCirconscrit(Point *point, Mesh *mesh, int idTriangle) 
{
    double dx = point->x - mesh->Triangles[idTriangle].centre_circ.x;
    double dy = point->y - mesh->Triangles[idTriangle].centre_circ.y;
    double distance = sqrt(dx * dx + dy * dy);

    return distance <= mesh->Triangles[idTriangle].rayon_circ;
}