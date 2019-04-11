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

#ifndef PROJECT1_LINE_H
#define PROJECT1_LINE_H

#include "point.h"
#include <iostream>

class line {
public:
    /*
     * description: constructor
     * return: none
     * precondition: none
     * postcondition: this instance created
    */
    line();
    /*
     * description: custom constructor
     * return: none
     * precondition: p1, p2 valid
     * postcondition: this instance created with values of p1, p2
    */
    line(point p1, point p2);
    /*
     * description: virtual destructor
     * return: none
     * precondition: this instance exists
     * postcondition: this instance doesn't exist
    */
    virtual ~line() = default;
    
    /*
     * description: displays the slope-intercept form of the line to out
     * return: void
     * precondition: out isn't in fail state, this instance valid
     * postcondition: out contains and displays the equation of this instance
    */
    void display(ostream&  out);
    /*
     * description: draws the line between p1, p2 on the plotter g
     * return: void
     * precondition: g is valid, this instance valid
     * postcondition: g has plotted the line this instance represents
    */
    void draw(SDL_Plotter& g);
    
    /*
     * description: sets p1 to value of p
     * return: void
     * precondition: p valid, passed by reference
     * postcondition: p1 contains value of p
    */
    void setP1(point p);
    /*
     * description: sets p2 to value of p
     * return: void
     * precondition: p valid, passed by reference
     * postcondition: p2 contains value of p
    */
    void setP2(point p);
    /*
     * description: sets color to value of c
     * return: void
     * precondition: c valid, passed by reference
     * postcondition: color contains value of c
    */
    void setColor(color_rgb c){color = c;}
    
    /*
     * description: gets value of p1
     * return: point
     * precondition: p1 valid
     * postcondition: returns p1 by value to calling code
    */
    point getP1(){return p1;}
    /*
     * description: gets value of p2
     * return: point
     * precondition: p2 valid
     * postcondition: returns p2 by value to calling code
    */
    point getP2(){return p2;}
    /*
     * description: gets value of color
     * return: color
     * precondition: color valid
     * postcondition: returns color by value to calling code
    */
    color_rgb getColor(){return color;}
    
    /*
     * description: increments currentColor
     * return: void
     * precondition: currentColor valid
     * postcondition: currentColor has increased value by 1
    */
    void nextColor();
    /*
     * description: sets currentColor to original state, 0
     * return: void
     * precondition: this instance exists
     * postcondition: currentColor is reset to 0
    */
    void resetColor();

private:
    point p1, p2;
    color_rgb color;
    bool slope(double& m);
    bool intercept(double& b);
    int currentColor;
    
};

#endif //PROJECT1_LINE_H
