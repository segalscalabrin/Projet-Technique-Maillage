#include <iostream>
#include <cmath>
using namespace std;

// Structure pour représenter un point
struct Point {
    double x, y;
};

// Fonction pour calculer le centre et le rayon du cercle circonscrit
void cercleCirconscrit(const Point& A, const Point& B, const Point& C, Point& centre, double& rayon) {
    // Coordonnées des milieux des côtés
    double mx1 = (A.x + B.x) / 2.0;
    double my1 = (A.y + B.y) / 2.0;
    double mx2 = (A.x + C.x) / 2.0;
    double my2 = (A.y + C.y) / 2.0;

    // Pentes des côtés
    double slopeAB = (B.y - A.y) / (B.x - A.x);
    double slopeAC = (C.y - A.y) / (C.x - A.x);

    // Pentes des médiatrices (perpendiculaires)
    double perpSlopeAB = -1.0 / slopeAB;
    double perpSlopeAC = -1.0 / slopeAC;

    // Équations des médiatrices
    // y = perpSlopeAB * (x - mx1) + my1
    // y = perpSlopeAC * (x - mx2) + my2

    // Résolution des équations pour trouver le centre
    // perpSlopeAB * (x - mx1) + my1 = perpSlopeAC * (x - mx2) + my2
    double xCentre = (perpSlopeAC * mx2 - perpSlopeAB * mx1 + my1 - my2) / (perpSlopeAC - perpSlopeAB);
    double yCentre = perpSlopeAB * (xCentre - mx1) + my1;

    // Calcul du rayon
    double dx = xCentre - A.x;
    double dy = yCentre - A.y;
    double r = sqrt(dx * dx + dy * dy);

    // Affectation des résultats
    centre.x = xCentre;
    centre.y = yCentre;
    rayon = r;
}

int main() {
    // Points du triangle
    Point A = {5.3, 9.55};
    Point B = {6.06, 5.75};
    Point C = {4.89, 6.63};

    // Variables pour le centre et le rayon
    Point centre;
    double rayon;

    // Calcul du cercle circonscrit
    cercleCirconscrit(A, B, C, centre, rayon);

    // Affichage des résultats
    cout << "Centre du cercle circonscrit: (" << centre.x << ", " << centre.y << ")" << endl;
    cout << "Rayon du cercle circonscrit: " << rayon << endl;

    return 0;
}
