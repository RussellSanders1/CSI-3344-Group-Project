#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include "constants.h"

using namespace std;

void clearScreen(SDL_Plotter &g);

void drawCircles(vector<circle> &circles, SDL_Plotter &g);

void drawMenu(SDL_Plotter &g);

void generateRandomPoints(vector<circle> &circles, SDL_Plotter &g);

void printHull(vector<circle> &hull, ostream &out);

void printPair(line a, ostream &out);

bool isStraightLine(vector<circle> &circles);

void eliminateDuplicates(vector<circle> &circles);

void caseBrutePair(SDL_Plotter &g);

void caseBruteHull(SDL_Plotter &g);

void caseDivideHull(SDL_Plotter &g);

void caseRandom(bool &solutionOnScreen, vector<circle> &circles, SDL_Plotter &g);

void caseImport(vector<circle> &circles, SDL_Plotter &g);

void storeMouseClick(int x, int y, vector<circle> &circles, SDL_Plotter &g);

#endif // MISCFUNCTIONS_H_INCLUDED
