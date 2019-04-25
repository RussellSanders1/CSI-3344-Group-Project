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

    return;
}

void printHull(vector<circle> &hull, ostream &out) {
	if (hull.size() >= 3) {
        out << "The points in Convex Hull are: " << endl;
        for (int i = 0; i < hull.size(); i++) {
            out << "(" << hull[i].getOrigin().getX() << ", " << hull[i].getOrigin().getY() << ") ";
        }
	}

	out << endl;

	return;
}


void printPair(line a, ostream &out) {
    if (a.getP1() == a.getP2()) {
        return;
    }
    out << "Closest pair: (" << a.getP1().getX() << ", " << a.getP1().getY();
    out << ") (" << a.getP2().getX() << ", " << a.getP2().getY() << ")" << endl;
}

bool isStraightLine(vector<circle> &circles) {
    bool isStraight = true;
    sort(circles.begin(), circles.end());
    line temp(circles[0].getOrigin(), circles[circles.size() - 1].getOrigin());

    for (int i = 1; i < circles.size() - 1 && isStraight; i++) {
        if (!temp.intersects(circles[i].getOrigin())) {
            isStraight = false;
        }
    }

    return isStraight;
}

void eliminateDuplicates(vector<circle> &circles) {
    set<circle> s;

    for (int i = 0; i < circles.size(); i++) {
        s.insert(circles[i]);
    }

    circles.clear();

    for (auto i: s) {
        circles.push_back(i);
    }

    return;
}

