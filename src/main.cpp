#include "include.h"

#include "delaunay/cavite.h"
#include "init_export/initialisation.h"
#include "frontiere/frontiere.h"
#include "init_export/export_mesh.h"
#include "coloriage/coloriage.h"
#include "raffinement/raffinement.h"

int main()
{
    int cas(0);
    cout << "Choix du cas test :" << endl;
    cout << "1. carré simple" << endl;
    cout << "2. carré avec un trou" << endl;
    cout << "3. cas connexe" << endl;
    cout << "4. cas non connexe du cours" << endl;
    cout << "5. carré avec un trou petit" << endl;
    cout << "6. profile naca" << endl;
    cout << "cas : " << endl;
    cin >> cas;

    int cas_raffinement(0);
    cout << "Choix du raffinement :" << endl;
    cout << "1. pas de raffinement" << endl;
    cout << "2. diviser par deux toutes les arêtes" << endl;
    cout << "3. raffinement adaptatif" << endl;
    cout << "cas : " << endl;
    cin >> cas_raffinement;

    string input_dir_path, output_dir_path;
    input_dir_path = "data/input_meshes/";
    string input_path;
    output_dir_path = "data/output/";

    switch (cas)
    {
    case (1) : 
        input_path = input_dir_path+"carre.mesh";
        output_dir_path += "carre/";
        break;
    case (2) : 
        input_path = input_dir_path+"carre_cercle2.mesh";
        output_dir_path += "carre_cercle/";
        break;
    case (3) : 
        input_path = input_dir_path+"connexe.mesh";
        output_dir_path += "connexe/";
        break;
    case (4) : 
        input_path = input_dir_path+"cours.mesh";
        output_dir_path += "cours/";
        break;
    case (5) : 
        input_path = input_dir_path+"carre_cercle_bis.mesh";
        output_dir_path += "carre_cercle_bis/";
        break;
    case (6) : 
        input_path = input_dir_path+"naca.mesh";
        output_dir_path += "naca/";
        break;
    default:
        break;
    }

    // --------------------------------------
    //         Lecture du maillage
    // --------------------------------------
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Lecture du maillage " << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    Mesh mesh;
    read_mesh(input_path, &mesh);

    for (unsigned int i=0; i<mesh.Triangles.size(); i++)
    {
        Triangle triangle = mesh.Triangles[i];
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
    output_path = output_dir_path + "output_boite.mesh";
    save_mesh(output_path, &mesh);
    
    for (int point=0; point<mesh.nbVertices-4; point++)
    {
        Point pt = mesh.Vertices[point];
    

        //cout << "ajout du point " << point << " : " << pt.x << ", " << pt.y << endl;

        // --------------------------------------
        //       Modification du maillage
        // --------------------------------------


        // Création de la cavite
        Cavite cavite;
        cavite = idCavite(&mesh, &pt);

        //cout << "Reconnection de la cavite" << endl;
        reconnectionCavite(&cavite, &mesh, pt, point, false);

        // Sauvegarde du maillage à chaque itération
        //string output_path;
        //output_path = output_dir_path + "output"+to_string(point+1)+".mesh";
        //save_mesh(output_path, &mesh);

    }
    output_path = output_dir_path + "output_bord.mesh";
    save_mesh(output_path, &mesh);
    // --------------------------------------
    //    Vérification des aretes de bord
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Vérification des aretes de bord" << endl;
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
        cout << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Swap des aretes de bord" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << endl;
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
        output_path = output_dir_path + "output_fin.mesh";
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
        cout << "Coloriage du maillage" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        cout << endl;
    
        coloriage(&mesh);
        // Suppression de la boite englobante
        suppBoite(&mesh);
    }

    
    // --------------------------------------
    //    Sauvegarde du nouveau maillage
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Sauvegarde du nouveau maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
    //string output_path;
    output_path = output_dir_path + "output_colorie.mesh";
    save_mesh(output_path, &mesh);


    // --------------------------------------
    //    Raffinement du maillage
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Raffinement du maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;
    std::vector<Point> pt_raffine (0);
    new_points (&mesh, &pt_raffine, cas_raffinement );
    printf ("new point size : %ld\n", pt_raffine.size());
    int nb_point = mesh.nbVertices;
    for (unsigned int point=nb_point; point<nb_point+pt_raffine.size(); point++)
    {
        Point pt = pt_raffine[point-nb_point];

        //cout << "ajout du point " << point << " : " << pt.x << ", " << pt.y << endl;

        mesh.Vertices.push_back(pt);
        mesh.nbVertices += 1;
        
        // Création de la cavite
        Cavite cavite;
        cavite = idCavite(&mesh, &pt);

        reconnectionCavite(&cavite, &mesh, pt, point, true);
    }
    raffinement_bord(&mesh, &pt_raffine, nb_point);
    
    output_path = output_dir_path + "output_raffine.mesh";
    save_mesh(output_path, &mesh);

    cout << endl;

    // --------------------------------------
    //    Qualité du maillage
    // --------------------------------------
    cout << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "Qualité du maillage" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << endl;

    vector<double> quality(mesh.nbTriangles);
    CalcQuality(&quality, &mesh);
    // sauvegarde de la qualité au format .vtk
    Save_quality(&quality, &mesh);

    vector<int> hist(7), bord_hist(7);
    bord_hist[0] = 1;
    bord_hist[1] = 2;
    bord_hist[2] = 3;
    bord_hist[3] = 5;
    bord_hist[4] = 10;
    bord_hist[5] = 50;
    bord_hist[6] = 100;

    for (int i=0; i<mesh.nbTriangles ; i++)
    {
        for (int j=0; j<6; j++)
        {
            if((quality[i]>bord_hist[j]) && (quality[i]<bord_hist[j+1]))
            {
                hist[j] += 1;
            }
        }
        if(quality[i]>bord_hist[6])
        {
            hist[6] += 1;
        }
    }
    printf("nb d'élément : %d\n", mesh.nbTriangles);
    printf("nb d'élément ayant une qualité entre 1 et 2    : %d\n", hist[0]);
    printf("nb d'élément ayant une qualité entre 2 et 3    : %d\n", hist[1]);
    printf("nb d'élément ayant une qualité entre 3 et 5    : %d\n", hist[2]);
    printf("nb d'élément ayant une qualité entre 5 et 10   : %d\n", hist[3]);
    printf("nb d'élément ayant une qualité entre 10 et 50  : %d\n", hist[4]);
    printf("nb d'élément ayant une qualité entre 50 et 100 : %d\n", hist[5]);
    printf("nb d'élément ayant une qualité supérieur à 100 : %d\n", hist[6]);

    return 0;

}