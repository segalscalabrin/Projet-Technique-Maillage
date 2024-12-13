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
    cout << "Lecture du maillage " << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    Mesh mesh;
    string input_path;
    input_path = "data/first_test/cours.mesh";
    read_mesh(input_path, &mesh);

    // --------------------------------------
    //      Ajout de la boite englobante
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Ajout de la boite englobante " << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
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

    // Sauvegarde du maillage de la boite englobante
    string output_path;
    output_path = "data/output"+to_string(0)+".mesh";
    save_mesh(output_path, &mesh);
    
    for (int point=0; point<mesh.nbVertices-4; point++)
    {
        Point pt = mesh.Vertices[point];
    

        cout << "ajout du point : " << pt.x << ", " << pt.y << endl;

        // --------------------------------------
        //       Modification du maillage
        // --------------------------------------


        // Création de la cavite
        Cavite cavite;
        cavite = idCavite(&mesh, &pt);

        //cout << "Reconnection de la cavite" << endl;
        reconnectionCavite(&cavite, &mesh, pt, point);

        // Sauvegarde du maillage à chaque itération
        //string output_path;
        output_path = "data/avecSwap/output"+to_string(point+1)+".mesh";
        save_mesh(output_path, &mesh);

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
        while (! aretesManquantes.empty())
        {
            int current = aretesManquantes.front();
            printf("arete manquate du bord : (%d, %d)\n", mesh.EdgesMesh[current].IDpt1, mesh.EdgesMesh[current].IDpt2);
            aretesManquantes.pop();
            Swap(current, &mesh);

        }

    }

    // Revérification de la frontière
    bordOK = true;
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
        output_path = "data/avecSwap/output_fin.mesh";
        save_mesh(output_path, &mesh);
    }
    else
    {
        printf("frontiere KO\n");
        printf("ERREUR \n");
        return 0;
    }


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