#include "maths.h"

/*void calculerCercleCirconscrit(Mesh *mesh, int idTriangle)
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

    printf("pente des mediatrice : %lf, %lf\n", slopeAB, slopeAC);

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
}*/

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

    double slopeAB = (B.x - A.x == 0) ? INFINITY : (B.y - A.y) / (B.x - A.x);
    double slopeAC = (C.x - A.x == 0) ? INFINITY : (C.y - A.y) / (C.x - A.x);

    double xCentre, yCentre;

    if (slopeAB == 0) { 
        // AB est horizontal, médiatrice verticale
        xCentre = mx1;
        if (slopeAC == INFINITY) { 
            // AC est vertical, médiatrice horizontale
            yCentre = my2;
        } else {
            // Médiatrice de AC a une pente définie
            double perpSlopeAC = -1.0 / slopeAC;
            yCentre = perpSlopeAC * (xCentre - mx2) + my2;
        }
    } else if (slopeAB == INFINITY) { 
        // AB est vertical, médiatrice horizontale
        yCentre = my1;
        if (slopeAC == 0) {
            // AC est horizontal, médiatrice verticale
            xCentre = mx2;
        } else {
            // Médiatrice de AC a une pente définie
            double perpSlopeAC = -1.0 / slopeAC;
            xCentre = (yCentre - my2) / perpSlopeAC + mx2;
        }
    } else if (slopeAC == 0) { 
        // AC est horizontal, médiatrice verticale
        xCentre = mx2;
        double perpSlopeAB = -1.0 / slopeAB;
        yCentre = perpSlopeAB * (xCentre - mx1) + my1;
    } else if (slopeAC == INFINITY) { 
        // AC est vertical, médiatrice horizontale
        yCentre = my2;
        double perpSlopeAB = -1.0 / slopeAB;
        xCentre = (yCentre - my1) / perpSlopeAB + mx1;
    } else {
        // Les deux médiatrices ont des pentes définies
        double perpSlopeAB = -1.0 / slopeAB;
        double perpSlopeAC = -1.0 / slopeAC;
        xCentre = (perpSlopeAC * mx2 - perpSlopeAB * mx1 + my1 - my2) / (perpSlopeAC - perpSlopeAB);
        yCentre = perpSlopeAB * (xCentre - mx1) + my1;
    }

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