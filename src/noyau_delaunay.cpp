#include "include.h"


double areaTriangle(Point A, Point B, Point C) {
    return B.x*C.y - C.x*B.y + A.x*(B.y - C.y) + A.y*(C.x - B.x);
}


bool isPointInTriangle(Triangle *t, Point *P) {
    Point A = t->sommets[0];
    Point B = t->sommets[1];
    Point C = t->sommets[2];

    double lambda1 = areaTriangle(A, B, *P);
    double lambda2 = areaTriangle(B, C, *P);
    double lambda3 = areaTriangle(C, A, *P);

    return (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0);
}


int findTriangle(vector<Triangle>* triangles, Point* point) {
    size_t i = 0; 
    for (Triangle &tri : *triangles) {
        if (isPointInTriangle(&tri, point)) {
            return i; 
        }
        ++i; 
    }
    return -1;
}


int main() {
    // Exemple de triangles
    std::vector<Triangle> triangles = {
        {{{{0, 0}, {4, 0}, {2, 3}}}, {}, {}, {}, true},  // Triangle 0
        {{{{4, 0}, {8, 0}, {6, 3}}}, {}, {}, {}, true}   // Triangle 1
    };

    Point p = {6, 1}; // Point à tester

    int triangleIndex = findTriangle(&triangles, &p);

    if (triangleIndex != -1) {
        std::cout << "Le point est dans le triangle " << triangleIndex << ".\n";
    } else {
        std::cout << "Le point n'est dans aucun triangle.\n";
    }

    return 0;
}