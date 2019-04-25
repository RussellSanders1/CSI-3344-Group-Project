#include "pairFunctions.h"

line smallestDistance(line a, line b){
    line closest;
    if(a.distance() <= b.distance()){
        closest = a;
    }
    else{
        closest = b;
    }
    return closest;
}


line brutePair(vector<circle> &circles, SDL_Plotter &g){
    double closestDist = INT_MAX;
    double dist = 0;
    circle p1, p2;

    line temp, closest;
    closest.setColor(HULL_LINE_COLOR);
    temp.setColor(TEMP_LINE_COLOR);

    if (circles.size() <= 1) {
        return line(point(0, 0), point(0, 0));
    }

    for (int i = 0; i < circles.size(); i++) {
        circles[i].setColor(SECOND_SELECTED_POINT_COLOR);
        circles[i].draw(g);
        g.update();
        g.Sleep(SLEEP_TIME);

        for (int j = 0; j < circles.size(); j++) {
            if(i != j) {
                circles[j].setColor(SECOND_SELECTED_POINT_COLOR);
                circles[j].draw(g);
                g.Sleep(SLEEP_TIME);

                temp.setP1(circles[i].getOrigin());
                temp.setP2(circles[j].getOrigin());
                temp.draw(g);
                g.update();
                g.Sleep(SLEEP_TIME);

                dist = temp.distance();

                if(dist < closestDist){
                    closestDist = dist;
                    closest.erase(g);
                    closest.setP1(circles[i].getOrigin());
                    closest.setP2(circles[j].getOrigin());
                    closest.draw(g);
                    g.update();
                    g.Sleep(SLEEP_TIME);

                    p1 = circles[i];
                    p2 = circles[j];
                    p1.setColor(FIRST_SELECTED_POINT_COLOR);
                    p2.setColor(FIRST_SELECTED_POINT_COLOR);
                }

                temp.erase(g);
                closest.draw(g);

                circles[j].setColor(BLACK);
                drawCircles(circles, g);
                p1.draw(g);
                p2.draw(g);
                g.update();
            }
        }

        circles[i].setColor(BLACK);
        circles[i].draw(g);
    }

    return line(p1.getOrigin(), p2.getOrigin());
}

/*
line dividePair(vector<circle> &circles, int first, int last){
    // Brute force at most 3 points
    int size = last - first;
    if(size <= 3){
        return brutePair(circles);
    }

    int mid = size / 2;
    point midPoint(circles[mid].getOrigin().getX(), circles[mid].getOrigin().getY());

    line left = dividePair(points, first, mid);
    line right = dividePair(points, mid + 1, last);
    double dist = min(left.distance(), right.distance());

    if(display){
        // Draw shortest pairs on left and right
    }




}
*/




/*
int main() {
    freopen("DataPoints1k.txt","r",stdin);
    int number;
    cin >> number;
    vector<Point> points;
    for(int i = 0; i < number; i++){
        Point p;
        cin >> p.x >> p.y;
        points.push_back(p);
    }

    sort(points.begin(),points.end(),compare);
    auto it = &points[points.size()/2];


    /*
    for(auto it = points.begin(); it != points.end(); it++){
        cout << "(" << it->x << "," << it->y << ")" << endl;
    }
    */
    /*
    pair<Point,Point> closestPair = bruteForce(points);
    Point p1 = closestPair.first;
    Point p2 = closestPair.second;
    double closestDist = sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));

    cout << "Points:" << endl;
    cout << "(" << p1.x << "," << p1.y << ")" << endl;
    cout << "(" << p2.x << "," << p2.y << ")" << endl;
    cout << "Distance: " << closestDist << endl;

    return 0;
}
*/
