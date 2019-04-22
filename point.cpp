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

#include "point.h"

point::point(){
    this->x = this->y = 0;
}
point::point(int x, int y){
    this->x = x;
    this->y = y;
}
point::point(const point& p): point(){
    *this = p;
}
void point::setY(int y){
    this->y = y;
}
void point::setX(int x){
    this->x = x;
}
void point::setColor(color_rgb c){
    this->color = c;
}
int point::getX() const {
    return this->x;
}
int point::getY() const {
    return this->y;
}
color_rgb point::getColor(){
    return this->color;
}
point& point::operator=(const point& rhs){
    this->x = rhs.x;
    this->y = rhs.y;
    this->color = rhs.color;
    return *this;
}


void point::display(ostream& out){
    out << this->x << ", " << this->y;
}
void point::draw(SDL_Plotter& g){
    g.plotPixel(this->x, this->y, this->color.getR(), this->color.getG(),
                this->color.getB());
}

bool point::operator<(const point &rhs) const {
    bool lessThan = false;

    if (this->getX() < rhs.getX()) {
        lessThan = true;
    }
    else if (this->getX() == rhs.getX()) {
        if (this->getY() < rhs.getY()) {
            lessThan = true;
        }
    }

    return lessThan;
}

bool point::operator==(const point &rhs) const {
    bool isEqual = false;

    if (this->getX() == rhs.getX() && this->getY() == rhs.getY()) {
        isEqual = true;
    }

    return isEqual;
}


