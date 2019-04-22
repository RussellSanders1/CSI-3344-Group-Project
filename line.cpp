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

#include "line.h"

line::line(): p1(), p2(), color() {}
line::line(point p1, point p2): p1(p1), p2(p2), color() {}
line::line(point p1, point p2, color_rgb c): p1(p1), p2(p2), color(c) {}

void line::setColor(color_rgb c) {
    this->color = c;
    this->p1.setColor(c);
    this->p2.setColor(c);
}


void line::display(ostream&  out){
    double m = 0, b= 0;
    if(slope(m)){
        intercept(b);
        out << "y = " << m << "x + " << b;
    }else{
        out << "x = " << this->p1.getX();
    }
}
void line::draw(SDL_Plotter& g){
    double b = 0, m = 0, delta = 0.001;

    //determine if there is a slope or not so we can use the correct algorithm
    //draw the line
    if (this->slope(m)) {
        this->intercept(b);
        //using the equation for a line, calculate the x and y points in
        //between the two endpoints. Use a delta of 0.001 so the line can be
        //all the way filled in. We can only plot int, so each value will be
        //converted to an int before being plotted, but this way ensures us
        //to get in between points we wouldn't get if we incremented by 1
        //every time
        for (double x = min(this->p1.getX(), this->p2.getX()); x <
             max(this->p1.getX(), this->p2.getX()); x+= delta) {
            g.plotPixel(x,((m * x) + b + 0.5), this->color.getR(), this->color.getG(),
                        this->color.getB());
        }
    }
    //if there is no slope, the line is just a straight vertical line, so
    //don't try and calculate points using the slope in an equation to avoid
    //errors
    else {
        for (double y = min(this->p1.getY(), this->p2.getY()); y <
             max(this->p1.getY(), this->p2.getY()); y+= delta) {
            g.plotPixel(this->p1.getX(), y, this->color.getR(),
                        this->color.getG(), this->color.getB());
        }
    }

    return;
}


bool line::slope(double &m) {
    bool hasSlope = false;

    if(p1.getX() != p2.getX()){
        hasSlope = true;
        m = static_cast<double>(p2.getY() - p1.getY())
                / (p2.getX() - p1.getX());
    }
    return hasSlope;
}

bool line::intercept(double &b) {
    bool hasIntercept = false;
    double m;
    if(slope(m)){
        hasIntercept = true;
        b = p1.getY() - (m * p1.getX());
    }
    return hasIntercept;
}

void line::setP1(point p) {
    this->p1 = p;
}

void line::setP2(point p) {
    this->p2 = p;
}

void line::erase(SDL_Plotter &g) {
    double b = 0, m = 0, delta = 0.001;

    //determine if there is a slope or not so we can use the correct algorithm
    //draw the line
    if (this->slope(m)) {
        this->intercept(b);
        //using the equation for a line, calculate the x and y points in
        //between the two endpoints. Use a delta of 0.001 so the line can be
        //all the way filled in. We can only plot int, so each value will be
        //converted to an int before being plotted, but this way ensures us
        //to get in between points we wouldn't get if we incremented by 1
        //every time
        for (double x = min(this->p1.getX(), this->p2.getX()); x <
             max(this->p1.getX(), this->p2.getX()); x+= delta) {
            g.plotPixel(x,((m * x) + b + 0.5), 255, 255, 255);
        }
    }
    //if there is no slope, the line is just a straight vertical line, so
    //don't try and calculate points using the slope in an equation to avoid
    //errors
    else {
        for (double y = min(this->p1.getY(), this->p2.getY()); y <
             max(this->p1.getY(), this->p2.getY()); y+= delta) {
            g.plotPixel(this->p1.getX(), y, 255, 255, 255);
        }
    }

    return;
}


