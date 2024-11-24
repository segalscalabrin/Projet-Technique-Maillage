#include "initialisation.h"


void read_mesh(string input_path, Mesh *mesh)
{
    //initialisation des variables 
    int nbVertices(0), nbTriangles(0), nbEdges(0);
    double bin(0);
    
    vector<Point> vertices;
    vector<Arete> edges;
    vector<Triangle> triangles;
    
    // ouverture du fichier .mesh et lecture des données d'entrée
    ifstream file(input_path);
    if (file)
    {
        // lire header
        string ligne;
        getline(file, ligne);
        cout << ligne << endl;
        getline(file, ligne);
        cout << ligne << endl;
        getline(file, ligne);
        cout << ligne << endl;  
        cout << endl;        

        while(getline(file, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            string mot;
            file>>mot;
            if (mot=="Vertices")
            {
                file>>nbVertices;
                cout << "nbVertices : " << nbVertices << endl;
                vertices.resize(nbVertices);
                for (int vertex=0; vertex<nbVertices; vertex++)
                {
                    file>>vertices[vertex].x>>vertices[vertex].y>>bin;
                }
            }
            else if (mot=="Edges")
            {
                file>>nbEdges;
                cout << "nbEdges : " << nbEdges << endl;
                edges.resize(nbEdges);
                for (int edge=0; edge<nbEdges; edge++)
                {
                    file>>edges[edge].IDpt1>>edges[edge].IDpt2>>bin;
                    edges[edge].IDpt1 -= 1;
                    edges[edge].IDpt2 -= 1;
                    edges[edge].areteValide = true;
                }
            }
            else if (mot=="Triangles")
            {
                file>>nbTriangles;
                cout << "nbTriangles : " << nbTriangles << endl;
                triangles.resize(nbTriangles);
                for (int triangle=0; triangle<nbTriangles; triangle++)
                {
                    file>>triangles[triangle].sommetsID[0]>>triangles[triangle].sommetsID[1]>>triangles[triangle].sommetsID[2]>>bin;
                    triangles[triangle].sommetsID[0] -= 1;
                    triangles[triangle].sommetsID[1] -= 1;
                    triangles[triangle].sommetsID[2] -= 1;

                    triangles[triangle].triangleValide = true;
                }
            }
        }
        
        file.close();
    }
    else
    {
        printf("ERREUR : impossible d'ouvrir le fichier !\n");
    }

    mesh->nbVertices = nbVertices;
    mesh->nbEdges = nbEdges;
    mesh->nbTriangles = nbTriangles;
    
    mesh->Vertices = vertices;
    mesh->EdgesMesh = edges;
    mesh->Triangles = triangles;
}