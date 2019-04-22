#include "plotterFunctions.h"

void clearScreen(SDL_Plotter &g) {
    for (int r = 0; r < ROW_MAX; r++) {
        for (int c = 0; c < COL_MAX; c++) {
            g.plotPixel(r, c, 255, 255, 255);
        }
    }

    return;
}


void drawCircles(vector<circle> &circles, SDL_Plotter &g) {
    for (int i = 0; i < circles.size(); i++) {
        circles[i].draw(g);
    }

    g.update();

    return;
}

void drawMenu(SDL_Plotter &g) {
    font f;

    f.plotString(point(200, 150), 4, "CSI 3344", color_rgb(0, 0, 0), g);
    f.plotString(point(100, 200), 4, "GROUP PROJECT", color_rgb(0, 0, 0), g);

    f.plotString(point(100, 400), 1, "PRESS 1 FOR BRUTE FORCE CLOSEST PAIR", color_rgb(0, 0, 0), g);
    f.plotString(point(100, 450), 1, "PRESS 2 FOR DIVIDE AND CONQUER CLOSEST PAIR", color_rgb(0, 0, 0), g);
    f.plotString(point(100, 500), 1, "PRESS 3 FOR BRUTE FORCE CONVEX HULL", color_rgb(0, 0, 0), g);
    f.plotString(point(100, 550), 1, "PRESS 4 FOR DIVIDE AND CONQUER CONVEX HULL", color_rgb(0, 0, 0), g);
    g.update();

    return;
}

void generateRandomPoints(vector<circle> &circles, SDL_Plotter &g) {
    for (int i = 0; i < MIN_POINTS + rand() % (MAX_POINTS + 1 - MIN_POINTS); i++) {
        circles.push_back(circle(point((RADIUS + rand() % ((COL_MAX - RADIUS) + 1 - RADIUS)),
                                       (RADIUS + rand() % ((ROW_MAX - RADIUS) + 1 - RADIUS))),
                                 RADIUS, color_rgb(0, 0, 0)));
    }

    drawCircles(circles, g);

    return;
}


