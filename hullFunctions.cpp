#include "hullFunctions.h"

using namespace std;

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
vector<circle> merger(vector<circle> &left, vector<circle> &right, SDL_Plotter &g, const bool fastMode) {
	int leftSize = left.size();
	int rightSize = right.size();
	int sleepTime = DIVIDE_SLEEP_TIME;
	if (fastMode) {
        sleepTime /= 10;
	}

	int rightMost = 0, leftMost = 0;

	for (int i = 1; i < leftSize; i++) {
		if (left[i].getOrigin().getX() > left[rightMost].getOrigin().getX()) {
			rightMost = i;
		}
	}

	left[rightMost].setColor(FIRST_SELECTED_POINT_COLOR);
	left[rightMost].draw(g);

	for (int i = 1; i < rightSize; i++) {
		if (right[i].getOrigin().getX() < right[leftMost].getOrigin().getX()) {
			leftMost = i;
		}
	}

	right[leftMost].setColor(FIRST_SELECTED_POINT_COLOR);
	right[leftMost].draw(g);

	g.update();
	g.Sleep(sleepTime);

	// finding the upper tangent
	int tempLeft = rightMost, tempRight = leftMost;
	bool foundTangent = false;

	line upperTangent(left[rightMost].getOrigin(), right[leftMost].getOrigin(), TEMP_LINE_COLOR);
    upperTangent.draw(g);
    g.update();
    g.Sleep(sleepTime);


	while (!foundTangent) {
		foundTangent = true;
		//modulation cycles through the set of points going forward
		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(tempLeft + 1) % leftSize].getOrigin()) >= 0) {
            left[tempLeft].setColor(BLACK);
            left[tempLeft].draw(g);

			tempLeft = (tempLeft + 1) % leftSize;
			left[tempLeft].setColor(FIRST_SELECTED_POINT_COLOR);
			left[tempLeft].draw(g);

			upperTangent.erase(g);
			upperTangent.setP1(left[tempLeft].getOrigin());
			upperTangent.draw(g);
			g.update();
			g.Sleep(sleepTime);
		}
        //modulation cycles through the set of points going backwards
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(rightSize + tempRight - 1) % rightSize].getOrigin()) <= 0) {
            right[tempRight].setColor(BLACK);
            right[tempRight].draw(g);

			tempRight = (rightSize + tempRight - 1) % rightSize;
			right[tempRight].setColor(FIRST_SELECTED_POINT_COLOR);
			right[tempRight].draw(g);

            foundTangent = false;

			upperTangent.erase(g);
			upperTangent.setP2(right[tempRight].getOrigin());
			upperTangent.draw(g);
			g.update();
			g.Sleep(sleepTime);
		}
	}

	left[tempLeft].setColor(BLACK);
	left[tempLeft].draw(g);
	right[tempRight].setColor(BLACK);
	right[tempRight].draw(g);

	upperTangent.setColor(SELECTED_LINE_COLOR);
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
    lowerTangent.draw(g);
    g.update();
    g.Sleep(sleepTime);

	//finding the lower tangent
	while (!foundTangent) {
		foundTangent = true;
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(tempRight+ 1) % rightSize].getOrigin()) >= 0) {
            right[tempRight].setColor(BLACK);
            right[tempRight].draw(g);

			tempRight = (tempRight + 1) % rightSize;
            right[tempRight].setColor(FIRST_SELECTED_POINT_COLOR);
			right[tempRight].draw(g);

			lowerTangent.erase(g);
			lowerTangent.setP2(right[tempRight].getOrigin());
			lowerTangent.draw(g);
			g.update();
			g.Sleep(sleepTime);
		}

		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(leftSize + tempLeft - 1) % leftSize].getOrigin()) <= 0) {
            left[tempLeft].setColor(BLACK);
            left[tempLeft].draw(g);

			tempLeft = (leftSize + tempLeft - 1) % leftSize;
			left[tempLeft].setColor(FIRST_SELECTED_POINT_COLOR);
			left[tempLeft].draw(g);

            foundTangent = false;

			lowerTangent.erase(g);
			lowerTangent.setP1(left[tempLeft].getOrigin());
			lowerTangent.draw(g);
			g.update();
			g.Sleep(sleepTime);
		}
	}
    left[tempLeft].setColor(BLACK);
	left[tempLeft].draw(g);
	right[tempRight].setColor(BLACK);
	right[tempRight].draw(g);

	for (int i = 0; i < right.size(); i++) {
        right[i].setColor(BLACK);
	}
	for (int i = 0; i < left.size(); i++) {
        left[i].setColor(BLACK);
	}
	drawCircles(left, g);
	drawCircles(right, g);

	lowerTangent.setColor(SELECTED_LINE_COLOR);
	lowerTangent.draw(g);
	g.update();
	g.Sleep(sleepTime);

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

	tempLine.setColor(SELECTED_LINE_COLOR);

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
	g.Sleep(sleepTime);

	return merged;
}

