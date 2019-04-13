#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include "point.h"
#include "line.h"
#include "circle.h"


using namespace std;

const int ROW_MAX = 500;
const int RADIUS = 3;
const int COL_MAX = 500;

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
        g.Sleep(500);
        for (int j = 0; j < circles.size(); j++) {
            thisSide = 5;
            oneSide = true;
            if (j != i) {
                line temp(circles[i].getOrigin(), circles[j].getOrigin(), color_rgb(0, 255, 0));
                temp.draw(g);
                g.update();
                g.Sleep(500);

                for (int k = 0; k < circles.size() && oneSide; k++) {
                    if (k != i && k != j) {
                        circles[k].setColor(color_rgb(205, 185, 60));
                        circles[k].draw(g);
                        g.update();
                        g.Sleep(500);

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
                g.Sleep(500);
            }
        }

        circles[i].setColor(color_rgb(0, 0, 0));
        circles[i].draw(g);
        g.Sleep(500);
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

void printHull(set<point> &hull) {
	// a[i].second -> y-coordinate of the ith point
	/*
	if (n < 3)
	{
		cout << "Convex hull not possible\n";
		return;
	}
	*/

	cout << "The points in Convex Hull are: " << endl;
	for (auto i: hull) {
        cout << "(" << i.getX() << ", " << i.getY() << ") ";
	}
	cout << endl;
}

// Driver code
int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    vector<point> points{point(50, 50), point(132, 30), point(400, 100),
                         point(356, 246), point(370, 400), point(140, 378),
                         point(23, 400), point(15, 103)};

    vector<circle> circles;

    for (int i = 0; i < points.size(); i++) {
        circles.push_back(circle(points[i], RADIUS, color_rgb(0, 0, 0)));
    }

	set<point> hull;

	int minIndex = 0, maxIndex = 0;

	for (int i = 1; i < circles.size(); i++) {
        if (circles[i].getOrigin().getX() < circles[minIndex].getOrigin().getX()) {
            minIndex = i;
        }

        if (circles[i].getOrigin().getX() > circles[maxIndex].getOrigin().getX()) {
            maxIndex = i;
        }
	}

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




    while(!g.getQuit()){
		if(g.kbhit()){
			switch(g.getKey()){
			}
		}
		g.update();
	}

	return 0;
}
