#include "include.h"

void calculerCercleCirconscrit(Mesh *mesh, int idTriangle);
bool pointDansCercleCirconscrit(Point *point, Mesh *mesh, int idTriangle);
void CalcQuality(vector<double> *quality, Mesh *mesh);