#include "cavite.h"



Cavite idCavite (vector<Triangle> *triangulation, Point *pt)
{
    Cavite cavite;
    // pour tous les triangles de la triangulation
    for (unsigned int t=0; t<triangulation->size(); t++)
    {
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
                    // si le sommet n'est pas présent dans la cavite, on le rajoute
                    if (!isSommetInCavite)
                    {
                        //printf("hi\n");
                        cavite.sommets.push_back(triangulation->at(t).sommets[i]);
                        cavite.sommetsID.push_back(triangulation->at(t).sommetID[i]);
                        //printf("hello %lf \n", cavite.sommets[0].x);
                    }
                    
                    
                    bool isArreteInCavite(false);
                    int areteId(-1);
                    Arete currentEdge;
                    currentEdge.pt1 = triangulation->at(t).sommetID[i];
                    currentEdge.pt2 = triangulation->at(t).sommetID[(i+1)%3];
                    currentEdge.areteValide = true;
                    
                    for (unsigned int areteC=0; areteC<cavite.aretes.size(); areteC++)
                    {
                       if (((cavite.aretes[areteC].pt1 == currentEdge.pt1)&&(cavite.aretes[areteC].pt2 == currentEdge.pt2))
                         || ((cavite.aretes[areteC].pt1 == currentEdge.pt2)&&(cavite.aretes[areteC].pt2 == currentEdge.pt1)))
                        {
                            isArreteInCavite = true;
                            areteId = areteC;                            
                        }
                    }
                    
                    // si l'arrete n'est pas dans la cavité, on l'ajoute
                    if (!isArreteInCavite)
                    {
                        cavite.aretes.push_back(currentEdge);
                    }
                    // on la supprime si elle y est
                    else
                    {
                        cavite.aretes[areteId].areteValide = false;
                    }
                }
                printf("\n");
            }
        }
    }
    return cavite;
}


void reconnectionCavite(Point p, int ptID, Cavite cav, vector<Triangle> *triangulation)
{
    for(Arete arete : cav.aretes)
    {
        if (arete.areteValide)
        {
            Triangle new_tri;
            Point p1({-1,-1}), p2({-1,-1});

            for (unsigned int i=0; i<cav.sommetsID.size(); i++)
            {
                if (arete.pt1 == cav.sommetsID[i])
                {
                    p1=cav.sommets[i];
                }
                if (arete.pt2 == cav.sommetsID[i])
                {
                    p2=cav.sommets[i];
                }
            }
            //sommets = {p1, p2, p};
            

            new_tri.sommets = {p1, p2, p};
            new_tri.sommetID = {arete.pt1, arete.pt2, ptID};
            new_tri.valide = true;

            triangulation->push_back(new_tri);
        }
        
    }
}