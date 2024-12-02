#include "export_mesh.h"


void save_mesh(string output_path, Mesh *mesh)
{
    // Ouverture du fichier en mode écriture
    ofstream file(output_path);
    if (!file)
    {
        printf("ERREUR : impossible de créer le fichier pour sauvegarder le maillage !\n");
        return;
    }

    // Écriture de l'en-tête
    file << "MeshVersionFormatted 2\n\n";
    printf("MeshVersionFormatted 2\n\n");
    file << "Dimension 2\n\n";
    printf("Dimension 2\n\n");

    // Sauvegarde des sommets (Vertices)
    file << "Vertices\n";
    file << mesh->nbVertices << "\n";
    printf("nbVertices : %d\n", mesh->nbVertices);
    for (const Point &vertex : mesh->Vertices)
    {
        file << vertex.x << " " << vertex.y << " 0\n"; // Coordonnées x, y, et 0 pour le format
    }
    file << "\n";

    // Sauvegarde des arêtes (Edges)
    file << "Edges\n";
    file << mesh->nbEdges << "\n";
    printf("nbEdges : %d\n", mesh->nbEdges);
    for (const Arete &edge : mesh->EdgesMesh)
    {
        // Écriture avec +1 pour repasser à l'indexation en base 1
        file << edge.IDpt1 + 1 << " " << edge.IDpt2 + 1 << " 1\n"; // 1 pour le marqueur
    }
    file << "\n";

    // Sauvegarde des triangles (Triangles)
    file << "Triangles\n";
    file << mesh->nbTriangles << "\n";
    printf("nbTriangles : %d\n\n", mesh->nbTriangles);
    for (const Triangle &triangle : mesh->Triangles)
    {
        if (triangle.triangleValide)
        {
            // Écriture des indices des sommets (indexation en base 1) et 0 pour le format
            file << triangle.sommetsID[0] + 1 << " " 
                 << triangle.sommetsID[1] + 1 << " " 
                 << triangle.sommetsID[2] + 1 << " 0\n";
        }
    }
    file << "\n";

    // Fin du fichier
    file << "End\n";

    // Fermeture du fichier
    file.close();

    cout << "Mesh sauvegardé avec succès dans le fichier : " << output_path << endl;
}
