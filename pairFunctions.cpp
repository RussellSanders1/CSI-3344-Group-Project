#include "pairFunctions.h"

bool compareY(const circle &a, const circle &b) {
    return a.getOrigin().getY() < b.getOrigin().getY();
}

line smallestDistance(line a, line b){
    line closest;
	// a is shorter than b
    if(a.distance() <= b.distance()){
        closest = a;
    }
	// b is shorter than a
    else{
        closest = b;
    }
    return closest;
}


line brutePair(vector<circle> &circles, SDL_Plotter &g, const bool fastMode){
    double closestDist = numeric_limits<double>::max();
    double dist = 0;
    int sleepTime = BRUTE_SLEEP_TIME;
    if (fastMode) {
        sleepTime /= 10;
    }

    circle p1, p2;

    line temp, closest;
    closest.setColor(SELECTED_LINE_COLOR);
    temp.setColor(TEMP_LINE_COLOR);
	
	// If there are not enough points, short circuit
    if (circles.size() <= 1) {
        return line(point(-1, -1), point(-1, -1));
    }
	
	
    for (int i = 0; i < circles.size(); i++) {
        circles[i].setColor(FIRST_SELECTED_POINT_COLOR);
        circles[i].draw(g);
        g.update();
        g.Sleep(sleepTime);

        for (int j = 0; j < circles.size(); j++) {
            if(i != j) {
                circles[j].setColor(FIRST_SELECTED_POINT_COLOR);
                circles[j].draw(g);
                g.Sleep(sleepTime);

                temp.setP1(circles[i].getOrigin());
                temp.setP2(circles[j].getOrigin());
                temp.draw(g);
                g.update();
                g.Sleep(sleepTime);

                dist = temp.distance();

                if(dist < closestDist){
                    closestDist = dist;
                    closest.erase(g);
                    closest.setP1(circles[i].getOrigin());
                    closest.setP2(circles[j].getOrigin());
                    closest.draw(g);
                    circle(closest.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
                    circle(closest.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
                    g.update();
                    g.Sleep(sleepTime);
                }

                temp.erase(g);
                closest.draw(g);

                circles[j].setColor(BLACK);
                drawCircles(circles, g);
                circle(closest.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
                circle(closest.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
                g.update();
            }
        }

        circles[i].setColor(BLACK);
        circles[i].draw(g);
    }

    return closest;
}

line stripClosestPair(vector<circle> &strip, SDL_Plotter &g, const bool fastMode){
	// If there are not enough points, short circuit
    if (strip.size() <= 1) {
        return line(point (-1, -1), point(-1, -1));
    }
    int sleepTime = DIVIDE_SLEEP_TIME;
    if (fastMode) {
        sleepTime /= 10;
    }

    double min = numeric_limits<double>::max();
	
	
	// Draw the left and right boundary of the strip
    line leftBoundary, rightBoundary;
    leftBoundary.setColor(STRIP_COLOR);
    rightBoundary.setColor(STRIP_COLOR);
    sort(strip.begin(), strip.end());

    leftBoundary.setP1(point(strip[0].getOrigin().getX() - RADIUS, 0));
    leftBoundary.setP2(point(strip[0].getOrigin().getX() - RADIUS, ROW_MAX));

    rightBoundary.setP1(point(strip[strip.size() - 1].getOrigin().getX() + RADIUS, 0));
    rightBoundary.setP2(point(strip[strip.size() - 1].getOrigin().getX() + RADIUS, ROW_MAX));

    leftBoundary.draw(g);
    rightBoundary.draw(g);

    sort(strip.begin(),strip.end(), compareY);

    line temp, closest;
    temp.setColor(TEMP_LINE_COLOR);
    closest.setColor(SELECTED_LINE_COLOR);

	
    for(int i = 0; i < strip.size(); i++){
        for(int j = i + 1; j < strip.size() && (strip[j].getOrigin().getY() - strip[i].getOrigin().getY()) < min; j++){
            if (i != j) {
                temp.setP1(strip[i].getOrigin());
                temp.setP2(strip[j].getOrigin());
                temp.setColor(TEMP_LINE_COLOR);
                temp.draw(g);
                g.update();
                g.Sleep(sleepTime);
                temp.erase(g);
                if(line(strip[i].getOrigin(), strip[j].getOrigin()).distance() < min) {
                    closest.erase(g);

                    min = line(strip[i].getOrigin(),strip[j].getOrigin()).distance();
                    closest.setP1(strip[i].getOrigin());
                    closest.setP2(strip[j].getOrigin());
                    closest.setColor(SELECTED_LINE_COLOR);
                    closest.draw(g);
                    circle(closest.getP1(), RADIUS, STRIP_COLOR).draw(g);
                    circle(closest.getP2(), RADIUS, STRIP_COLOR).draw(g);
                    g.update();
                    g.Sleep(sleepTime);
                }
                closest.draw(g);
            }
        }
    }
	
	// Erase the strip boundary and draw closest pair in strip
    leftBoundary.erase(g);
    rightBoundary.erase(g);
    drawCircles(strip, g);
    circle(closest.getP1(), RADIUS, STRIP_COLOR).draw(g);
    circle(closest.getP2(), RADIUS, STRIP_COLOR).draw(g);


    return closest;
}

line dividePair(vector<circle> &circles, int begin, int end, SDL_Plotter &g, const bool fastMode) {
    // Brute force at most 3 points
    sort(circles.begin(), circles.end());
    int size = end - begin;
    int sleepTime = DIVIDE_SLEEP_TIME;
    if (fastMode) {
        sleepTime /= 10;
    }

    if(size <= 3){
        vector<circle> temp;
        for (int i = begin; i <= end; i++) {
            temp.push_back(circles[i]);
        }
        return brutePair(temp, g, fastMode);
    }

    int mid = (size / 2) + begin;
    point midpoint = circles[mid].getOrigin();

    line boundary;
    boundary.setColor(HIDDEN_COLOR);

    boundary.setP1(point(circles[mid + 1].getOrigin().getX() - RADIUS, 0));
    boundary.setP2(point(circles[mid + 1].getOrigin().getX()  - RADIUS, ROW_MAX));

    boundary.draw(g);

    for (int i = mid + 1; i <= end; i++) {
        circles[i].setColor(HIDDEN_COLOR);
    }
    drawCircles(circles, g);
    g.Sleep(sleepTime);

    line left = dividePair(circles, begin, mid, g, fastMode);

    for (int i = mid + 1; i <= end; i++) {
        circles[i].setColor(BLACK);
    }
    drawCircles(circles, g);
    circle(left.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    circle(left.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    g.update();
    g.Sleep(sleepTime);

    line right = dividePair(circles, mid + 1, end, g, fastMode);

    line closest = smallestDistance(left, right);
    right.erase(g);
    left.erase(g);

    closest.setColor(SELECTED_LINE_COLOR);
    closest.draw(g);
    drawCircles(circles, g);
    circle(closest.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    circle(closest.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    g.Sleep(sleepTime);

    double dist = closest.distance();

    boundary.erase(g);
    drawCircles(circles, g);
    // Make strip
    vector<circle> strip;
    for(int i = begin; i <= end; i++) {
        if(abs(circles[i].getOrigin().getX() - midpoint.getX()) < dist){
            strip.push_back(circles[i]);
        }
    }

    for (int i = 0; i < strip.size(); i++) {
        strip[i].setColor(STRIP_COLOR);
    }

    drawCircles(strip, g);
    circle(closest.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    circle(closest.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    g.Sleep(sleepTime);

    // Get the closest pair in the strip.
    if(strip.size() > 1) {
        line stripClosest = stripClosestPair(strip, g, fastMode);

        closest.erase(g);
        stripClosest.erase(g);

        // Compare closest pair in the strip with the previous closest.
        closest = smallestDistance(closest, stripClosest);
        closest.setColor(SELECTED_LINE_COLOR);
        closest.draw(g);
    }

    drawCircles(circles, g);
    circle(closest.getP1(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    circle(closest.getP2(), RADIUS, SELECTED_LINE_COLOR).draw(g);
    g.update();
    g.Sleep(sleepTime);

    return closest;
}

line brutePairSimple(vector<circle> &circles) {
    double closestDist = numeric_limits<double>::max();
    double dist = 0;

    circle p1, p2;

    line temp, closest;
	
	// If there are not enough points, short circuit
    if (circles.size() <= 1) {
        return line(point(-1, -1), point(-1, -1));
    }
	
	// For every point, check the distance to every point 
    for (int i = 0; i < circles.size(); i++) {

        for (int j = 0; j < circles.size(); j++) {
			// If the points are different 
            if(i != j) {
				// Make temp line
                temp.setP1(circles[i].getOrigin());
                temp.setP2(circles[j].getOrigin());
				// Get length of closest pair
                dist = temp.distance();
				// If temp line is shorter than closest pair
                if(dist < closestDist){
					// Update closest pair 
                    closestDist = dist;
                    closest.setP1(circles[i].getOrigin());
                    closest.setP2(circles[j].getOrigin());
                }
            }
        }
    }

    return closest;
}

line stripClosestPairSimple(vector<circle> &strip) {
	// If there are not enough points, short circuit
    if (strip.size() <= 1) {
        return line(point (-1, -1), point(-1, -1));
    }
	
    double min = numeric_limits<double>::max();

    sort(strip.begin(),strip.end(), compareY);

    line temp, closest;
	
	// Run the brute force algorithm on the strip of points
    for(int i = 0; i < strip.size(); i++){
        for(int j = i + 1; j < strip.size() && (strip[j].getOrigin().getY() - strip[i].getOrigin().getY()) < min; j++){
			// If the points are different
            if (i != j) {
				// Make temp line 
                temp.setP1(strip[i].getOrigin());
                temp.setP2(strip[j].getOrigin());
				// If temp line is shorter than min
                if(line(strip[i].getOrigin(), strip[j].getOrigin()).distance() < min) {
					// Line becomes new min and closest is updated
                    min = line(strip[i].getOrigin(),strip[j].getOrigin()).distance();
                    closest.setP1(strip[i].getOrigin());
                    closest.setP2(strip[j].getOrigin());
                }
            }
        }
    }

    return closest;
}

line dividePairSimple(vector<circle> &circles, int begin, int end) {
    // Brute force at most 3 points
    sort(circles.begin(), circles.end());
    int size = end - begin;

    if(size <= 3){
        vector<circle> temp;
        for (int i = begin; i <= end; i++) {
            temp.push_back(circles[i]);
        }
        return brutePairSimple(temp);
    }

    int mid = (size / 2) + begin;
    point midpoint = circles[mid].getOrigin();

	// Run divide and conquer algorithm on left half
    line left = dividePairSimple(circles, begin, mid);

	// Run divide and conquer alogrithm on right half
    line right = dividePairSimple(circles, mid + 1, end);
	
	// Get the smaller line between left and right
    line closest = smallestDistance(left, right);
	
	// Get length of closest pair
    double dist = closest.distance();

    // Make strip
    vector<circle> strip;
    for(int i = begin; i <= end; i++) {
        if(abs(circles[i].getOrigin().getX() - midpoint.getX()) < dist){
            strip.push_back(circles[i]);
        }
    }

    // Get the closest pair in the strip.
    if(strip.size() > 1) {
        line stripClosest = stripClosestPairSimple(strip);

        // Compare closest pair in the strip with the previous closest.
        closest = smallestDistance(closest, stripClosest);
    }

    return closest;
}


