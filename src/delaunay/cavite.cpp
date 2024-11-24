#include "cavite.h"


void ajouterAreteACavite(Mesh *mesh, vector<Arete> *cavite, Arete currentEdge)
{
    // Parcourt toutes les arêtes existantes dans la cavité
    for (vector<Arete>::iterator it = cavite->begin(); it != cavite->end(); ++it)
    {
        // Vérifie si les arêtes sont identiques (dans les deux sens)
        if ((it->IDpt1 == currentEdge.IDpt1 && it->IDpt2 == currentEdge.IDpt2) ||
            (it->IDpt1 == currentEdge.IDpt2 && it->IDpt2 == currentEdge.IDpt1)) {
            // Invalide l'arête et la supprime de la cavité
            it = cavite->erase(it); // Supprime et récupère le nouvel itérateur
            return; // Arrête la fonction après suppression
        }
    }

    // Si l'arête n'est pas trouvée, elle est ajoutée à la cavité
    cavite->push_back(currentEdge);
}



void ajouterTriangleACavite(Mesh *mesh, vector<Arete> *cavite, unsigned int t)
{
    Triangle *triangle;
    triangle = &(mesh->Triangles[t]);

    printf("Sommets du triangle à enlever : %d, %d, %d\n", 
           triangle->sommetsID[0], 
           triangle->sommetsID[1], 
           triangle->sommetsID[2]);

    printf("Cercle : centre = (%lf, %lf), rayon = %lf\n", 
           triangle->centre_circ.x, 
           triangle->centre_circ.y, 
           triangle->rayon_circ);

    triangle->triangleValide = false; // Le triangle est invalidé
    mesh->nbTriangles -= 1;

    for (int i = 0; i < 3; i++)
    {
        Arete arete_tri = {triangle->sommetsID[i], triangle->sommetsID[(i + 1) % 3], true};
        ajouterAreteACavite(mesh, cavite, arete_tri);
    }
}


vector<Arete> idCavite(Mesh *mesh, Point *pt)
{
    vector<Arete> cavite;

    // Pour tous les triangles de la triangulation
    for (int t = 0; t < mesh->nbTriangles; t++)
    {
        if (mesh->Triangles[t].triangleValide && pointDansCercleCirconscrit(pt, mesh, t))
        {
            ajouterTriangleACavite(mesh, &cavite, t);
        }
    }

    return cavite;
}


/*
void reconnectionCavite(Point p, int ptID, Cavite cav, Mesh *mesh)
{
    for(Arete arete : cav.aretes)
    {
        if (arete.areteValide)
        {
            Triangle new_tri;
            Point p1({-1,-1}), p2({-1,-1});

            for (unsigned int i=0; i<cav.sommetsID.size(); i++)
            {
                if (arete.IDpt1 == cav.sommetsID[i])
                {
                    p1=cav.sommets[i];
                }
                if (arete.IDpt2 == cav.sommetsID[i])
                {
                    p2=cav.sommets[i];
                }
            }
            //sommets = {p1, p2, p};
            

            new_tri.sommets = {p1, p2, p};
            new_tri.sommetsID = {arete.IDpt1, arete.IDpt2, ptID};
            new_tri.triangleValide = true;

            mesh->Tripush_back(new_tri);
        }
        
    }
}*/