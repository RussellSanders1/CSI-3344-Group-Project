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

line::line(): p1(), p2(), color(), currentColor(0) {}
line::line(point p1, point p2): p1(p1), p2(p2), color(), currentColor(0){}
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
    double m = 0;
    switch(currentColor){
        case 0:
            this->color = color_rgb(255,0,0);
            break;
        case 1:
            this->color = color_rgb(0,255,0);
            break;
        case 2:
            this->color = color_rgb(0,0,255);
            break;
        case 3:
            this->color = color_rgb(144,12,63);
            break;
        case 4:
            this->color = color_rgb(105,213,207);
            break;
        case 5:
            this->color = color_rgb(160,0,164);
            break;
    }
    double b;
    if(slope(m)){
        intercept(b);
        double delta = 0.1;
        if(p2.getX() < p1.getX()){
            delta = -delta;
        }
        double y;
        for(double x = p1.getX(); (int)x != p2.getX(); x += delta){
            y = m*x + b;
            g.plotPixel(x,y,color.getR(), color.getG(), color.getB());
        }
    }else{
        int x = this->p1.getX();
        int minY = min(this->p1.getY(), this->p2.getY());
        int maxY = max(this->p1.getY(), this->p2.getY());
        
        for(int y = minY; y < maxY; y++){
            g.plotPixel(x,y,this->color.getR(), this->color.getG(),
                        this->color.getB());
        }
    }
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

void line::nextColor() {
    this->currentColor = (this->currentColor + 1) % 6;
}

void line::resetColor() {
    this->currentColor = 0;
}
