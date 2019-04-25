#include "divideHullFunctions.h"

using namespace std;

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
int orientation(line l, point p) {
    int orientation = 0;
	int res = (l.getP2().getY() - l.getP1().getY()) * (p.getX() - l.getP2().getX()) -
			(p.getY() - l.getP2().getY()) * (l.getP2().getX() - l.getP1().getX());

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

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<circle> merger(vector<circle> &left, vector<circle> &right, SDL_Plotter &g) {
	// n1 -> number of points in polygon a
	// n2 -> number of points in polygon b
	int leftSize = left.size();
	int rightSize = right.size();

	int rightMost = 0, leftMost = 0;

	//ia -> rightmost point of a
	for (int i = 1; i < leftSize; i++) {
		if (left[i].getOrigin().getX() > left[rightMost].getOrigin().getX()) {
			rightMost = i;
		}
	}

	left[rightMost].setColor(FIRST_SELECTED_POINT_COLOR);
	left[rightMost].draw(g);

	// ib -> leftmost point of b
	for (int i = 1; i < rightSize; i++) {
		if (right[i].getOrigin().getX() < right[leftMost].getOrigin().getX()) {
			leftMost = i;
		}
	}

	right[leftMost].setColor(FIRST_SELECTED_POINT_COLOR);
	right[leftMost].draw(g);

	g.update();
	g.Sleep(SLEEP_TIME);

	// finding the upper tangent
	int tempLeft = rightMost, tempRight = leftMost;
	bool foundTangent = false;

	line upperTangent(left[rightMost].getOrigin(), right[leftMost].getOrigin(), TEMP_LINE_COLOR);

	while (!foundTangent) {
        upperTangent.draw(g);
        g.update();
        g.Sleep(SLEEP_TIME);
		foundTangent = true;
		//modulation cycles through the set of points going forward
		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(tempLeft + 1) % leftSize].getOrigin()) >= 0) {
            left[tempLeft].setColor(BLACK);
            left[tempLeft].draw(g);
			tempLeft = (tempLeft + 1) % leftSize;
			left[tempLeft].setColor(FIRST_SELECTED_POINT_COLOR);
			left[tempLeft].draw(g);
			g.update();
			g.Sleep(SLEEP_TIME);
		}
        //modulation cycles through the set of points going backwards
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(rightSize + tempRight - 1) % rightSize].getOrigin()) <= 0) {
            right[tempRight].setColor(BLACK);
            right[tempRight].draw(g);
			tempRight = (rightSize + tempRight - 1) % rightSize;
			foundTangent = false;
			right[tempRight].setColor(FIRST_SELECTED_POINT_COLOR);
			right[tempRight].draw(g);
			g.update();
			g.Sleep(SLEEP_TIME);
		}

		upperTangent.erase(g);
		upperTangent.setP1(left[tempLeft].getOrigin());
		upperTangent.setP2(right[tempRight].getOrigin());
	}

	left[tempLeft].setColor(BLACK);
	left[tempLeft].draw(g);
	right[tempRight].setColor(BLACK);
	right[tempRight].draw(g);

	upperTangent.setColor(HULL_LINE_COLOR);
	upperTangent.draw(g);
	g.update();

	int upperLeft = tempLeft, upperRight = tempRight;
	tempLeft = rightMost, tempRight = leftMost;
	foundTangent = false;
	left[tempLeft].setColor(FIRST_SELECTED_POINT_COLOR);
	left[tempLeft].draw(g);
	right[tempRight].setColor(FIRST_SELECTED_POINT_COLOR);
	right[tempRight].draw(g);

	line lowerTangent(left[tempLeft].getOrigin(), right[tempRight].getOrigin(), TEMP_LINE_COLOR);
	//int g = 0;
	//finding the lower tangent
	while (!foundTangent) {
		foundTangent = true;
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(tempRight+ 1) % rightSize].getOrigin()) >= 0) {
            right[tempRight].setColor(BLACK);
            right[tempRight].draw(g);
			tempRight = (tempRight + 1) % rightSize;
            right[tempRight].setColor(FIRST_SELECTED_POINT_COLOR);
			right[tempRight].draw(g);
			g.update();
			g.Sleep(SLEEP_TIME);

		}

		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(leftSize + tempLeft - 1) % leftSize].getOrigin()) <= 0) {
            left[tempLeft].setColor(BLACK);
            left[tempLeft].draw(g);
			tempLeft = (leftSize + tempLeft - 1) % leftSize;
			foundTangent = false;
			left[tempLeft].setColor(FIRST_SELECTED_POINT_COLOR);
			left[tempLeft].draw(g);
			g.update();
			g.Sleep(SLEEP_TIME);
		}

        lowerTangent.erase(g);
		lowerTangent.setP1(left[tempLeft].getOrigin());
		lowerTangent.setP2(right[tempRight].getOrigin());
	}

    left[tempLeft].setColor(BLACK);
	left[tempLeft].draw(g);
	right[tempRight].setColor(BLACK);
	right[tempRight].draw(g);

	lowerTangent.setColor(HULL_LINE_COLOR);
	lowerTangent.draw(g);
	g.update();
	g.Sleep(SLEEP_TIME);

    line tempLine;

    for (int i = 0; i < left.size() - 1; i++) {
        tempLine.setP1(left[i].getOrigin());
        tempLine.setP2(left[i + 1].getOrigin());
        tempLine.erase(g);
    }

    tempLine.setP1(left[0].getOrigin());
    tempLine.setP2(left[left.size() - 1].getOrigin());
    tempLine.erase(g);

    for (int i = 0; i < right.size() - 1; i++) {
        tempLine.setP1(right[i].getOrigin());
        tempLine.setP2(right[i + 1].getOrigin());
        tempLine.erase(g);
    }

    tempLine.setP1(right[0].getOrigin());
    tempLine.setP2(right[right.size() - 1].getOrigin());
    tempLine.erase(g);

	int lowerLeft = tempLeft, lowerRight= tempRight;
	vector<circle> merged;

	//ret contains the convex hull after merging the two convex hulls
	//with the points sorted in anti-clockwise order
	int tempMerged = upperLeft;
	merged.push_back(left[upperLeft]);
	while (tempMerged != lowerLeft) {
		tempMerged = (tempMerged + 1) % leftSize;
		merged.push_back(left[tempMerged]);
	}

	tempMerged = lowerRight;
	merged.push_back(right[lowerRight]);
	while (tempMerged != upperRight) {
		tempMerged = (tempMerged + 1) % rightSize;
		merged.push_back(right[tempMerged]);
	}

	tempLine.setColor(HULL_LINE_COLOR);

	for (int i = 0; i < merged.size() - 1; i++) {
        tempLine.setP1(merged[i].getOrigin());
        tempLine.setP2(merged[i + 1].getOrigin());
        tempLine.draw(g);
	}

	tempLine.setP1(merged[0].getOrigin());
	tempLine.setP2(merged[merged.size() - 1].getOrigin());
	tempLine.draw(g);

	drawCircles(left, g);
	drawCircles(right, g);
	g.Sleep(SLEEP_TIME);

	return merged;
}

