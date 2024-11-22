#include "cavite.h"


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

                    //std::cout << isArreteInCavite << " " << true << std::endl;

                    int areteId(-1);
                    Arete currentEdge = {-1, -1, true};
                    //printf("hi i=%d i+1=%d triangulation->at(t).edge= %d\n", i, (i+1)%3, currentEdge.pt1);
                    currentEdge.pt1 = triangulation->at(t).sommetID[i];
                    currentEdge.pt2 = triangulation->at(t).sommetID[(i+1)%3];
                    currentEdge.areteValide = true;
                    std::cout << "arete valide : " << " " << currentEdge.areteValide << std::endl;
                    printf("hi\n");
                    for (unsigned int areteC=0; areteC<cavite.aretes.size(); areteC++)
                    {
                        printf("arete cavite : [%d, %d] arete actuelle : [%d,%d] presente : %B\n", cavite.aretes[areteC].pt1, 
                        cavite.aretes[areteC].pt2, currentEdge.pt1, currentEdge.pt2, ((cavite.aretes[areteC].pt1 == currentEdge.pt1)&&(cavite.aretes[areteC].pt2 == currentEdge.pt2))
                         || ((cavite.aretes[areteC].pt1 == currentEdge.pt2)&&(cavite.aretes[areteC].pt2 == currentEdge.pt1)));
                        if (((cavite.aretes[areteC].pt1 == currentEdge.pt1)&&(cavite.aretes[areteC].pt2 == currentEdge.pt2))
                         || ((cavite.aretes[areteC].pt1 == currentEdge.pt2)&&(cavite.aretes[areteC].pt2 == currentEdge.pt1)))
                        {
                            std::cout << "arete valide : " << " " << cavite.aretes[areteId].areteValide << std::endl;
                            if (cavite.aretes[areteId].areteValide)
                            {
                                printf("hi");
                                isArreteInCavite = true;
                                areteId = areteC;
                            }
                            
                        }
                    }
                    
                    //printf("hi\n");
                    std::cout << isArreteInCavite << " " << true << std::endl;
                    // si l'arrete n'est pas dans la cavité, on l'ajoute
                    if (!isArreteInCavite)
                    {
                        //printf("hi");
                        cavite.aretes.push_back(currentEdge);
                    }
                    // on la supprime si elle y est
                    else
                    {
                        //cavite.aretes[areteId].areteValide = false;
                    }
                }
            }
        }
    }
    return cavite;
}


void reconnectionCavite(Point p, Cavite cav, vector<Triangle> *triangulation)
{
    for(Arete arete : cav.aretes) {
        Triangle new_tri;
        Point p1, p2;
        int p1iD, p2iD; 
        array<Point, 3> sommets;
        array<int,3> sommetsID;

        p1 = cav.sommets[arete.pt1];
        p2 = cav.sommets[arete.pt2];

        p1iD = cav.sommetsID[arete.pt1];
        p2iD = cav.sommetsID[arete.pt2];

        sommets = {p1, p2, p};

        sommetsID = {p1iD, p2iD, static_cast<int>(triangulation->size())};

        new_tri.sommets = sommets;
        new_tri.sommetID = sommetsID;

        triangulation->push_back(new_tri);
    }
}