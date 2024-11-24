#include "include.h"

#include "delaunay/cavite.h"
#include "init_export/initialisation.h"

int main()
{
    Mesh mesh;
    string input_path;

    input_path = "data/test.mesh";

    read_mesh(input_path, &mesh);


    //initialisation de la triangulation
    std::vector<Triangle> triangulation(mesh.nbTriangles);
    for (int i=0; i<mesh.nbTriangles; i ++)
    {
        for (int j=0; j<3; j++)
        {
            triangulation[i].sommetID[j] = mesh.Triangles[3*i+j];
            triangulation[i].sommets[j].x = mesh.Vertices[(triangulation[i].sommetID[j]-1)*2];
            triangulation[i].sommets[j].y = mesh.Vertices[(triangulation[i].sommetID[j]-1)*2+1];
            triangulation[i].valide = true;
        }       
        std::cout << triangulation[i].sommetID[0]<< " " << triangulation[i].valide  << std::endl;
    }
    
    std::cout<< "1=" <<triangulation[0].sommets[0].x << std::endl;

    /*
    // point à ajouter
    Point pt;
    pt.x = 3.65;
    pt.y = 5.05;

    // calcul de la cavité
    printf("\ncréation de la cavite\n");
    Cavite cavite;
    cavite = idCavite (&triangulation, &pt);

    printf("cavite : \n");
    printf("sommets : \n");
    for (unsigned int i=0; i<cavite.sommets.size(); i++)
    {
        printf (" - ID = %d, x = %lf, y = %lf\n", cavite.sommetsID[i], cavite.sommets[i].x, cavite.sommets[i].y);
    }

    printf("aretes : \n");
    for (unsigned int i=0; i<cavite.aretes.size(); i++)
    {
        if (cavite.aretes[i].areteValide)
        {
            printf (" - pt1 = %d, pt2 = %d\n", cavite.aretes[i].pt1, cavite.aretes[i].pt2);
        }
    }
    */
    //ecrire le maillage dans un fichier
    std::ofstream file_out;
    file_out.open("output.mesh");
    if (file_out)
    {

    }
    file_out.close();
    return 0;

}