/*
#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include "point.h"
#include "line.h"
#include "circle.h"
#include <cstdlib>
#include <ctime>
#include "font.h"

using namespace std;

const int ROW_MAX = 800;
const int RADIUS = 3;
const int COL_MAX = 800;
const int MIN_POINTS = 10;
const int MAX_POINTS = 20;
const int SLEEP_TIME = 0;

void clearScreen(SDL_Plotter &g) {
    for (int r = 0; r < ROW_MAX; r++) {
        for (int c = 0; c < COL_MAX; c++) {
            g.plotPixel(r, c, 255, 255, 255);
        }
    }

    return;
}


void drawCircles(vector<circle> circles, SDL_Plotter &g) {
    for (int i = 0; i < circles.size(); i++) {
        circles[i].draw(g);
    }

    g.update();

    return;
}


// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(point p1, point p2, point p) {
	int val = (p.getY() - p1.getY()) * (p2.getX() - p1.getX()) -
			(p2.getY() - p1.getY()) * (p.getX() - p1.getX());

	if (val > 0) {
		return 1;
	}

	if (val < 0) {
		return -1;
	}

	return 0;
}


void bruteHull(vector<circle> &circles, set<point> &hull, SDL_Plotter &g) {
    bool oneSide = true;
    int thisSide = 5;
    for (int i = 0; i < circles.size(); i++) {
        circles[i].setColor(color_rgb(255, 0, 0));
        circles[i].draw(g);
        g.Sleep(SLEEP_TIME);
        for (int j = 0; j < circles.size(); j++) {
            thisSide = 5;
            oneSide = true;
            if (j != i) {
                line temp(circles[i].getOrigin(), circles[j].getOrigin(), color_rgb(0, 255, 0));
                temp.draw(g);
                g.update();
                g.Sleep(SLEEP_TIME);

                for (int k = 0; k < circles.size() && oneSide; k++) {
                    if (k != i && k != j) {
                        circles[k].setColor(color_rgb(205, 185, 60));
                        circles[k].draw(g);
                        g.update();
                        g.Sleep(SLEEP_TIME);

                        if (thisSide == 5) {
                            thisSide = findSide(circles[i].getOrigin(), circles[j].getOrigin(), circles[k].getOrigin());
                        }
                        else {
                            if (findSide(circles[i].getOrigin(), circles[j].getOrigin(), circles[k].getOrigin()) != thisSide) {
                                oneSide = false;
                            }
                        }
                        circles[k].setColor(color_rgb(0, 0, 0));
                        circles[k].draw(g);
                    }
                }
                if (oneSide) {
                    hull.insert(circles[i].getOrigin());
                    hull.insert(circles[j].getOrigin());
                    temp.setColor(color_rgb(0, 0, 255));
                    temp.draw(g);
                }
                else {
                    temp.erase(g);

                    for (int i = 0; i < circles.size(); i++) {
                        circles[i].draw(g);
                    }
                }
                g.update();
                g.Sleep(SLEEP_TIME);
            }
        }

        circles[i].setColor(color_rgb(0, 0, 0));
        circles[i].draw(g);
        g.Sleep(SLEEP_TIME);
    }

    return;
}

// Stores the result (points of convex hull)


// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
/*
int lineDist(point p1, point p2, point p) {
	return abs((p.getY() - p1.getY()) * (p2.getX() - p1.getX()) -
			  (p2.getY() - p1.getY()) * (p.getX() - p1.getX()));
}

// End points of line L are p1 and p2. side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(vector<circle> circles, circle p1, circle p2, int side, set<point> &hull, SDL_Plotter &g) {
    color_rgb previousColor;
	int index = -1, maxDist = 0;

	line temp(p1.getOrigin(), p2.getOrigin(), color_rgb(0, 255, 0));

	temp.draw(g);
	g.update();
	g.Sleep(500);

	// finding the point with maximum distance
	// from L and also on the specified side of L.
	for (int i = 0; i < circles.size(); i++) {
		int temp = lineDist(p1.getOrigin(), p2.getOrigin(), circles[i].getOrigin());
		circles[i].setColor(color_rgb(205, 185, 60));
		circles[i].draw(g);
		g.update();
		g.Sleep(500);

		if (findSide(p1.getOrigin(), p2.getOrigin(), circles[i].getOrigin()) == side && temp > maxDist) {
            if (index != -1) {
                circles[index].setColor(color_rgb(0, 0, 0));
                circles[index].draw(g);
            }
			index = i;
			maxDist = temp;
			circles[i].setColor(color_rgb(255, 0, 0));
			circles[i].draw(g);
			g.update();
			g.Sleep(500);
		}
		if (i != index) {
            circles[i].setColor(color_rgb(0, 0, 0));
            circles[i].draw(g);
            g.Sleep(500);
		}
	}

	// If no point is found, add the end points
	// of L to the convex hull.
	if (index == -1) {
        temp.setColor(color_rgb(0, 0, 255));
        temp.draw(g);

		hull.insert(p1.getOrigin());
		hull.insert(p2.getOrigin());
		g.update();
		g.Sleep(500);

		return;
	}
    g.update();
	// Recur for the two parts divided by a[ind]
	quickHull(circles, circles[index], p1, -findSide(circles[index].getOrigin(), p1.getOrigin(), p2.getOrigin()), hull, g);
	quickHull(circles, circles[index], p2, -findSide(circles[index].getOrigin(), p2.getOrigin(), p1.getOrigin()), hull, g);
    temp.erase(g);
    for (int i = 0; i < circles.size(); i++) {
        circles[i].draw(g);
    }

}
*/
/*
void printHull(set<point> &hull) {
	// a[i].second -> y-coordinate of the ith point
	/*
	if (n < 3)
	{
		cout << "Convex hull not possible\n";
		return;
	}
	*/
    /*
	cout << "The points in Convex Hull are: " << endl;
	for (auto i: hull) {
        cout << "(" << i.getX() << ", " << i.getY() << ") ";
	}
	cout << endl;
}

// Driver code
int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    int tempX = 0, tempY = 0;
    font f;
    char input = '\0';
    /*
    vector<point> points{point(50, 50), point(132, 30), point(400, 100),
                         point(356, 246), point(370, 400), point(140, 378),
                         point(23, 400), point(15, 103)};
    */
    //vector<circle> circles;
    /*
    for (int i = 0; i < points.size(); i++) {
        circles.push_back(circle(points[i], RADIUS, color_rgb(0, 0, 0)));
    }
    */

	//set<point> hull;

	//int minIndex = 0, maxIndex = 0;

	//srand(time(0));

	/*
	for (int i = 1; i < circles.size(); i++) {
        if (circles[i].getOrigin().getX() < circles[minIndex].getOrigin().getX()) {
            minIndex = i;
        }

        if (circles[i].getOrigin().getX() > circles[maxIndex].getOrigin().getX()) {
            maxIndex = i;
        }
	}
	*/

	/*
    for (int i = 0; i < circles.size(); i++) {
       circles[i].draw(g);
	}
	g.update();

	// Recursively find convex hull points on
	// one side of line joining a[min_x] and
	// a[max_x]
	//quickHull(circles, circles[minIndex], circles[maxIndex], 1, hull, g);

	// Recursively find convex hull points on
	// other side of line joining a[min_x] and
	// a[max_x]
	//quickHull(circles, circles[minIndex], circles[maxIndex], -1, hull, g);
    bruteHull(circles, hull, g);
	printHull(hull);
	*/
	/*
    while (!g.getQuit()) {
        f.plotString(point(200, 150), 4, "CSI 3344", color_rgb(0, 0, 0), g);
        f.plotString(point(100, 200), 4, "GROUP PROJECT", color_rgb(0, 0, 0), g);

        f.plotString(point(100, 400), 1, "PRESS 1 FOR BRUTE FORCE CLOSEST PAIR", color_rgb(0, 0, 0), g);
        f.plotString(point(100, 450), 1, "PRESS 2 FOR DIVIDE AND CONQUER CLOSEST PAIR", color_rgb(0, 0, 0), g);
        f.plotString(point(100, 500), 1, "PRESS 3 FOR BRUTE FORCE CONVEX HULL", color_rgb(0, 0, 0), g);
        f.plotString(point(100, 550), 1, "PRESS 4 FOR DIVIDE AND CONQUER CONVEX HULL", color_rgb(0, 0, 0), g);
        g.update();
        input = '\0';

        while (!g.getQuit() && input != '1' && input != '2' && input != '3' && input != '4') {
            if (g.kbhit()) {
                input = g.getKey();
            }
        }

        clearScreen(g);

        switch(input) {
            case '3':
                while(!g.getQuit() && input != LEFT_ARROW){
                    if(g.kbhit()){
                        input = g.getKey();
                        cout << g.getKey() << endl;
                        switch(input){
                            case 'R':
                                for (int i = 0; i < MIN_POINTS + rand() % (MAX_POINTS + 1 - MIN_POINTS); i++) {
                                    circles.push_back(circle(point((RADIUS + rand() % (COL_MAX + 1 - RADIUS)), (RADIUS + rand() % (ROW_MAX + 1 - RADIUS))), RADIUS, color_rgb(0, 0, 0)));
                                }

                                drawCircles(circles, g);
                                break;

                            case '(':
                                bruteHull(circles, hull, g);
                                printHull(hull);
                                break;

                            case 'E':
                                clearScreen(g);
                                circles.clear();
                                hull.clear();
                                break;
                            case RIGHT_ARROW:
                                clearScreen(g);
                                break;

                            default: break;
                        }
                    }

                    else if (g.getMouseClick(tempX, tempY)) {
                        cout << "click" << endl;
                        if (tempX > RADIUS && tempY > RADIUS) {
                            circles.push_back(circle(point(tempX, tempY), RADIUS, color_rgb(0, 0, 0)));
                            circles[circles.size() - 1].draw(g);
                        }
                    }

                    g.update();
                }
                break;

            default: break;
        }
        clearScreen(g);
    }

	return 0;
}
*/

