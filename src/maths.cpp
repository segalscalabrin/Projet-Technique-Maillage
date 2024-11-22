#include "maths.h"


void computeCircumscribedCircle(Triangle *t)
{
    Point A = t->sommets[0];
    Point B = t->sommets[1];
    Point C = t->sommets[2];
    //printf("triangle : (%lf, %lf) (%lf, %lf) (%lf, %lf)\n", t->sommets[0].x, t->sommets[0].y, t->sommets[1].x,
    //t->sommets[1].y, t->sommets[2].x, t->sommets[2].y);

    /*double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));

    double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                 (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                 (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;

    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                 (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;

    t->centre_circ.x = Ux;
    t->centre_circ.y = Uy;

    t->rayon_circ = sqrt((Ux - A.x) * (Ux - A.x) + (Uy - A.y) * (Uy - A.y));
}

void cercleCirconscrit(const Point& A, const Point& B, const Point& C, Point& centre, double& rayon) {*/
    // Coordonnées des milieux des côtés
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

    // Équations des médiatrices
    // y = perpSlopeAB * (x - mx1) + my1
    // y = perpSlopeAC * (x - mx2) + my2

    // Résolution des équations pour trouver le centre
    // perpSlopeAB * (x - mx1) + my1 = perpSlopeAC * (x - mx2) + my2
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
    //printf("rayon = %lf, centre = %lf, %lf\n", r, xCentre, yCentre);
}


bool isPointInCircumscribedCircle(Triangle *triangle, Point *point) 
{
    double dx = point->x - triangle->centre_circ.x;
    double dy = point->y - triangle->centre_circ.y;
    double distance = sqrt(dx * dx + dy * dy);

    return distance <= triangle->rayon_circ;
}

<<<<<<< HEAD
Cavite idCavite (vector<Triangle> *triangulation, Point *pt)
{
    Cavite cavite;
    // pour tous les triangles de la triangulation
    for (unsigned int t=0; t<triangulation->size(); t++)
    {
        //Triangle tri = triangulation->at(t);
        // si le triangle est valide/existe
        if(triangulation->at(t).valide)
        {
            //on calcul le cercle et on teste si le point à ajouter est dans le cercle
            calculerCercleCirconscrit(&(triangulation->at(t)));
            
            if(pointDansCercleCirconscrit(&(triangulation->at(t)), pt)) // si le point est dans le cercle circonscrit,
            {
                printf("sommets du triangle a enlever : %d, %d, %d\n", triangulation->at(t).sommetID[0], triangulation->at(t).sommetID[1], triangulation->at(t).sommetID[2]);
                printf("cercle : centre = (%lf, %lf), rayon = %lf\n", triangulation->at(t).centre_circ.x, triangulation->at(t).centre_circ.y, triangulation->at(t).rayon_circ);
                // on retire le triangle
                triangulation->at(t).valide = false;
                // pour tous les sommets du triange
                for (int i=0; i<3; i++)
                {
                    // on ajoute le sommet s'il n'y est pas
                    bool isSommetInCavite(false);
                    // pour tous les sommets dans la cavité
                    for (unsigned int somC=0; somC<cavite.sommets.size(); somC++)
                    {
                        if ((cavite.sommets[somC].x == triangulation->at(t).sommets[i].x) && (cavite.sommets[somC].y == triangulation->at(t).sommets[i].y))
                        {
                            isSommetInCavite = true;
                        }
                    }
                    if (!isSommetInCavite)
                    {
                        //printf("hi\n");
                        cavite.sommets.push_back(triangulation->at(t).sommets[i]);
                        cavite.sommetsID.push_back(triangulation->at(t).sommetID[i]);
                        //printf("hello %lf \n", cavite.sommets[0].x);
                    }
                    
                    
                    bool isArreteInCavite(false);

                    std::cout << isArreteInCavite << " " << true << std::endl;

                    int areteId(-1);
                    Arete currentEdge = {-1, -1, true};
                    //printf("hi i=%d i+1=%d triangulation->at(t).edge= %d\n", i, (i+1)%3, currentEdge.pt1);
                    currentEdge.pt1 = triangulation->at(t).sommetID[i];
                    currentEdge.pt2 = triangulation->at(t).sommetID[(i+1)%3];
                    //printf("hi");
                    currentEdge.areteValide = true;
                    /*for (unsigned int areteC=0; areteC<cavite.sommets.size(); areteC++)
                    {
                        if ((cavite.aretes[areteC].pt1 == currentEdge.pt1)&&(cavite.aretes[areteC].pt1 == currentEdge.pt2))
                        {
                            if (cavite.aretes[areteId].areteValide)
                            {
                                printf("hi");
                                isArreteInCavite = true;
                                areteId = areteC;
                            }
                            
                        }
                    }*/
                    
                    printf("hi\n");
                    std::cout << isArreteInCavite << " " << true << std::endl;
                    // si l'arrete n'est pas dans la cavité, on l'ajoute
                    /*if (!isArreteInCavite)
                    {
                        //printf("hi");
                        //cavite.aretes.push_back(currentEdge);
                    }
                    // on la supprime si elle y est
                    else
                    {
                        //cavite.aretes[areteId].areteValide = false;
                    }*/
                }
            }
        }
    }
    return cavite;
}

/*int main() 
=======









int main() 
>>>>>>> e332ca2a03ef08272f8c3bed4352a76d57ffd2b5
{
    Triangle t = {{{{0, 0}, {4, 0}, {2, 3}}}, {1, 2, 3}, {}, 0.0, true};
    computeCircumscribedCircle(&t);
    std::cout << "Premier sommet : (" << t.sommets[0].x << ", " << t.sommets[0].y << ")\n";
    std::cout << "Cercle circ : (" << t.centre_circ.x << ", " << t.centre_circ.y << ")\n";
    std::cout << "Rayon circ : (" << t.rayon_circ << ")\n";

    Point p = {1, 2};

    cout << isPointInCircumscribedCircle(&t, &p) << endl;



    return 0;
}*/