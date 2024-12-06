#include "coloriage.h"

void coloriage (Mesh *mesh)
{
    queue<int> triColorie; 

    int tri_bord = triangleBord(mesh);
    printf ("\n triangle bord : %d\n", tri_bord);
    mesh->Triangles[tri_bord].triInt=false;
    mesh->Triangles[tri_bord].couleur = 0;

    triColorie.push(tri_bord);

    while(!(triColorie.empty()))
    //for (int k=0; k<50; k++)
    {
        int CurrentTriangle;
        CurrentTriangle = triColorie.front();
        triColorie.pop();

        for(int i=0; i<3; i++)
        {
            int voisin = mesh->Triangles[CurrentTriangle].triVoisins[i];
            //printf("colorie : %B, true : %B\n", mesh->Triangles[voisin].colorie, true);
            if (voisin!=-1 && (mesh->Triangles[voisin].couleur==-1))
            {
                // colorie le triangle voisin
                if (mesh->Triangles[CurrentTriangle].aretes[i].areteBord)
                {
                    if (mesh->Triangles[CurrentTriangle].couleur == 0)
                    {
                        mesh->Triangles[voisin].couleur = 1;
                    }
                    else
                    {
                        mesh->Triangles[voisin].couleur = 0;
                    }
                }
                else
                {
                    mesh->Triangles[voisin].couleur = mesh->Triangles[CurrentTriangle].couleur;
                }

                // on l'ajoute à la pile
                triColorie.push(voisin);
            }
        }
        printf ("taille de la file : %ld\n", triColorie.size());
    }



}

int triangleBord (Mesh *mesh)
{
    int tri_bord = -1;
    for (unsigned int tri=0; tri<mesh->Triangles.size(); tri++)
    {
        for(int i=0; i<3; i++)
        {
            if (mesh->Triangles[tri].triangleValide)
            {
                if (mesh->Triangles[tri].triVoisins[i] == -1)
                {
                    tri_bord = tri;
                    return tri_bord;
                }
            }
        }
    }
    return -1;
}

void suppBoite(Mesh *mesh)
{
    for (unsigned int tri=0; tri<mesh->Triangles.size(); tri++)
    {
        if ((mesh->Triangles[tri].triangleValide) && (mesh->Triangles[tri].couleur==0))
        {
            mesh->Triangles[tri].triangleValide = false;
        }
    }
}