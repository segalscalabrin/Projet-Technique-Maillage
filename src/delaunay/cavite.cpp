#include "cavite.h"


void ajouterAreteACavite(Triangle *triangle, Cavite *cavite, int currentEdgeID)
{
    Arete currentEdge(triangle->aretes[currentEdgeID]);
    // Parcourt toutes les arêtes existantes dans la cavité
    /*for (vector<Arete>::iterator it = (cavite->aretes).begin(); it != (cavite->aretes).end(); ++it)
    {
        // Vérifie si les arêtes sont identiques (dans les deux sens)
        if ((it->IDpt1 == currentEdge.IDpt1 && it->IDpt2 == currentEdge.IDpt2) 
        || (it->IDpt1 == currentEdge.IDpt2 && it->IDpt2 == currentEdge.IDpt1)) 
        {
            it = (cavite->aretes).erase(it);
            return; 
        }
    }*/

   for (size_t i = 0; i < cavite->aretes.size(); ++i) 
   {
        if ((cavite->aretes[i].IDpt1 == currentEdge.IDpt1 && cavite->aretes[i].IDpt2 == currentEdge.IDpt2) ||
            (cavite->aretes[i].IDpt1 == currentEdge.IDpt2 && cavite->aretes[i].IDpt2 == currentEdge.IDpt1)) {
            // Remplacer l'élément courant par le dernier
            cavite->aretes[i] = cavite->aretes.back();
            cavite->aretes.pop_back(); // Réduit la taille du vecteur
            cavite->voisins[i] = cavite->voisins.back();
            cavite->voisins.pop_back(); // Réduit la taille du vecteur
            return; // Quitte la boucle après suppression
        }
    }

    // Si l'arête n'est pas trouvée, elle est ajoutée à la cavité
    (cavite->aretes).push_back(currentEdge);
    //ajouter le voisin à la cavite par cette arete dans voisin 
    (cavite->voisins).push_back(triangle->triVoisins[currentEdgeID]);
    //printf ("id cavite voisin : %d\n",triangle->triVoisins[currentEdgeID]);
}



void ajouterTriangleACavite(Mesh *mesh, Cavite *cavite, unsigned int t)
{
    Triangle *triangle;
    triangle = &(mesh->Triangles[t]);

    triangle->triangleValide = false; // Le triangle est invalidé
    mesh->nbTriangles -= 1;

    for (int i = 0; i < 3; i++)
    {
        //Arete arete_tri = triangle->aretes[i];//{triangle->sommetsID[i], triangle->sommetsID[(i + 1) % 3], true};
        ajouterAreteACavite(triangle, cavite, i);
    }
}


Cavite idCavite(Mesh *mesh, Point *pt)
{
    Cavite cavite;

    // Pour tous les triangles de la triangulation
    for (unsigned int t = 0; t < mesh->Triangles.size(); t++)
    {
        calculerCercleCirconscrit(mesh, t); //ID triangle
        if (mesh->Triangles[t].triangleValide && pointDansCercleCirconscrit(pt, mesh, t))
        {
            ajouterTriangleACavite(mesh, &cavite, t);
        }
    }

    return cavite;
}

void addVoisins(Mesh *mesh, Cavite *cavite, int triID, int triDebut, int triFin)
{
    Triangle triangle = mesh->Triangles[triID];
    // pour tous les triangles ajouter
    for(int tri=triDebut; tri< triFin; tri++)
    {
        if (tri != triID)
        {
            // pour les deux premieres aretes de triID 
            for (int arr2=0; arr2<2; arr2++)
            {
                //on check toutes les arretes des autres triangles
                for (int arr=0; arr<3; arr++)
                {
                    Arete arete = mesh->Triangles[tri].aretes[arr2];
                    if (((triangle.aretes[arr].IDpt1 == arete.IDpt1)
                        || (triangle.aretes[arr].IDpt1 == arete.IDpt2))
                        &&
                        ((triangle.aretes[arr].IDpt2 == arete.IDpt1)
                        || (triangle.aretes[arr].IDpt2 == arete.IDpt2)))
                    {
                        mesh->Triangles[triID].triVoisins[arr] = tri;
                        //printf("triID = % d, tri = %d, arr = %d\n", triID, tri, arr);
                    }
                }
            }
        }
    }
}

void reconnectionCavite(Cavite *cavite, Mesh *mesh, Point pt, int IDpt)
{
    //mesh->nbVertices += 1;
    //mesh->Vertices.push_back(pt);
    int nbTri = mesh->Triangles.size();
    for(unsigned int i=0; i< cavite->aretes.size(); i++)
    {
        Arete arete(cavite->aretes[i]);
        Triangle new_tri;
        Arete arete_1, arete_2;

        arete_1.IDpt1 = arete.IDpt1;
        arete_1.IDpt2 = IDpt;
        arete_1.areteBord = false;
        arete_1.areteValide = true;

        arete_2.IDpt1 = arete.IDpt2;
        arete_2.IDpt2 = IDpt;
        arete_2.areteBord = false;
        arete_2.areteValide = true;
      
        new_tri.sommetsID = {arete.IDpt1, arete.IDpt2, IDpt};
        new_tri.aretes = {arete_1, arete_2, arete};
        new_tri.triangleValide = true;
        // si new tri est voisin de cavite->voisins[i], alors cavite->voisins[i] est voisin de new_tri
        new_tri.triVoisins[2] = cavite->voisins[i];
        if (cavite->voisins[i] != -1)
        {
            int indice_arete=-5;
            for (int ind=0; ind<3; ind++)
            {
                if (((arete.IDpt1 == mesh->Triangles[cavite->voisins[i]].aretes[ind].IDpt1)
                || (arete.IDpt1 == mesh->Triangles[cavite->voisins[i]].aretes[ind].IDpt2))
                && ((arete.IDpt2 == mesh->Triangles[cavite->voisins[i]].aretes[ind].IDpt1)
                || (arete.IDpt2 == mesh->Triangles[cavite->voisins[i]].aretes[ind].IDpt2)))
                {
                    indice_arete = ind;
                }
            }

            if ((mesh->Triangles[cavite->voisins[i]].triangleValide) && (indice_arete>=0))
            {
                //printf("triangle ext cavite : %d, arete = %d, voisin : %ld\n", 
                //cavite->voisins[i], indice_arete, mesh->Triangles.size());
                mesh->Triangles[cavite->voisins[i]].triVoisins[indice_arete] = mesh->Triangles.size();
            }
        }
        
        mesh->nbTriangles += 1;
        mesh->Triangles.push_back(new_tri);

        calculerCercleCirconscrit(mesh, mesh->Triangles.size()-1);
    }
    for(unsigned int i=nbTri; i< mesh->Triangles.size(); i++)
    {
        addVoisins(mesh, cavite, i, nbTri, mesh->Triangles.size());
    }
}