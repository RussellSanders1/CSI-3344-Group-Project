#ifndef DIVIDEHULLFUNCTIONS_H_INCLUDED
#define DIVIDEHULLFUNCTIONS_H_INCLUDED

#include "constants.h"

using namespace std;

// determines the quadrant of a point
// (used in compare())
int getQuadrant(point p);

// Checks whether the line is crossing the polygon
int orientation(point a, point b, point c);

// compare function for sorting
bool compare(point p1, point q1);

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<point> merger(vector<point> a, vector<point> b);

vector<point> bruteHullSimple(vector<circle> &circles);

// Returns the convex hull for the given set of points
vector<point> divideHull(vector<circle> &a);

#endif // DIVIDEHULLFUNCTIONS_H_INCLUDED
