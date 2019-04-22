#ifndef PLOTTERFUNCTIONS_H_INCLUDED
#define PLOTTERFUNCTIONS_H_INCLUDED

#include <vector>
#include "point.h"
#include "line.h"
#include "circle.h"
#include "constants.h"
#include "font.h"
#include "SDL_Plotter.h"

using namespace std;

void clearScreen(SDL_Plotter &g);

void drawCircles(vector<circle> &circles, SDL_Plotter &g);

void drawMenu(SDL_Plotter &g);

void generateRandomPoints(vector<circle> &circles, SDL_Plotter &g);

#endif // PLOTTERFUNCTIONS_H_INCLUDED
