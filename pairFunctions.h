#ifndef PAIRFUNCTIONS_H_INCLUDED
#define PAIRFUNCTIONS_H_INCLUDED

#include "constants.h"

bool compareY(const circle &a, const circle &b);

line brutePair(vector<circle> &circles, SDL_Plotter &g, const bool fastMode);

line brutePairSimple(vector<circle> &circles);

line smallestDistance(line a, line b);

line stripClosestPair(vector<circle> &strip, SDL_Plotter &g, const bool fastMode);

line stripClosestPairSimple(vector<circle> &strip);

line dividePair(vector<circle> &circles, int begin, int end, SDL_Plotter &g, const bool fastMode);

line dividePairSimple(vector<circle> &circles, int begin, int end);

#endif // PAIRFUNCTIONS_H_INCLUDED
