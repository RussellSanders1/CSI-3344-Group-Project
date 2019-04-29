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


bool line::slope(double &m) const {
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

double line::distance(){
    return sqrt(((p2.getX() - p1.getX()) * (p2.getX() - p1.getX())) +
                ((p2.getY() - p1.getY()) * (p2.getY() - p1.getY())));
}

bool line::intersects(point a) {
    bool intersect = false;
    line that(this->getP1(), a);
    double thisSlope = 0, thatSlope = 0;

    if (this->slope(thisSlope) && that.slope(thatSlope)) {
        if (thisSlope == thatSlope) {
            intersect = true;
        }
        else if (thisSlope == thatSlope * -1) {
            intersect = true;
        }
    }
    else if (!this->slope(thisSlope) && !that.slope(thatSlope)) {
        if (a.getX() == this->getP1().getX()) {
            intersect = true;
        }
    }

    return intersect;
}

int line::findSide(point a) {
    double m, b;
    int side;
    point thisLine;
    thisLine.setX(a.getX());
    if (this->slope(m)) {
        this->intercept(b);
        thisLine.setY(m * thisLine.getX() + b);
        if (thisLine.getY() < a.getY()) {
            side = -1;
        }
        else if (thisLine.getY() > a.getY()) {
            side = 1;
        }
        else {
            side = 0;
        }
    }
    else {
        thisLine.setY(a.getY());
        thisLine.setX(this->p1.getX());

        if (thisLine.getX() > a.getX()) {
            side = 1;
        }
        else if (thisLine.getX() < a.getX()) {
            side = -1;
        }
        else {
            side = 0;
        }
    }

    return side;
}

bool line::operator==(const line &other) {
    bool isEqual = false;
    double thisSlope, otherSlope;
    if (this->getP1() == other.getP1() && this->getP2() == other.getP2()) {
        isEqual = true;
    }
    else if (this->slope(thisSlope) && other.slope(otherSlope)) {
        if (thisSlope == otherSlope && this->intersects(other.getP1())) {
            isEqual = true;
        }
    }
    else if (!this->slope(thisSlope) && !other.slope(otherSlope)) {
        if (this->p1.getX() == other.getP1().getX()) {
            isEqual = true;
        }
    }

    return isEqual;
}




