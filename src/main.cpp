#include "include.h"

#include "delaunay/cavite.h"
#include "init_export/initialisation.h"
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
    
    Point pt = {3.65, 5.05};

    cout << endl;

    // --------------------------------------
    //       Modification du maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Modification du maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << "Création de la cavite" << endl;
    vector<Arete> cavite;
    cavite = idCavite(&mesh, &pt);

    cout << "Reconnection de la cavite" << endl;
    reconnectionCavite(cavite, &mesh, pt);


    cout << endl;

   
    // --------------------------------------
    //    Sauvegarde du nouveau maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Sauvegarde du nouveau maillage :" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    string output_path;
    output_path = "data/output.mesh";
    save_mesh(output_path, &mesh);

    cout << endl;

    return 0;

}