#include "include.h"

#include "delaunay/cavite.h"
#include "init_export/initialisation.h"
#include "frontiere/frontiere.h"
#include "init_export/export_mesh.h"
#include "coloriage/coloriage.h"

int main()
{
    // --------------------------------------
    //         Lecture du maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Lecture du maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    Mesh mesh;
    string input_path;
    input_path = "data/first_test/cours.mesh";
    read_mesh(input_path, &mesh);

    for (unsigned int i=0; i<mesh.Triangles.size(); i++)
    {
        Triangle triangle = mesh.Triangles[i];
        //cout << triangle.triangleValide << " " <<  endl;
        if (triangle.triangleValide)
        {
            printf("triangle %d : (%d %d %d) ; voisin : %d, %d, %d ; arete : (%d,%d), (%d,%d), (%d,%d)\n", 
            i, triangle.sommetsID[0], triangle.sommetsID[1], triangle.sommetsID[2], 
            triangle.triVoisins[0], triangle.triVoisins[1], triangle.triVoisins[2], 
            triangle.aretes[0].IDpt1, triangle.aretes[0].IDpt2, 
            triangle.aretes[1].IDpt1, triangle.aretes[1].IDpt2,
            triangle.aretes[2].IDpt1, triangle.aretes[2].IDpt2);
        }
    }

    cout << endl;


    // --------------------------------------
    //   Calcul des données sur le maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Calcul des données sur le maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;


    cout << "Calcul des cercles circonscrits aux triangles" << endl;
    for(int i=0; i<mesh.nbTriangles; i++) {
        calculerCercleCirconscrit(&mesh, i);
    }

    string output_path;
    output_path = "data/output"+to_string(0)+".mesh";
    save_mesh(output_path, &mesh);
    
    //Point pt = {3.65, 5.05};
    for (int point=0; point<mesh.nbVertices-4; point++)
    {
        Point pt = mesh.Vertices[point];
    

        cout << "ajout du point : " << pt.x << ", " << pt.y << endl;

        // --------------------------------------
        //       Modification du maillage
        // --------------------------------------
        //cout << "----------------------------------------------------------------------------" << endl;
        //cout << "Modification du maillage :" << endl;
        //cout << "----------------------------------------------------------------------------" << endl;
        //cout << endl;

        //cout << "Création de la cavite" << endl;
        Cavite cavite;
        cavite = idCavite(&mesh, &pt);

        // print cavité
        /*printf("cavite : \n");
        for (unsigned int i=0; i<cavite.aretes.size(); i++)
        {
            printf("arrete : (%d,%d), voisin de la cavité : %d\n", cavite.aretes[i].IDpt1, cavite.aretes[i].IDpt2, cavite.voisins[i]);
        }*/

        //cout << "Reconnection de la cavite" << endl;
        reconnectionCavite(&cavite, &mesh, pt, point);
        //string output_path;
        output_path = "data/avecSwap/output"+to_string(point+1)+".mesh";
        save_mesh(output_path, &mesh);

        
        //cout << endl;
    }

    // --------------------------------------
    //    Vérification des aretes de bord
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Vérification des aretes de bord :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
    bool bordOK (true);
    queue<int> aretesManquantes;
    for (int edgeb=0; edgeb<mesh.nbEdges; edgeb++)
    {
        // pour les arretes de bord, on regarde si ca correspond
        bool found(false);
        found = isAreteInMesh(edgeb, &mesh, &aretesManquantes);
        if (! found)
        {
            bordOK = false;
        }        
    }

    if (bordOK)
    {
        printf("frontiere OK\n");
    }
    else
    {
        printf("frontiere KO\n");
        // identifier les aretes qui ne vont pas et faire des swaps 

    }

    //cout << "nb triangle: " << mesh.nbTriangles << endl;

    /*for (unsigned int i=0; i<mesh.Triangles.size(); i++)
    {
        Triangle triangle = mesh.Triangles[i];
        //cout << triangle.triangleValide << " " <<  endl;
        if (triangle.triangleValide)
        {
            printf("triangle %d : (%d %d %d) ; voisin : %d, %d, %d ; arete : (%d,%d), (%d,%d), (%d,%d) ; couleur : %d\n", 
            i, triangle.sommetsID[0], triangle.sommetsID[1], triangle.sommetsID[2], 
            triangle.triVoisins[0], triangle.triVoisins[1], triangle.triVoisins[2], 
            triangle.aretes[0].IDpt1, triangle.aretes[0].IDpt2, 
            triangle.aretes[1].IDpt1, triangle.aretes[1].IDpt2,
            triangle.aretes[2].IDpt1, triangle.aretes[2].IDpt2,
            triangle.couleur);
        }
    }*/

    if (bordOK)
    {
        // --------------------------------------
        //    Coloriage du maillage
        // --------------------------------------
        cout << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Coloriage du maillage :" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << endl;
    
        coloriage(&mesh);
        suppBoite(&mesh);
    }

    /*for (unsigned int i=0; i<mesh.Triangles.size(); i++)
    {
        Triangle triangle = mesh.Triangles[i];
        //cout << triangle.triangleValide << " " <<  endl;
        if (triangle.triangleValide)
        {
            printf("triangle %d : (%d %d %d) ; voisin : %d, %d, %d ; arete : (%d,%d), (%d,%d), (%d,%d) ; couleur : %d\n", 
            i, triangle.sommetsID[0], triangle.sommetsID[1], triangle.sommetsID[2], 
            triangle.triVoisins[0], triangle.triVoisins[1], triangle.triVoisins[2], 
            triangle.aretes[0].IDpt1, triangle.aretes[0].IDpt2, 
            triangle.aretes[1].IDpt1, triangle.aretes[1].IDpt2,
            triangle.aretes[2].IDpt1, triangle.aretes[2].IDpt2,
            triangle.couleur);
        }
    }*/


    // --------------------------------------
    //    Sauvegarde du nouveau maillage
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Sauvegarde du nouveau maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    //string output_path;
    output_path = "data/avecSwap/output.mesh";
    save_mesh(output_path, &mesh);

    cout << endl;

    return 0;

}