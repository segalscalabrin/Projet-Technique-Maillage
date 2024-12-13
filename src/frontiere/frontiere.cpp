#include "frontiere.h"

bool isAreteInMesh(int areteId, Mesh *mesh, queue<int> *aretesManquantes)
{
    bool found(false);
    for (unsigned int triangle=0; triangle<mesh->Triangles.size(); triangle++)
    {
        if (mesh->Triangles[triangle].triangleValide)
        {
            for (int edge_int=0; edge_int<3; edge_int++)
            {
                if (
                ((mesh->EdgesMesh[areteId].IDpt1 == mesh->Triangles[triangle].aretes[edge_int].IDpt1)
                ||(mesh->EdgesMesh[areteId].IDpt2 == mesh->Triangles[triangle].aretes[edge_int].IDpt1))
                && 
                ((mesh->EdgesMesh[areteId].IDpt1 == mesh->Triangles[triangle].aretes[edge_int].IDpt2)
                ||(mesh->EdgesMesh[areteId].IDpt2 == mesh->Triangles[triangle].aretes[edge_int].IDpt2)))
                {
                    found = true;
                    mesh->Triangles[triangle].aretes[edge_int].areteBord = true;
                }
            }
        }
    }
    if (!found)
    {
        aretesManquantes->push(areteId);
    }
    return found;
}

void findTriangles(int areteID, int *tri1, int *tri2, Mesh *mesh)
{
    vector<int> potentielsTri1, potentielsTri2; // tous les triangles qui ont un des deux sommet de l'arete à forcer
    
    for (unsigned int tri=0; tri<mesh->Triangles.size(); tri++)
    {
        if(mesh->Triangles[tri].triangleValide)
        {
            for(int i=0; i<3; i++)
            {
                if((mesh->Triangles[tri].sommetsID[i] == mesh->EdgesMesh[areteID].IDpt1))
                {
                    potentielsTri1.push_back(tri);
                    break;
                }
        
                else if((mesh->Triangles[tri].sommetsID[i] == mesh->EdgesMesh[areteID].IDpt2))
                {
                    potentielsTri2.push_back(tri);
                    break;
                }
            }
            
        }
    }

    for (unsigned int t1=0; t1<potentielsTri1.size(); t1++)
    {
        for (unsigned int t2=0; t2<potentielsTri2.size(); t2++)
        {
            int triangle1 = potentielsTri1[t1];
            int triangle2 = potentielsTri2[t2];
            for (int i=0; i<3; i++)
            {
                if (mesh->Triangles[triangle1].triVoisins[i] == triangle2)
                {
                    (*tri1) = triangle1;
                    (*tri2) = triangle2;
                }
            }
        }
    }

}

