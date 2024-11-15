#include "include.h"

int main()
{
    //initialisation des variables 
    int nbVertices(0), nbTriangles(0), nbEdges(0);
    double bin(0);
    std::vector<double> vertices, edges, triangles;
    
    
    
    // ouverture du fichier .mesh et lecture des données d'entrée
    std::ifstream file("data/input.mesh");
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
        

        while(getline(file, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            std::string mot;
            file>>mot;
            //std::cout << "mot : " << mot << std::endl;
            if (mot=="Vertices")
            {
                file>>nbVertices;
                std::cout << "nbVertices : " << nbVertices << std::endl;
                vertices.resize(nbVertices*2, 0.0);
                for (int vertex=0; vertex<nbVertices; vertex++)
                {
                    file>>vertices[vertex*2]>>vertices[vertex*2+1]>>bin;
                }

                /*for (int i=0; i<vertices.size(); i++)
                {
                    std::cout << vertices[i] << " ";
                }
                std::cout << std::endl;*/
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

                /*for (int i=0; i<edges.size(); i++)
                {
                    std::cout << edges[i] << " ";
                }
                std::cout << std::endl;*/
            }
            else if (mot=="Triangles")
            {
                file>>nbTriangles;
                std::cout << "nbTriangles : " << nbTriangles << std::endl;
                triangles.resize(nbTriangles*3, 0.0);
                printf("triangle %d \n", nbTriangles*3);
                for (int triangle=0; triangle<nbTriangles; triangle++)
                {
                    //printf("ind 1 %d, ind 2 %d, ind 3 %d\n", triangle*3, triangle*3+1, triangle*3+2);
                    file>>triangles[triangle*3]>>triangles[triangle*3+1]>>triangles[triangle*3+2]>>bin;
                }

                /*for (int i=0; i<triangles.size(); i++)
                {
                    std::cout << triangles[i] << " ";
                }
                std::cout << std::endl;*/
            }
        }
        
        file.close();
    }
    else
    {
        printf("ERREUR : impossible d'ouvrir le fichier !\n");
    }


    // création de la boite englobante
    double xmin(vertices[0]), xmax(vertices[0]), ymin(vertices[1]), ymax(vertices[1]), delta_x, delta_y;
    for (int i=0;i<nbVertices;i++)
    {
        if(vertices[2*i]<xmin)
        {
            xmin = vertices[2*i];
        }
        else if (vertices[2*i] > xmax)
        {
            xmax = vertices[2*i];
        }

        if(vertices[2*i+1] < ymin)
        {
            ymin = vertices[2*i+1];
        }
        else if (vertices[2*i+1] > ymax)
        {
            ymax = vertices[2*i+1];
        }
    }

    printf("xmin : %f, xmax : %f, ymin : %f, ymax : %f \n", xmin, xmax, ymin, ymax);
    delta_x = xmax-xmin;
    delta_y = ymax-ymin;

    

    //ecrire le maillage dans un fichier
    std::ofstream file_out;
    file_out.open("output.mesh");
    if (file_out)
    {

    }
    file_out.close();
    return 0;

}