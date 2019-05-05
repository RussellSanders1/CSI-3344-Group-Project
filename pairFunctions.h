#ifndef PAIRFUNCTIONS_H_INCLUDED
#define PAIRFUNCTIONS_H_INCLUDED

#include "constants.h"

/*
 * description: Compares Y values of two circle's origin.
 * return: bool
 * precondition: Two circles exist
 * postcondition: Returns true if a's Y value is less than b's Y value.
 * 
 */
bool compareY(const circle &a, const circle &b);

/*
 * description: Finds the closest pair of points using brute force and visualizes the algorithm.
 * return: line
 * precondition: vector is not empty and plotter g exists
 * postcondition: Returns a line connecting the closest pair of points. The algorithm is visualized on the plotter.
 * 
 */
line brutePair(vector<circle> &circles, SDL_Plotter &g, const bool fastMode);

/*
 * description: Finds the closest pair using brute force.
 * return: line
 * precondition: vector has at least two circles
 * postcondition: A line connecting the closest pair is returned.
 * 
 */
line brutePairSimple(vector<circle> &circles);

 /*
 * description: Retuns the shorter line between line a and b.
 * return: line
 * precondition: Two lines exist
 * postcondition: The shorter line is returned.
 * 
 */
line smallestDistance(line a, line b);

/*
 * description: Finds the closest pair within the strip for divide and conquer and visualizes algorithm.
 * return: line
 * precondition: vector is not empty and plotter g exists
 * postcondition: Returns a line connecting the closest pair. The algorithm is visualized on the plotter.
 * 
 */
line stripClosestPair(vector<circle> &strip, SDL_Plotter &g, const bool fastMode);

/*
 * description: Finds the closest pair within the strip.
 * return: line
 * precondition: vector has at least two circles
 * postcondition: The shortest line within the strip is returned.
 * 
 */
line stripClosestPairSimple(vector<circle> &strip);

/*
 * description: Finds the closest pair using divide and conquer and visualizes the algorithm.
 * return: line
 * precondition: vector is not empty and plotter g exists
 * postcondition: Returns a line connecting the closest pair. The algorithm is visualized on the plotter.
 * 
 */
line dividePair(vector<circle> &circles, int begin, int end, SDL_Plotter &g, const bool fastMode);

/*
 * description: Finds the closest pair using divide an conquer.
 * return: line
 * precondition: vector is not empty
 * postcondition: Returns a line connecting the closest pair.
 * 
 */
line dividePairSimple(vector<circle> &circles, int begin, int end);

#endif // PAIRFUNCTIONS_H_INCLUDED
