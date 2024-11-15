#include "include.h"


void computeCircumscribedCircle(Triangle *t)
{
    Point A = t->sommets[0];
    Point B = t->sommets[1];
    Point C = t->sommets[2];

    double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));

    double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                 (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                 (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;

    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                 (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                 (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;

    t->centre_circ.x = Ux;
    t->centre_circ.y = Uy;

    t->rayon_circ = sqrt((Ux - A.x) * (Ux - A.x) + (Uy - A.y) * (Uy - A.y));
}


bool isPointInCircumscribedCircle(Triangle *triangle, Point *point) 
{
    double dx = point->x - triangle->centre_circ.x;
    double dy = point->y - triangle->centre_circ.y;
    double distance = sqrt(dx * dx + dy * dy);

    return distance <= triangle->rayon_circ;
}










int main() 
{
    Triangle t = {{{{0, 0}, {4, 0}, {2, 3}}}, {1, 2, 3}, {}, 0.0, true};
    computeCircumscribedCircle(&t);
    std::cout << "Premier sommet : (" << t.sommets[0].x << ", " << t.sommets[0].y << ")\n";
    std::cout << "Cercle circ : (" << t.centre_circ.x << ", " << t.centre_circ.y << ")\n";
    std::cout << "Rayon circ : (" << t.rayon_circ << ")\n";

    Point p = {1, 2};

    cout << isPointInCircumscribedCircle(&t, &p) << endl;

    return 0;
}