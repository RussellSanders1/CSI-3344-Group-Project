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

#ifndef PROJECT1_POINT_H
#define PROJECT1_POINT_H

#include "SDL_Plotter.h"
#include "color_rgb.h"

class point {
public:
    /*
     * description: constructor
     * return: none
     * precondition: none
     * postcondition: this instance exists
    */
    point();
    /*
     * description: custom constructor
     * return: none
     * precondition: x, y valid
     * postcondition: this instance created with values of x, y
    */
    point(int x, int y);
    /*
     * description: copy constructor
     * return: none
     * precondition: p valid
     * postcondition: this instances created with value of p
    */
    point(const point& p);
    /*
     * description: virtual destructor
     * return: none
     * precondition: this instance exists
     * postcondition: this instance doesn't exist
    */
    virtual ~point() = default;

    /*
     * description: sets this->y to value y
     * return: void
     * precondition: y valid
     * postcondition: this->y contains value of y
    */
    void setY(int y);
    /*
     * description: sets this->x to value x
     * return: void
     * precondition: x valid
     * postcondition: this->x contains value of x
    */
    void setX(int x);
    /*
     * description: sets this->color to value c
     * return: void
     * precondition: c valid
     * postcondition: this->color contains value of c
    */
    void setColor(color_rgb c);
    /*
     * description: gets value of x
     * return: int
     * precondition: this instance exists
     * postcondition: returns x by value to calling code
    */
    int getX() const;
    /*
     * description: gets value of y
     * return: int
     * precondition: this instance exists
     * postcondition: returns y by value to calling code
    */
    int getY() const;
    /*
     * description: gets value of color
     * return: int
     * precondition: this instance exists
     * postcondition: returns color by value to calling code
    */
    color_rgb getColor();
    /*
     * description: assignment operator
     * return: point&
     * precondition: this instance exists, rhs valid
     * postcondition: this instance contains the values of rhs
    */
    point& operator=(const point& rhs);
    /*
     * description: displays the values of x, y to ostream out
     * return: void
     * precondition: this instance valid, out isn't in fail state
     * postcondition: out contains and displays the coordinates
    */
    void display(ostream& out);
    /*
     * description: plots the point in the plotter g
     * return: void
     * precondition: g, this instance valid
     * postcondition: g plots a pixel at the coordinates x, y
    */
    void draw(SDL_Plotter& g);

    bool operator<(const point &rhs) const;

    bool operator==(const point &rhs) const;

    int getQuadrant();

private:
    int x, y;
    color_rgb color;
};


#endif //PROJECT1_POINT_H
