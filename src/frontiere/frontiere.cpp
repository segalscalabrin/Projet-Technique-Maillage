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

void findTriangles(int *tri1, int *tri2, int *areteTri1, int *areteTri2, Mesh *mesh)
{

}

void Swap (int areteBord, Mesh *mesh)
{
    int tri1, tri2, areteTri1, areteTri2;
    findTriangles(&tri1, &tri2, &areteTri1, &areteTri2, mesh);

}