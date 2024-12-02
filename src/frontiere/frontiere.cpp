#include "frontiere.h"

bool isAreteInMesh(int areteId, Mesh *mesh)
{
    bool found(false);
    for (unsigned int triangle=0; triangle<mesh->Triangles.size(); triangle++)
    {
        for (int edge_int=0; edge_int<3; edge_int++)
        {
            if (
            ((mesh->EdgesMesh[areteId].IDpt1 == mesh->Triangles[triangle].sommetsID[edge_int])
            ||(mesh->EdgesMesh[areteId].IDpt2 == mesh->Triangles[triangle].sommetsID[edge_int]))
            && 
            ((mesh->EdgesMesh[areteId].IDpt1 == mesh->Triangles[triangle].sommetsID[(edge_int+1)%3])
            ||(mesh->EdgesMesh[areteId].IDpt2 == mesh->Triangles[triangle].sommetsID[(edge_int+1)%3])))
            {
                found = true;
            }
        }
    }
    return found;
}