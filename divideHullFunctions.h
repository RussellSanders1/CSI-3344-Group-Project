#ifndef DIVIDEHULLFUNCTIONS_H_INCLUDED
#define DIVIDEHULLFUNCTIONS_H_INCLUDED

#include "constants.h"

using namespace std;

// determines the quadrant of a point
// (used in compare())
int getQuadrant(point p);

// Checks whether the line is crossing the polygon
int orientation(line l, point p);

// compare function for sorting
bool compare(point p1, point q1);

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<circle> merger(vector<circle> &a, vector<circle> &b);

vector<point> bruteHullSimple(vector<circle> &circles);

// Returns the convex hull for the given set of points
vector<circle> divideHull(vector<circle> &a, SDL_Plotter &g);

#endif // DIVIDEHULLFUNCTIONS_H_INCLUDED
