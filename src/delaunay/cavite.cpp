#include "cavite.h"


void ajouterAreteACavite(Mesh *mesh, vector<Arete> *cavite, Arete currentEdge)
{
    // Parcourt toutes les arêtes existantes dans la cavité
    for (vector<Arete>::iterator it = cavite->begin(); it != cavite->end(); ++it)
    {
        // Vérifie si les arêtes sont identiques (dans les deux sens)
        if ((it->IDpt1 == currentEdge.IDpt1 && it->IDpt2 == currentEdge.IDpt2) || (it->IDpt1 == currentEdge.IDpt2 && it->IDpt2 == currentEdge.IDpt1)) {
            it = cavite->erase(it); 
            return; 
        }
    }

    // Si l'arête n'est pas trouvée, elle est ajoutée à la cavité
    cavite->push_back(currentEdge);
}



void ajouterTriangleACavite(Mesh *mesh, vector<Arete> *cavite, unsigned int t)
{
    Triangle *triangle;
    triangle = &(mesh->Triangles[t]);

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
    for (int t = 0; t < mesh->Triangles.size(); t++)
    {
        calculerCercleCirconscrit(mesh, t); //ID triangle
        if (mesh->Triangles[t].triangleValide && pointDansCercleCirconscrit(pt, mesh, t))
        {
            ajouterTriangleACavite(mesh, &cavite, t);
        }
    }

    return cavite;
}


void reconnectionCavite(vector<Arete> cavite, Mesh *mesh, Point pt, int IDpt)
{
    //mesh->nbVertices += 1;
    //mesh->Vertices.push_back(pt);
    for(Arete arete : cavite)
    {
        Triangle new_tri;
      
        new_tri.sommetsID = {arete.IDpt1, arete.IDpt2, IDpt};
        new_tri.triangleValide = true;

        mesh->nbTriangles += 1;
        mesh->Triangles.push_back(new_tri);

        calculerCercleCirconscrit(mesh, mesh->nbTriangles-1); //ID triangle
    }
}