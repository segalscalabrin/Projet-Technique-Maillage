#include "initialisation.h"


void read_mesh(string input_path, Mesh *mesh)
{
    //initialisation des variables 
    int nbVertices(0), nbTriangles(0), nbEdges(0);
    double bin(0);
    std::vector<double> vertices, edges, triangles;
    
    // ouverture du fichier .mesh et lecture des données d'entrée
    std::ifstream file(input_path);
    if (file)
    {
        // lire header
        std::string ligne;
        getline(file, ligne);
        std::cout << ligne << std::endl;
        getline(file, ligne);
        std::cout << ligne << std::endl;
        getline(file, ligne);
        std::cout << ligne << std::endl;  
        std::cout << std::endl;        

        while(getline(file, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            std::string mot;
            file>>mot;
            if (mot=="Vertices")
            {
                file>>nbVertices;
                std::cout << "nbVertices : " << nbVertices << std::endl;
                vertices.resize(nbVertices*2, 0.0);
                for (int vertex=0; vertex<nbVertices; vertex++)
                {
                    file>>vertices[vertex*2]>>vertices[vertex*2+1]>>bin;
                }
            }
            else if (mot=="Edges")
            {
                file>>nbEdges;
                std::cout << "nbEdges : " << nbEdges << std::endl;
                edges.resize(nbEdges*2, 0.0);
                for (int edge=0; edge<nbEdges; edge++)
                {
                    file>>edges[edge*2]>>edges[edge*2+1]>>bin;
                }
            }
            else if (mot=="Triangles")
            {
                file>>nbTriangles;
                std::cout << "nbTriangles : " << nbTriangles << std::endl;
                triangles.resize(nbTriangles*3, 0.0);
                printf("triangle %d \n", nbTriangles*3);
                for (int triangle=0; triangle<nbTriangles; triangle++)
                {
                    file>>triangles[triangle*3]>>triangles[triangle*3+1]>>triangles[triangle*3+2]>>bin;
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
    mesh->Edges = edges;
    mesh->Triangles = triangles;
}