void Swap (int areteBord, Mesh *mesh)
{
    int tri1(-1), tri2(-1);
    findTriangles(areteBord, &tri1, &tri2, mesh);
    
    int sommet1ID(-1), sommet2ID(-1);
    for (int i=0; i<3; i++)
    {
        if ((mesh->Triangles[tri1].sommetsID[i] == mesh->EdgesMesh[areteBord].IDpt1)
        || (mesh->Triangles[tri1].sommetsID[i] == mesh->EdgesMesh[areteBord].IDpt2))
        {
            sommet1ID = mesh->Triangles[tri1].sommetsID[(i+1)%3];
            sommet2ID = mesh->Triangles[tri1].sommetsID[(i+2)%3];
        }
        
    }
    //printf("sommet 1 : %d ; sommet 2 : %d\n", sommet1ID, sommet2ID);
    

    Triangle newTri1, newTri2;

    newTri1.sommetsID = {mesh->EdgesMesh[areteBord].IDpt1, mesh->EdgesMesh[areteBord].IDpt2,sommet1ID};
    newTri1.aretes[0] = mesh->EdgesMesh[areteBord];
    newTri1.triVoisins[0] = mesh->Triangles.size()+1;
    newTri1.couleur = -1;
    newTri1.triangleValide = true;


    newTri2.sommetsID = {mesh->EdgesMesh[areteBord].IDpt1, mesh->EdgesMesh[areteBord].IDpt2,sommet2ID};
    newTri2.aretes[0] = mesh->EdgesMesh[areteBord];
    newTri2.triVoisins[0] = mesh->Triangles.size();
    newTri2.couleur = -1;
    newTri2.triangleValide = true;

    // MAJ de "triVoisins" de newTri1 et newTri2
    for (int i=0; i<3; i++)
    {
        if(((mesh->Triangles[tri1].aretes[i].IDpt1 == sommet1ID) || 
        (mesh->Triangles[tri1].aretes[i].IDpt2 == sommet1ID))
        && ((mesh->Triangles[tri1].aretes[i].IDpt1 == mesh->EdgesMesh[areteBord].IDpt1) || 
        (mesh->Triangles[tri1].aretes[i].IDpt2 == mesh->EdgesMesh[areteBord].IDpt1)))
        {
            newTri1.aretes[1] = mesh->Triangles[tri1].aretes[i];
            newTri1.triVoisins[1] = mesh->Triangles[tri1].triVoisins[i];
        }

        if(((mesh->Triangles[tri2].aretes[i].IDpt1 == sommet1ID) || 
        (mesh->Triangles[tri2].aretes[i].IDpt2 == sommet1ID))
        && ((mesh->Triangles[tri2].aretes[i].IDpt1 == mesh->EdgesMesh[areteBord].IDpt2) || 
        (mesh->Triangles[tri2].aretes[i].IDpt2 == mesh->EdgesMesh[areteBord].IDpt2)))
        {
            newTri1.aretes[2] = mesh->Triangles[tri2].aretes[i];
            newTri1.triVoisins[2] = mesh->Triangles[tri2].triVoisins[i];
        }

        if(((mesh->Triangles[tri1].aretes[i].IDpt1 == sommet2ID) || 
        (mesh->Triangles[tri1].aretes[i].IDpt2 == sommet2ID))
        && ((mesh->Triangles[tri1].aretes[i].IDpt1 == mesh->EdgesMesh[areteBord].IDpt1) || 
        (mesh->Triangles[tri1].aretes[i].IDpt2 == mesh->EdgesMesh[areteBord].IDpt1)))
        {
            newTri2.aretes[1] = mesh->Triangles[tri1].aretes[i];
            newTri2.triVoisins[1] = mesh->Triangles[tri1].triVoisins[i];
        }
        
        if(((mesh->Triangles[tri2].aretes[i].IDpt1 == sommet2ID) || 
        (mesh->Triangles[tri2].aretes[i].IDpt2 == sommet2ID))
        && ((mesh->Triangles[tri2].aretes[i].IDpt1 == mesh->EdgesMesh[areteBord].IDpt2) || 
        (mesh->Triangles[tri2].aretes[i].IDpt2 == mesh->EdgesMesh[areteBord].IDpt2)))
        {
            newTri2.aretes[2] = mesh->Triangles[tri2].aretes[i];
            newTri2.triVoisins[2] = mesh->Triangles[tri2].triVoisins[i];
        }
    }

    // MAJ de "triVoisins" des voisins de newTri1 et newTri2
    for (int i=1; i<3; i++)
    {
        int voisin = newTri1.triVoisins[i];
        for (int j=0; j<3; j++)
        {
            if ((mesh->Triangles[voisin].triVoisins[j] == tri1)||(mesh->Triangles[voisin].triVoisins[j] == tri2))
            {
                if(((mesh->Triangles[voisin].aretes[j].IDpt1 == newTri1.aretes[i].IDpt1)||
                (mesh->Triangles[voisin].aretes[j].IDpt1 == newTri1.aretes[i].IDpt2)) && 
                ((mesh->Triangles[voisin].aretes[j].IDpt2 == newTri1.aretes[i].IDpt1)||
                (mesh->Triangles[voisin].aretes[j].IDpt2 == newTri1.aretes[i].IDpt2)))
                {
                    mesh->Triangles[voisin].triVoisins[j] = mesh->Triangles.size(); //newTri1
                }
                else
                {
                    mesh->Triangles[voisin].triVoisins[j] = mesh->Triangles.size()+1; //newTri2
                }
            }
        }
    }
    for (int i=1; i<3; i++)
    {
        int voisin = newTri2.triVoisins[i];
        for (int j=0; j<3; j++)
        {
            if ((mesh->Triangles[voisin].triVoisins[j] == tri1)||(mesh->Triangles[voisin].triVoisins[j] == tri2))
            {
                if(((mesh->Triangles[voisin].aretes[j].IDpt1 == newTri1.aretes[i].IDpt1)||
                (mesh->Triangles[voisin].aretes[j].IDpt1 == newTri1.aretes[i].IDpt2)) && 
                ((mesh->Triangles[voisin].aretes[j].IDpt2 == newTri1.aretes[i].IDpt1)||
                (mesh->Triangles[voisin].aretes[j].IDpt2 == newTri1.aretes[i].IDpt2)))
                {
                    mesh->Triangles[voisin].triVoisins[j] = mesh->Triangles.size(); //newTri1
                }
                else
                {
                    mesh->Triangles[voisin].triVoisins[j] = mesh->Triangles.size()+1; //newTri2
                }
            }
        }
    }


    //supprimer tri1 et tri2
    mesh->Triangles[tri1].triangleValide = false;
    mesh->Triangles[tri2].triangleValide = false;

    //on rajoute les deux triangles créés
    mesh->Triangles.push_back(newTri1);
    mesh->Triangles.push_back(newTri2);
}