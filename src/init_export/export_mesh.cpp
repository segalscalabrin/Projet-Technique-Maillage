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














// Sauvegarde la solution
void Save_quality(const vector<double>* sol, Mesh *mesh)
{
	string name_file = "quality.vtk";
	unsigned int nb_vert = mesh->nbVertices;
    if (sol->size() != mesh->nbTriangles)
    {
        printf("The size of the solution vector is not the same than the number of _triangles !");
    }

	ofstream solution;
	solution.open(name_file, ios::out);
	solution.precision(7);

	solution << "# vtk DataFile Version 3.0 " << endl;
	solution << "2D Unstructured Grid" << endl;
	solution << "ASCII" << endl;
	solution << "DATASET UNSTRUCTURED_GRID" << endl;

	solution << "POINTS " << nb_vert << " float " << endl;
	for (unsigned int i = 0 ; i < nb_vert ; ++i)
	{
		solution << mesh->Vertices[i].x << " "
		<< mesh->Vertices[i].y << " 0." << endl;
	}
	solution << endl;

	solution << "CELLS " << mesh->nbTriangles << " "
	<< mesh->nbTriangles*4 << endl;
	for (unsigned int i = 0 ; i < mesh->Triangles.size() ; ++i)
	{
        if(mesh->Triangles[i].triangleValide)
        {
            solution << 3 << " " << ((mesh->Triangles[i]).sommetsID)[0]
            << " " << ((mesh->Triangles[i]).sommetsID)[1]
            << " " << ((mesh->Triangles[i]).sommetsID)[2] << endl;
        }
	}
	solution << endl;

	solution << "CELL_TYPES " << mesh->nbTriangles << endl;
	for (unsigned int i = 0 ; i < mesh->Triangles.size() ; ++i)
	{
        if(mesh->Triangles[i].triangleValide)
        {
		    solution << 5 << endl;
        }
    }
	solution << endl;

	solution << "CELL_DATA " << mesh->nbTriangles << endl;
	solution << "SCALARS sol float 1" << endl;
	solution << "LOOKUP_TABLE default" << endl;
	// To avoid strange behaviour (which appear only with Apple)
	// with Paraview when we have very small data (e-35 for example)
	double eps = 1.0e-10;
    int k = 0;
	for (unsigned int i = 0 ; i < mesh->Triangles.size() ; ++i)
	{
        if(mesh->Triangles[i].triangleValide)
        {
            solution << max(eps,(*sol)[k]) << endl;
            k += 1;
        }
	}
	solution << endl;

	solution.close();
}

