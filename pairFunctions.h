#ifndef PAIRFUNCTIONS_H_INCLUDED
#define PAIRFUNCTIONS_H_INCLUDED

#include "constants.h"

bool compareY(const circle &a, const circle &b);

line brutePair(vector<circle> &circles, SDL_Plotter &g, const bool fastMode);

line smallestDistance(line a, line b);

line stripClosestPair(vector<circle> &strip, SDL_Plotter &g, const bool fastMode);

line dividePair(vector<circle> &circles, int begin, int end, SDL_Plotter &g, const bool fastMode);

#endif // PAIRFUNCTIONS_H_INCLUDED
