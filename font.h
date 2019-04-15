#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "point.h"
#include "SDL_Plotter.h"
#include "color_rgb.h"

#include <sstream>
#include <fstream>

const int MAX_ROW_LETTER = 10;
const int MAX_COLUMN_LETTER = 12;
const int NUM_FONT = 39;

using namespace std;

class font
{
    private:
        char alphabet[NUM_FONT][MAX_ROW_LETTER][MAX_COLUMN_LETTER];

    public:
        //default constructor
        font();
        //turns an int into the corresponding string, in reference to the array of chars
        string getFontString(int a);
        //turns a char into the index of the alphabet array holding that char
        int getFontNum(char c);

        //plots a char
        void plotChar(point &p, int scale, char c, SDL_Plotter &g, color_rgb color);
        //plots a string
        void plotString(point currentPosition, int scale, string message, color_rgb color, SDL_Plotter &g);
        //erases a string
        void eraseString(point currentPosition, int scale, string message, SDL_Plotter &g);
};

#endif // FONT_H_INCLUDED