// Returns the convex hull for the given set of points
vector<circle> divideHull(vector<circle> &circles, SDL_Plotter &g, const bool fastMode) {
    if (circles.size() <  3) {
        return vector<circle>();
    }
    sort(circles.begin(), circles.end());
    int sleepTime = DIVIDE_SLEEP_TIME;
    if (fastMode) {
        sleepTime /= 10;
    }
    point middle;
	// If the number of points is less than 6 then the
	// function uses the brute algorithm to find the
	// convex hull
	if (circles.size() <= BRUTEFORCE_MIN) {
        vector<circle> hull = bruteHull(circles, g, fastMode);
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

            int one = p.getQuadrant();
            int two = q.getQuadrant();

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

	line boundary;
	boundary.setColor(HIDDEN_COLOR);
	boundary.setP1(point(right[0].getOrigin().getX() - RADIUS, 0));
	boundary.setP2(point(right[0].getOrigin().getX() - RADIUS, ROW_MAX));
	boundary.draw(g);
	drawCircles(right, g);
	g.Sleep(sleepTime);

	// convex hull for the left and right sets
	vector<circle> leftHull = divideHull(left, g, fastMode);

	for (int i = 0; i < right.size(); i++) {
        right[i].setColor(BLACK);
	}
	drawCircles(right, g);

	vector<circle> rightHull = divideHull(right, g, fastMode);

    boundary.erase(g);
	drawCircles(right, g);

	if (leftHull.size() == 0 || rightHull.size() == 0) {
        left.insert(left.end(), right.begin(), right.end());

        vector<circle> hull = bruteHull(left, g, fastMode);
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

            int one = p.getQuadrant();
            int two = q.getQuadrant();

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

	drawCircles(circles, g);

	// merging the convex hulls
	return merger(leftHull, rightHull, g, fastMode);
}

vector<circle> bruteHull(vector<circle> &circles, SDL_Plotter &g, const bool fastMode) {
    int sleepTime = BRUTE_SLEEP_TIME;
    if (fastMode) {
        sleepTime /= 10;
    }

    vector<circle> hull;
    vector<line> hullLines;
    bool added = false;
    bool finished = false;
    bool oneSide = true;
    bool noHull = true;
    int thisSide = 5;
    int nextPoint = -1;

    if (circles.size() < 3) {
        return hull;
    }

    if (isStraightLine(circles)) {
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
        g.Sleep(sleepTime);

        for (int j = 0; j < circles.size() && !added; j++) {
            thisSide = 5;
            oneSide = true;
            if (j != i) {
                line temp(circles[i].getOrigin(), circles[j].getOrigin(), TEMP_LINE_COLOR);
                temp.draw(g);
                g.update();
                g.Sleep(sleepTime);

                for (int k = 0; k < circles.size() && oneSide; k++) {
                    if (k != i && k != j) {
                        circles[k].setColor(SECOND_SELECTED_POINT_COLOR);
                        circles[k].draw(g);
                        g.update();
                        g.Sleep(sleepTime);

                        if (thisSide == 5 && temp.findSide(circles[k].getOrigin()) != 0) {
                            thisSide = temp.findSide(circles[k].getOrigin());
                        }
                        else {
                            if (temp.findSide(circles[k].getOrigin()) != thisSide &&
                                temp.findSide(circles[k].getOrigin()) != 0) {
                                oneSide = false;
                            }
                        }
                        circles[k].setColor(BLACK);
                        circles[k].draw(g);
                    }
                }
                if (oneSide) {
                    if (nextPoint == -1) {
                        hull.push_back(circles[i]);
                    }
                    added = true;
                    finished = false;
                    for (int search = 0; search < hull.size(); search++) {
                        if (hull[search].getOrigin() == circles[j].getOrigin()) {
                            added = false;
                            finished = true;
                        }
                    }

                    if (added == true) {
                        hull.push_back(circles[j]);
                    }

                    temp.setColor(SELECTED_LINE_COLOR);
                    hullLines.push_back(temp);

                    nextPoint = j;
                }
                else {
                    temp.erase(g);
                }

                drawCircles(circles, g);

                for (int linesIndex = 0; linesIndex < hullLines.size(); linesIndex++) {
                    hullLines[linesIndex].draw(g);
                }
                g.update();
                g.Sleep(sleepTime);
            }
        }

        circles[i].setColor(BLACK);
        circles[i].draw(g);
        g.Sleep(sleepTime);

        if (nextPoint != -1) {
            i--;
        }
    }

    return hull;
}

vector<circle> mergerSimple(vector<circle> &left, vector<circle> &right) {
	int leftSize = left.size();
	int rightSize = right.size();

	int rightMost = 0, leftMost = 0;

	for (int i = 1; i < leftSize; i++) {
		if (left[i].getOrigin().getX() > left[rightMost].getOrigin().getX()) {
			rightMost = i;
		}
	}

	for (int i = 1; i < rightSize; i++) {
		if (right[i].getOrigin().getX() < right[leftMost].getOrigin().getX()) {
			leftMost = i;
		}
	}

	// finding the upper tangent
	int tempLeft = rightMost, tempRight = leftMost;
	bool foundTangent = false;


	while (!foundTangent) {
		foundTangent = true;
		//modulation cycles through the set of points going forward
		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(tempLeft + 1) % leftSize].getOrigin()) >= 0) {
			tempLeft = (tempLeft + 1) % leftSize;
		}
        //modulation cycles through the set of points going backwards
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(rightSize + tempRight - 1) % rightSize].getOrigin()) <= 0) {
			tempRight = (rightSize + tempRight - 1) % rightSize;
            foundTangent = false;
		}
	}

	int upperLeft = tempLeft, upperRight = tempRight;
	tempLeft = rightMost, tempRight = leftMost;
	foundTangent = false;

	//finding the lower tangent
	while (!foundTangent) {
		foundTangent = true;
		while (orientation(line(left[tempLeft].getOrigin(), right[tempRight].getOrigin()), right[(tempRight+ 1) % rightSize].getOrigin()) >= 0) {
			tempRight = (tempRight + 1) % rightSize;
		}

		while (orientation(line(right[tempRight].getOrigin(), left[tempLeft].getOrigin()), left[(leftSize + tempLeft - 1) % leftSize].getOrigin()) <= 0) {
			tempLeft = (leftSize + tempLeft - 1) % leftSize;
            foundTangent = false;
		}
	}

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

	return merged;
}

