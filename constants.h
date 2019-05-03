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

#include "hullFunctions.h"
#include "miscFunctions.h"
#include "pairFunctions.h"


const int ROW_MAX = 800;
const int COL_MAX = 800;

const int RADIUS = 3;

const int MIN_POINTS = 10;
const int MAX_POINTS = 20;

const int BRUTE_SLEEP_TIME = 100;
const int DIVIDE_SLEEP_TIME = 500;

const color_rgb FIRST_SELECTED_POINT_COLOR = color_rgb(255, 0, 0);
const color_rgb TEMP_LINE_COLOR = color_rgb(0, 255, 0);
const color_rgb SECOND_SELECTED_POINT_COLOR = color_rgb(205, 185, 60);
const color_rgb SELECTED_LINE_COLOR = color_rgb(0, 0, 255);
const color_rgb BLACK = color_rgb(0, 0, 0);
const color_rgb HIDDEN_COLOR = color_rgb(84, 127, 84);
const color_rgb STRIP_COLOR = color_rgb(66, 238, 244);

const int BRUTEFORCE_MIN = 5;

const string INPUT_FILE_NAME = "points.txt";

const char PAIR_OPTION = '1';
const char HULL_OPTION = '2';
const char DIVIDE_OPTION = 'D';
const char BRUTE_OPTION = 'B';
const char RANDOM_OPTION = 'R';
const char ERASE_OPTION = 'E';
const char IMPORT_OPTION = 'I';
const char BACK_OPTION = LEFT_ARROW;
const char CONTROLS_OPTION = 'C';
const char FAST_OPTION = 'F';
const char SLOW_OPTION = 'S';
const char ANIMATION_OPTION = 'A';


#endif // CONSTANTS_H_INCLUDED
