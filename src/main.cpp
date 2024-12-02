#include "include.h"

#include "delaunay/cavite.h"
#include "init_export/initialisation.h"
#include "frontiere/frontiere.h"
#include "init_export/export_mesh.h"

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
    input_path = "data/input.mesh";
    read_mesh(input_path, &mesh);

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
    for (int point=0; point<mesh.nbVertices; point++)
    {
        Point pt = mesh.Vertices[point];
    

        cout << "ajout du point : " << pt.x << ", " << pt.y << endl;

        // --------------------------------------
        //       Modification du maillage
        // --------------------------------------
        /*cout << "----------------------------------------------------------------------------" << endl;
        cout << "Modification du maillage :" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << endl;*/

        //cout << "Création de la cavite" << endl;
        vector<Arete> cavite;
        cavite = idCavite(&mesh, &pt);

        //cout << "Reconnection de la cavite" << endl;
        reconnectionCavite(cavite, &mesh, pt, point);
        //string output_path;
        output_path = "data/output"+to_string(point+1)+".mesh";
        save_mesh(output_path, &mesh);

        //ajout du point dans la cavite
        //reconnectionCavite(pt, nbVertices+5, cavite, &triangulation);

        //cout << endl;
    }

    // --------------------------------------
    //    vérification des aretes
    // --------------------------------------
    bool bordOK (true);
    for (int edgeb=0; edgeb<mesh.nbEdges; edgeb++)
    {
        // pour les arretes de bord, on regarde si ca correspond
        bool found(false);
        found = isAreteInMesh(edgeb, &mesh);
        if (! found)
        {
            bordOK = false;
        }        
    }

    if (bordOK)
    {
        printf("frontiere OK\n");
    }
    else{
        printf("frontiere KO\n");
        // identifier les aretes qui ne vont pas et faire des swaps 
    }
   
    // --------------------------------------
    //    Sauvegarde du nouveau maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Sauvegarde du nouveau maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    //string output_path;
    output_path = "data/output.mesh";
    save_mesh(output_path, &mesh);

    cout << endl;

    return 0;

}