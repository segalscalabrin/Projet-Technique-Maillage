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
            /*else if (mot=="Triangles")
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
            }*/
        }
        
        file.close();
    }
    else
    {
        printf("ERREUR : impossible d'ouvrir le fichier !\n");
    }

    // initialisation de la boite englobante
    double xmin(vertices[0].x), xmax(vertices[0].x), ymin(vertices[0].y), ymax(vertices[0].y);
    for (int vertex=1; vertex<nbVertices; vertex++)
    {
        if (vertices[vertex].x < xmin)
        {
            xmin = vertices[vertex].x;
        }
        else if (vertices[vertex].x > xmax)
        {
            xmax = vertices[vertex].x;
        }
        if (vertices[vertex].y < ymin)
        {
            ymin = vertices[vertex].y;
        }
        else if (vertices[vertex].y > ymax)
        {
            ymax = vertices[vertex].y;
        }
    }
    double deltax(xmax-xmin), deltay(ymax-ymin);
    vertices.push_back({xmin-deltax,ymin-deltay});
    vertices.push_back({xmin-deltax, ymax+deltay});
    vertices.push_back({xmax+deltax, ymin-deltay});
    vertices.push_back({xmax+deltax, ymax+deltay});

    //triangleBoite = {1+nbVertices, 2+nbVertices, 4+nbVertices, 1+nbVertices, 3+nbVertices, 4+nbVertices};
    nbTriangles = 2;
    triangles.resize(nbTriangles);
    triangles[0].sommetsID[0] = 1+nbVertices-1;
    triangles[0].sommetsID[1] = 2+nbVertices-1;
    triangles[0].sommetsID[2] = 4+nbVertices-1;
    triangles[0].aretes[0].IDpt1 = triangles[0].sommetsID[0];
    triangles[0].aretes[0].IDpt2 = triangles[0].sommetsID[1];
    triangles[0].aretes[1].IDpt1 = triangles[0].sommetsID[1];
    triangles[0].aretes[1].IDpt2 = triangles[0].sommetsID[2];
    triangles[0].aretes[2].IDpt1 = triangles[0].sommetsID[2];
    triangles[0].aretes[2].IDpt2 = triangles[0].sommetsID[0];
    triangles[0].triangleValide = true;
    triangles[0].triVoisins[0] = -1;
    triangles[0].triVoisins[1] = -1;
    triangles[0].triVoisins[2] = 1;
    triangles[0].couleur = -1;

    triangles[1].sommetsID[0] = 1+nbVertices-1;
    triangles[1].sommetsID[1] = 3+nbVertices-1;
    triangles[1].sommetsID[2] = 4+nbVertices-1;
    triangles[1].aretes[0].IDpt1 = triangles[1].sommetsID[0];
    triangles[1].aretes[0].IDpt2 = triangles[1].sommetsID[1];
    triangles[1].aretes[1].IDpt1 = triangles[1].sommetsID[1];
    triangles[1].aretes[1].IDpt2 = triangles[1].sommetsID[2];
    triangles[1].aretes[2].IDpt1 = triangles[1].sommetsID[2];
    triangles[1].aretes[2].IDpt2 = triangles[1].sommetsID[0];
    triangles[1].triangleValide = true;
    triangles[1].triVoisins[0] = -1;
    triangles[1].triVoisins[1] = -1;
    triangles[1].triVoisins[2] = 0;
    triangles[1].couleur = -1;


    mesh->nbVertices = nbVertices+4;
    mesh->nbEdges = nbEdges;
    mesh->nbTriangles = nbTriangles;
    
    mesh->Vertices = vertices;
    mesh->EdgesMesh = edges;
    mesh->Triangles = triangles;
}