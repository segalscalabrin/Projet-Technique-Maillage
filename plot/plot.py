import matplotlib.pyplot as plt
from matplotlib.tri import Triangulation

# Fonction pour lire le fichier
def read_mesh_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    
    vertices = []
    edges = []
    triangles = []

    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if line == "Vertices":
            i += 1
            n_vertices = int(lines[i].strip())
            for j in range(n_vertices):
                i += 1
                parts = lines[i].strip().split()
                vertices.append((float(parts[0]), float(parts[1])))
        elif line == "Edges":
            i += 1
            n_edges = int(lines[i].strip())
            for j in range(n_edges):
                i += 1
                parts = lines[i].strip().split()
                edges.append((int(parts[0]) - 1, int(parts[1]) - 1))  # Convertir en index 0-based
        elif line == "Triangles":
            i += 1
            n_triangles = int(lines[i].strip())
            for j in range(n_triangles):
                i += 1
                parts = lines[i].strip().split()
                triangles.append((int(parts[0]) - 1, int(parts[1]) - 1, int(parts[2]) - 1))  # 0-based
        i += 1

    return vertices, edges, triangles
def plot_meshes_side_by_side(vertices_in, edges_in, triangles_in, vertices_out, edges_out, triangles_out):
    fig, axes = plt.subplots(1, 2, figsize=(14, 7))  # Deux sous-graphiques côte à côte

    # Tracer l'input mesh
    ax = axes[0]
    if vertices_in:
        x_in, y_in = zip(*vertices_in)
        ax.scatter(x_in, y_in, color='red', label='Vertices')
        
        # Ajouter les indices des sommets
        for idx, (x, y) in enumerate(vertices_in):
            ax.text(x+0.2, y+0.2, str(idx), color='black', fontsize=11, ha='center', va='center')
        
        for edge in edges_in:
            x_coords = [vertices_in[edge[0]][0], vertices_in[edge[1]][0]]
            y_coords = [vertices_in[edge[0]][1], vertices_in[edge[1]][1]]
            ax.plot(x_coords, y_coords, color='blue', linewidth=1, label='Edges' if edge == edges_in[0] else "")
        if triangles_in:
            triangulation_in = Triangulation(x_in, y_in, triangles_in)
            ax.triplot(triangulation_in, color='green', label='Triangles')
    ax.set_title("Input Mesh")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.axis('equal')

    # Tracer l'output mesh
    ax = axes[1]
    if vertices_out:
        x_out, y_out = zip(*vertices_out)
        ax.scatter(x_out, y_out, color='red', label='Vertices')
        
        # Ajouter les indices des sommets
        for idx, (x, y) in enumerate(vertices_out):
            ax.text(x+0.2, y+0.2, str(idx), color='black', fontsize=11, ha='center', va='center')
        
        for edge in edges_out:
            x_coords = [vertices_out[edge[0]][0], vertices_out[edge[1]][0]]
            y_coords = [vertices_out[edge[0]][1], vertices_out[edge[1]][1]]
            ax.plot(x_coords, y_coords, color='blue', linewidth=1, label='Edges' if edge == edges_out[0] else "")
        if triangles_out:
            triangulation_out = Triangulation(x_out, y_out, triangles_out)
            ax.triplot(triangulation_out, color='green', label='Triangles')
    ax.set_title("Output Mesh")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.axis('equal')

    plt.tight_layout()
    plt.show()


# Nom des fichiers
filename_in = "data/test.mesh"
filename_out = "output.mesh"

# Lire les fichiers
vertices_in, edges_in, triangles_in = read_mesh_file(filename_in)
vertices_out, edges_out, triangles_out = read_mesh_file(filename_out)

# Afficher les deux maillages côte à côte
plot_meshes_side_by_side(vertices_in, edges_in, triangles_in, vertices_out, edges_out, triangles_out)
