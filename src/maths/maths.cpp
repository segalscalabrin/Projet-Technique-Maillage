#include "maths.h"

void calculerCercleCirconscrit(Triangle *t)
{
    Point A = t->sommets[0];
    Point B = t->sommets[1];
    Point C = t->sommets[2];

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
    t->centre_circ.x = xCentre;
    t->centre_circ.y = yCentre;

    t->rayon_circ = r;
}


bool pointDansCercleCirconscrit(Triangle *triangle, Point *point) 
{
    double dx = point->x - triangle->centre_circ.x;
    double dy = point->y - triangle->centre_circ.y;
    double distance = sqrt(dx * dx + dy * dy);

    return distance <= triangle->rayon_circ;
}