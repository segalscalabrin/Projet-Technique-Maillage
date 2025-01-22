#include "raffinement.h"

bool inPoint(Point pt, std::vector<Point> *pt_raffine, int *ID)
{
    bool found(false);
    for (unsigned int i=0; i<pt_raffine->size(); i++)
    {
        Point point = (*pt_raffine)[i];
        if ((pt.x == point.x) && (pt.y == point.y))
        {
            found = true;
            *ID = i;
        }
    }
    return found;
}

void new_points (Mesh *mesh, std::vector<Point> *pt_raffine, int cas)
{
    int j;
    Point min, max;
    switch (cas)
    {
    case (1):
        break;
    case (2):
    {
        min = mesh->Vertices[mesh->nbVertices-4];
        max = mesh->Vertices[mesh->nbVertices-1];
        for (const Triangle &triangle : mesh->Triangles)
        {
            if (triangle.triangleValide)
            {
                Point pt;
                for (int i=0; i<3; i++)
                {
                    pt.x = (mesh->Vertices[triangle.aretes[i].IDpt1].x + 
                        mesh->Vertices[triangle.aretes[i].IDpt2].x)/2.0;
                    pt.y = (mesh->Vertices[triangle.aretes[i].IDpt1].y + 
                        mesh->Vertices[triangle.aretes[i].IDpt2].y)/2.0;
                    if ((!inPoint(pt, pt_raffine, &j))&&(pt.x!=min.x)&& (pt.x!=max.x) 
                    && (pt.y!=min.y) && (pt.y!=max.y))
                    {
                        pt_raffine->push_back(pt);
                    }
                    
                }
            }
        }
        break;
    }
    case (3):
    {
        double h1(0.5), h2(0.06);
        min = mesh->Vertices[mesh->nbVertices-4];
        max = mesh->Vertices[mesh->nbVertices-1];
        for (const Triangle &triangle : mesh->Triangles)
        {
            if (triangle.triangleValide)
            {
                Point pt;
                // pour chaque arête
                for (int i=0; i<3; i++)
                {
                    Point pt2, pt1;
                    if (!(triangle.aretes[i].areteBord))
                    {
                        pt1.x = mesh->Vertices[triangle.aretes[i].IDpt1].x;
                        pt1.y = mesh->Vertices[triangle.aretes[i].IDpt1].y;
                        pt2.x = mesh->Vertices[triangle.aretes[i].IDpt2].x;
                        pt2.y = mesh->Vertices[triangle.aretes[i].IDpt2].y;

                        double d = sqrt(pow(pt2.x-pt1.x, 2)+pow(pt2.y-pt1.y, 2));
                        int n = int(2*d/(h2+h1))-1;
                        double r = (h1-h2)/(n+2);
                        double alpha(h2);
                        pt.x = pt2.x;
                        pt.y = pt2.y;
                        for(int i=1; i<n; i++)
                        {
                            alpha += i*r;
                            pt.x += alpha*(pt1.x-pt2.x)/d;
                            pt.y += alpha*(pt1.y-pt2.y)/d;
                            if ((!inPoint(pt, pt_raffine, &j))&&(pt.x!=min.x)&& (pt.x!=max.x) 
                            && (pt.y!=min.y) && (pt.y!=max.y))
                            {
                                pt_raffine->push_back(pt);
                            }
                        }
                        alpha = h1 - r;
                        pt.x = pt2.x + alpha*(pt1.x-pt2.x)/d;
                        pt.y = pt2.y + alpha*(pt1.y-pt2.y)/d;
                        if ((!inPoint(pt, pt_raffine, &j))&&(pt.x!=min.x)&& (pt.x!=max.x) 
                        && (pt.y!=min.y) && (pt.y!=max.y))
                        {
                            pt_raffine->push_back(pt);
                        }
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    }

    
}

void raffinement_bord(Mesh *mesh, std::vector<Point> *pt_raffine, int nb_point)
{
    int ID;
    for (unsigned int i=0; i< mesh->EdgesMesh.size(); i++)
    {
        Point pt;
        pt.x = (mesh->Vertices[mesh->EdgesMesh[i].IDpt1].x + 
        mesh->Vertices[mesh->EdgesMesh[i].IDpt2].x)/2.0;
        pt.y = (mesh->Vertices[mesh->EdgesMesh[i].IDpt1].y + 
            mesh->Vertices[mesh->EdgesMesh[i].IDpt2].y)/2.0;

        if (inPoint(pt, pt_raffine, &ID))
        {
            Arete new_edge;
            new_edge.IDpt1 = nb_point + ID;
            new_edge.IDpt2 = mesh->EdgesMesh[i].IDpt2;
            new_edge.areteValide = true;
            mesh->EdgesMesh[i].IDpt2 = nb_point + ID;
            mesh->EdgesMesh.push_back(new_edge);
            mesh->nbEdges += 1;
        }
    }
}