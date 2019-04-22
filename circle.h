#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include <cmath>
#include "point.h"
#include "color_rgb.h"
#include "SDL_Plotter.h"

using namespace std;


class circle{
private:
    double radius;
    point origin;
    color_rgb color;
public:
    circle();
    circle(point,double,color_rgb);

    void setRadius(const double);
    double getRadius();

    void setOrigin(const point);
    point getOrigin() const;

    void setColor(const color_rgb);
    color_rgb getColor();

    void draw(SDL_Plotter& g);
    void eraseCircle(SDL_Plotter& g);

    bool operator<(const circle &rhs) const;
};


#endif // CIRCLE_H_INCLUDED
