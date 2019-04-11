/*
 * Author: Russell Sanders
 * Assignment Title: Programming_Assignment_1
 * Assignment Description: This program plots data given in
 * sets on the SDL_Plotter in the form of "curves" consisting
 * of lines determined by point data in the data sets
 * Due Date: 1/28/2019
 * Date Created: 1/27/2019
 * Date Last Modified: 2/5/2019
 */

#ifndef PROJECT1_CURVE_H
#define PROJECT1_CURVE_H

#include "line.h"
#include <vector>
#include "SDL_Plotter.h"

typedef vector<pair<int,long double>> DataSet_t;
typedef vector<DataSet_t> Data_t;

class curve {
public:
    /*
     * description: constructor for curve instantiation
     * return: none
     * precondition: none
     * postcondition: instance of curve created
    */
    curve();
    
    /*
     * description: virtual destructor of curve
     * return: none
     * precondition: curve instance exists
     * postcondition: curve instance doesn't exist
    */
    virtual ~curve() = default;
    
    /*
     * description: displays the points of all curves in data to the ostream
     * referenced
     * return: void
     * precondition: data contains valid information, out is not in a fail-state
     * postcondition: the points in data will be displayed in out, organized into
     * individual sections
    */
    void display(Data_t data, ostream&);
    
    /*
     * description: draws the curves in the Data_t set on the plotter g
     * return: void
     * precondition: data's data is valid
     * postcondition: all curves in data will be plotted on the plotter g
    */
    void draw(Data_t data, SDL_Plotter&);
    
    /*
     * description: returns the value of sameScale
     * return: bool
     * precondition: sameScale is either true/false
     * postcondition: value of sameScale returned to calling code
    */
    bool getSameScale(){ return sameScale;}
    
    /*
     * description: sets sameScale to the value of t
     * return: void
     * precondition: t is true/false
     * postcondition: sameScale has same value as t
    */
    void setSameScale(bool t){sameScale = t;}

private:
    /*
     * description: plots the x and y axes
     * return: void
     * precondition:  maxX and maxY correspond to the dimensions of the plotter g
     * postcondition: the x and y axes will be plotted on the plotter g
    */
    void plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g);
    
    /*
     * description: plots the tick marks of the axes
     * return: void
     * precondition: maxX and maxY correspond to the dimensions of the plotter g
     * postcondition: the ticks will be plotted on the plotter g
    */
    void plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g);
    
    /*
     * description: verifies the points in a line will fit in the graph region
     * return: bool
     * precondition: a contains point data
     * postcondition: a boolean will be returned indicating whether the line is
     * good or not
    */
    bool goodPoints(line a, int margin, SDL_Plotter& g);
    bool sameScale;
    
};
#endif //PROJECT1_CURVE_H
