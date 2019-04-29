#ifndef HULLFUNCTIONS_H_INCLUDED
#define HULLFUNCTIONS_H_INCLUDED

#include "constants.h"

using namespace std;

vector<circle> bruteHull(vector<circle> &circles, SDL_Plotter &g, const bool fastMode);

// Checks whether the line is crossing the polygon
int orientation(line l, point p);

// compare function for sorting
bool compare(point p1, point q1);

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<circle> merger(vector<circle> &a, vector<circle> &b, const bool fastMode);

// Returns the convex hull for the given set of points
vector<circle> divideHull(vector<circle> &a, SDL_Plotter &g, const bool fastMode);




#endif // HULLFUNCTIONS_H_INCLUDED
