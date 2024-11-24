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
    cout << endl;

    Mesh mesh;
    string input_path;
    input_path = "data/test.mesh";
    read_mesh(input_path, &mesh);

    cout << endl;
    cout << "Fin de la lecture du maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    // --------------------------------------
    //   Calcul des données sur le maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Calcul des données sur le maillage :" << endl;
    cout << endl;

    cout << "Calcul des cercles circonscrits aux triangles" << endl;
    for(int i=0; i<mesh.nbTriangles; i++) {
        calculerCercleCirconscrit(&mesh, i);
    }
    
    Point pt = {6, 4};

    cout << endl;
    cout << "Fin du calcul des données sur le maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    // --------------------------------------
    //       Modification du maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Modification du maillage :" << endl;
    cout << endl;

    cout << "Création de la cavite" << endl;
    vector<Arete> cavite;
    cavite = idCavite(&mesh, &pt);


    cout << endl;
    cout << "Fin du calcul des données sur le maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

   
    // --------------------------------------
    //    Sauvegarde du nouveau maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Sauvegarde du nouveau maillage :" << endl;
    cout << endl;

    string output_path;
    output_path = "output.mesh";
    save_mesh(output_path, &mesh);

    cout << endl;
    cout << "Fin du calcul des données sur le maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    return 0;

}