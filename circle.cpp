#include "circle.h"

circle::circle() {
    origin = point(1, 1);
    radius = 10;
    color = color_rgb(255, 255, 255);
}

circle::circle(point a, double x, color_rgb col) {
    origin = a;
    radius = x;
    color = col;
}

void circle::setRadius(const double x) {
    radius = x;
}

double circle::getRadius() {
    return radius;
}

void circle::setOrigin(const point a) {
    origin = a;
}

point circle::getOrigin() const {
    return origin;
}

void circle::setColor(const color_rgb col) {
    color = col;
}

color_rgb circle::getColor() {
    return color;
}

void circle::draw(SDL_Plotter& g) {
    for (double x = -radius; x <= radius; x+=0.1) {
        for (int y = -radius; y <= radius; y++) {
            if (sqrt(y*y + x*x) <= radius) {
                g.plotPixel(origin.getX() + x, origin.getY() + y,
                            color.getR(), color.getG(),
                            color.getB());
            }
        }
    }

    return;
}

void circle::eraseCircle(SDL_Plotter& g) {
    for (double x = -radius; x <= radius; x+=0.1) {
        for (int y = -radius; y <= radius; y++) {
            if (sqrt(y*y + x*x) <= radius) {
                g.plotPixel(origin.getX() + x, origin.getY() + y, 0, 0, 0);
            }
        }
    }
}

bool circle::operator<(const circle &rhs) const {
    return this->getOrigin() < rhs.getOrigin();
}
