#include "bruteHullFunctions.h"

int findSide(line l, point p) {
	int val = (p.getY() - l.getP1().getY()) * (l.getP2().getX() - l.getP1().getX()) -
			(l.getP2().getY() - l.getP1().getY()) * (p.getX() - l.getP1().getX());
	if (val > 0) {
		return 1;
	}

	if (val < 0) {
		return -1;
	}

	return 0;
}


vector<point> bruteHull(vector<circle> &circles, SDL_Plotter &g) {
    clearScreen(g);
    drawCircles(circles, g);
    g.update();

    vector<point> hull;
    vector<line> hullLines;
    bool added = false;
    bool finished = false;
    bool oneSide = true;
    int thisSide = 5;
    int nextPoint = -1;

    if (circles.size() < 3) {
        return hull;
    }

    for (int i = 0; i < circles.size() && !finished; i++) {
        if (hull.size() != 0) {
            finished = true;
        }

        added = false;

        if (nextPoint != -1) {
            i = nextPoint;
        }

        circles[i].setColor(FIRST_SELECTED_POINT_COLOR);
        circles[i].draw(g);
        g.Sleep(SLEEP_TIME);

        for (int j = 0; j < circles.size() && !added; j++) {
            thisSide = 5;
            oneSide = true;
            if (j != i) {
                line temp(circles[i].getOrigin(), circles[j].getOrigin(), TEMP_LINE_COLOR);
                temp.draw(g);
                g.update();
                g.Sleep(SLEEP_TIME);

                for (int k = 0; k < circles.size() && oneSide; k++) {
                    if (k != i && k != j) {
                        circles[k].setColor(SECOND_SELECTED_POINT_COLOR);
                        circles[k].draw(g);
                        g.update();
                        g.Sleep(SLEEP_TIME);

                        if (thisSide == 5) {
                            thisSide = findSide(temp, circles[k].getOrigin());
                        }
                        else {
                            if (findSide(temp, circles[k].getOrigin()) != thisSide) {
                                oneSide = false;
                            }
                        }
                        circles[k].setColor(BLACK);
                        circles[k].draw(g);
                    }
                }
                if (oneSide) {
                    if (nextPoint == -1) {
                        hull.push_back(circles[i].getOrigin());
                    }
                    added = true;
                    finished = false;
                    for (int search = 0; search < hull.size(); search++) {
                        if (hull[search] == circles[j].getOrigin()) {
                            added = false;
                            finished = true;
                        }
                    }

                    if (added == true) {
                        hull.push_back(circles[j].getOrigin());
                    }

                    temp.setColor(HULL_LINE_COLOR);
                    hullLines.push_back(temp);

                    nextPoint = j;
                }
                else {
                    temp.erase(g);
                }

                for (int circleIndex = 0; circleIndex < circles.size(); circleIndex++) {
                    circles[circleIndex].draw(g);
                }
                for (int linesIndex = 0; linesIndex < hullLines.size(); linesIndex++) {
                    hullLines[linesIndex].draw(g);
                }
                g.update();
                g.Sleep(SLEEP_TIME);
            }
        }

        circles[i].setColor(BLACK);
        circles[i].draw(g);
        g.Sleep(SLEEP_TIME);

        if (nextPoint != -1) {
            i--;
        }
    }

    return hull;
}

void printHull(vector<point> &hull) {
	if (hull.size() >= 3) {
        cout << "The points in Convex Hull are: " << endl;
        for (int i = 0; i < hull.size(); i++) {
            cout << "(" << hull[i].getX() << ", " << hull[i].getY() << ") ";
        }
	}

	cout << endl;

	return;
}
