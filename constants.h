#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <fstream>

#include "point.h"
#include "line.h"
#include "circle.h"
#include "font.h"

#include "bruteHullFunctions.h"
#include "plotterFunctions.h"
#include "divideHullFunctions.h"
#include "pairFunctions.h"


const int ROW_MAX = 800;
const int COL_MAX = 800;

const int RADIUS = 3;

const int MIN_POINTS = 10;
const int MAX_POINTS = 20;

const int SLEEP_TIME = 20;

const color_rgb FIRST_SELECTED_POINT_COLOR = color_rgb(255, 0, 0);
const color_rgb TEMP_LINE_COLOR = color_rgb(0, 255, 0);
const color_rgb SECOND_SELECTED_POINT_COLOR = color_rgb(205, 185, 60);
const color_rgb HULL_LINE_COLOR = color_rgb(0, 0, 255);
const color_rgb BLACK = color_rgb(0, 0, 0);
const color_rgb HIDDEN_COLOR = color_rgb(84, 127, 84);

const int BRUTEFORCE_MIN = 5;

const string INPUT_FILE_NAME = "points.txt";


#endif // CONSTANTS_H_INCLUDED