// Returns the convex hull for the given set of points
vector<circle> divideHull(vector<circle> &circles, SDL_Plotter &g) {
    if (circles.size() <  3) {
        return vector<circle>();
    }
    sort(circles.begin(), circles.end());
    point middle;
	// If the number of points is less than 6 then the
	// function uses the brute algorithm to find the
	// convex hull
	if (circles.size() <= BRUTEFORCE_MIN) {
        vector<circle> hull = bruteHull(circles, g);
        middle.setX(0);
        middle.setY(0);
        int n = hull.size();
        for (int i = 0; i < n; i++) {
            middle.setX(middle.getX() + hull[i].getOrigin().getX());
            middle.setY(middle.getY() + hull[i].getOrigin().getY());
            hull[i].setOrigin(point(hull[i].getOrigin().getX() * n, hull[i].getOrigin().getY() * n));
        }

        auto comp = [&](circle p1, circle q1)-> bool{
            bool comparison;
            point p(p1.getOrigin().getX() - middle.getX(), p1.getOrigin().getY() - middle.getY());
            point q(q1.getOrigin().getX() - middle.getX(), q1.getOrigin().getY() - middle.getY());

            int one = getQuadrant(p);
            int two = getQuadrant(q);

            if (one != two) {
                comparison = (one < two);
            }
            else {
                comparison = (p.getY() * q.getX() < q.getY() * p.getX());
            }

            return comparison;
        };

        sort(hull.begin(), hull.end(), comp);
        for (int i = 0; i < hull.size(); i++) {
            hull[i].setOrigin(point((hull[i].getOrigin().getX() / n), (hull[i].getOrigin().getY() / n)));
        }

        return hull;
	}

	// left contains the left half points
	// right contains the right half points
	vector<circle> left, right;
	for (int i = 0; i < circles.size() / 2; i++) {
		left.push_back(circles[i]);
	}
	for (int i = circles.size() / 2; i < circles.size(); i++) {
		right.push_back(circles[i]);
	}

	for (int i = 0; i < right.size(); i++) {
        right[i].setColor(HIDDEN_COLOR);
	}
	drawCircles(right, g);
	g.Sleep(SLEEP_TIME);

	// convex hull for the left and right sets
	vector<circle> leftHull = divideHull(left, g);

	for (int i = 0; i < right.size(); i++) {
        right[i].setColor(BLACK);
	}
	drawCircles(right, g);

	vector<circle> rightHull = divideHull(right, g);

	drawCircles(circles, g);

	// merging the convex hulls
	return merger(leftHull, rightHull, g);
}
