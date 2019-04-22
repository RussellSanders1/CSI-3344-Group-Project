#include "divideHullFunctions.h"

using namespace std;

point middle = point(0, 0);

// determines the quadrant of a point
// (used in compare())
int getQuadrant(point p) {
    int quadrant = 0;
	if (p.getX() >= 0 && p.getY() >= 0) {
        quadrant = 1;
	}
	else if (p.getX() <= 0 && p.getY() >= 0) {
        quadrant = 2;
	}
	else if (p.getX() <= 0 && p.getY() <= 0) {
        quadrant = 3;
	}
	else {
        quadrant = 4;
	}

	return quadrant;
}

// Checks whether the line is crossing the polygon
int orientation(point a, point b, point c) {
    int orientation = 0;
	int res = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
			(c.getY() - b.getY()) * (b.getX() - a.getX());

	if (res == 0) {
        orientation = 0;
	}
	else if (res > 0) {
        orientation = 1;
	}
    else {
        orientation = -1;
    }

	return orientation;
}

// compare function for sorting
bool compare(point p1, point q1) {
    bool comparison = false;
	point p(p1.getX() - middle.getX(), p1.getY() - middle.getY());
	point q(q1.getX() - middle.getX(), q1.getY() - middle.getY());

	int one = getQuadrant(p);
	int two = getQuadrant(q);

	if (one != two) {
		comparison = (one < two);
	}
	else {
        comparison = (p.getY() * q.getX() < q.getY() * p.getX());
	}

	return comparison;
}

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<point> merger(vector<point> a, vector<point> b) {
	// n1 -> number of points in polygon a
	// n2 -> number of points in polygon b
	int n1 = a.size(), n2 = b.size();

	int ia = 0, ib = 0;

	//ia -> rightmost point of a
	for (int i = 1; i < n1; i++) {
		if (a[i].getX() > a[ia].getX()) {
			ia = i;
		}
	}

	// ib -> leftmost point of b
	for (int i = 1; i < n2; i++) {
		if (b[i].getX() < b[ib].getX()) {
			ib = i;
		}
	}

	// finding the upper tangent
	int inda = ia, indb = ib;
	bool done = false;

	while (!done) {
		done = true;
		while (orientation(b[indb], a[inda], a[(inda + 1) % n1]) >= 0) {
			inda = (inda + 1) % n1;
		}

		while (orientation(a[inda], b[indb], b[(n2 + indb - 1) % n2]) <= 0) {
			indb = (n2 + indb - 1) % n2;
			done = false;
		}
	}

	int uppera = inda, upperb = indb;
	inda = ia, indb = ib;
	done = false;
	int g = 0;
	//finding the lower tangent
	while (!done) {
		done = true;
		while (orientation(a[inda], b[indb], b[(indb + 1) % n2]) >= 0) {
			indb = (indb + 1) % n2;
		}

		while (orientation(b[indb], a[inda], a[(n1 + inda - 1) % n1]) <= 0) {
			inda = (n1 + inda - 1) % n1;
			done = false;
		}
	}

	int lowera = inda, lowerb = indb;
	vector<point> ret;

	//ret contains the convex hull after merging the two convex hulls
	//with the points sorted in anti-clockwise order
	int ind = uppera;
	ret.push_back(a[uppera]);
	while (ind != lowera) {
		ind = (ind + 1) % n1;
		ret.push_back(a[ind]);
	}

	ind = lowerb;
	ret.push_back(b[lowerb]);
	while (ind != upperb) {
		ind = (ind + 1) % n2;
		ret.push_back(b[ind]);
	}

	return ret;
}

vector<point> bruteHullSimple(vector<circle> &circles) {
    vector<point> hull;
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

        for (int j = 0; j < circles.size() && !added; j++) {
            thisSide = 5;
            oneSide = true;
            if (j != i) {
                line temp(circles[i].getOrigin(), circles[j].getOrigin(), TEMP_LINE_COLOR);

                for (int k = 0; k < circles.size() && oneSide; k++) {
                    if (k != i && k != j) {
                        if (thisSide == 5) {
                            thisSide = findSide(temp, circles[k].getOrigin());
                        }
                        else {
                            if (findSide(temp, circles[k].getOrigin()) != thisSide) {
                                oneSide = false;
                            }
                        }
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
                    nextPoint = j;
                }
            }
        }

        if (nextPoint != -1) {
            i--;
        }
    }

    return hull;
}


// Returns the convex hull for the given set of points
vector<point> divideHull(vector<circle> &a) {
	// If the number of points is less than 6 then the
	// function uses the brute algorithm to find the
	// convex hull
	if (a.size() <= 5) {
        vector<point> ret = bruteHullSimple(a);
        middle.setX(0);
        middle.setY(0);
        int n = ret.size();
        for (int i = 0; i < n; i++) {
            middle.setX(middle.getX() + ret[i].getX());
            middle.setY(middle.getY() + ret[i].getY());
            ret[i].setX(ret[i].getX() * n);
            ret[i].setY(ret[i].getY() * n);
        }
        sort(ret.begin(), ret.end(), compare);
        for (int i = 0; i < ret.size(); i++) {
            ret[i] = point(ret[i].getX() / n, ret[i].getY() / n);
        }

        return ret;
	}

	// left contains the left half points
	// right contains the right half points
	vector<circle> left, right;
	for (int i = 0; i < a.size() / 2; i++) {
		left.push_back(a[i]);
	}
	for (int i = a.size() / 2; i < a.size(); i++) {
		right.push_back(a[i]);
	}
	// convex hull for the left and right sets
	vector<point> leftHull = divideHull(left);
	vector<point> rightHull = divideHull(right);

	// merging the convex hulls
	return merger(leftHull, rightHull);
}