vector<circle> divideHullSimple(vector<circle> &circles) {
    if (circles.size() <  3) {
        return vector<circle>();
    }
    sort(circles.begin(), circles.end());
    point middle;
	// If the number of points is less than 6 then the
	// function uses the brute algorithm to find the
	// convex hull
	if (circles.size() <= BRUTEFORCE_MIN) {
        vector<circle> hull = bruteHullSimple(circles);
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

            int one = p.getQuadrant();
            int two = q.getQuadrant();

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

	// convex hull for the left and right sets
	vector<circle> leftHull = divideHullSimple(left);

	vector<circle> rightHull = divideHullSimple(right);

	if (leftHull.size() == 0 || rightHull.size() == 0) {
        left.insert(left.end(), right.begin(), right.end());

        vector<circle> hull = bruteHullSimple(left);
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

            int one = p.getQuadrant();
            int two = q.getQuadrant();

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

	// merging the convex hulls
	return mergerSimple(leftHull, rightHull);
}

vector<circle> bruteHullSimple(vector<circle> &circles) {
    vector<circle> hull;
    bool added = false;
    bool finished = false;
    bool oneSide = true;
    bool noHull = true;
    int thisSide = 5;
    int nextPoint = -1;

    if (circles.size() < 3) {
        return hull;
    }

    if (isStraightLine(circles)) {
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
                        if (thisSide == 5 && temp.findSide(circles[k].getOrigin()) != 0) {
                            thisSide = temp.findSide(circles[k].getOrigin());
                        }
                        else {
                            if (temp.findSide(circles[k].getOrigin()) != thisSide &&
                                temp.findSide(circles[k].getOrigin()) != 0) {
                                oneSide = false;
                            }
                        }
                    }
                }
                if (oneSide) {
                    if (nextPoint == -1) {
                        hull.push_back(circles[i]);
                    }
                    added = true;
                    finished = false;
                    for (int search = 0; search < hull.size(); search++) {
                        if (hull[search].getOrigin() == circles[j].getOrigin()) {
                            added = false;
                            finished = true;
                        }
                    }

                    if (added == true) {
                        hull.push_back(circles[j]);
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



