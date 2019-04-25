#ifndef BRUTEHULLFUNCTIONS_H_INCLUDED
#define BRUTEHULLFUNCTIONS_H_INCLUDED

#include <iostream>
#include <set>
#include <vector>
#include "point.h"
#include "line.h"
#include "circle.h"
#include "SDL_Plotter.h"
#include "plotterFunctions.h"
#include "constants.h"

using namespace std;

int findSide(line l, point p);

vector<circle> bruteHull(vector<circle> &circles, SDL_Plotter &g);


#endif // BRUTEHULLFUNCTIONS_H_INCLUDED