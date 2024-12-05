#include "frontiere.h"

bool isAreteInMesh(int areteId, Mesh *mesh)
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
    return found;
}