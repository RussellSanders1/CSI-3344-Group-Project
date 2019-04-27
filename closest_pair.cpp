#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

struct Point{
    double x, y;
};

bool compareX(const Point &a, const Point &b){
    return a.x < b.x;
}

bool compareY(const Point &a, const Point &b){
    return a.y < b.y;
}

double distance(const Point &p1, const Point &p2){
    return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}

double distance(const pair<Point,Point> p){
    return sqrt(pow(p.second.x-p.first.x,2)+pow(p.second.y-p.first.y,2));
}

pair<Point,Point> smallestDistance(const pair<Point,Point> a, const pair<Point, Point> b){
    pair<Point,Point> closest;
    assert(&a!=&b);
    if(distance(a) <= distance(b)){
        closest = a;
    }
    else{
        closest = b;
    }
    return closest;
}

pair<Point,Point> stripClosestPair(vector<Point> strip){
    assert(strip.size() > 1);
    double min = numeric_limits<double>::max();
    sort(strip.begin(),strip.end(),compareY);
    Point a = strip[0];
    Point b = strip[strip.size()-1];
    for(int i = 0; i < strip.size(); i++){
        for(int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; j++){
            if(&strip[i] != &strip[j] && distance(strip[i],strip[j]) < min){
                min = distance(strip[i],strip[j]);
                a = strip[i];
                b = strip[j];
            }
        }
    }
    return make_pair(a,b);
}

pair<Point,Point> bruteForce(vector<Point> points,int begin,int end){
    double closestDist = INT_MAX;
    Point p1 = points[begin];
    Point p2 = points[end];
    assert(end - begin > 0);
    for(int i = begin; i < end; i++){
        for(int j = begin; j < end; j++){
            if(&points[i] != &points[j]){
                double dist = distance(points[i],points[j]);
                if(dist < closestDist){
                    closestDist = dist;
                    p1 = points[i];
                    p2 = points[j];
                }
            }
        }
    }
    return make_pair(p1,p2);
}

pair<Point,Point> divideAndConquer(vector<Point> points, int begin, int end, bool display){
    // Brute force at most 3 points
    int size = end - begin;
    if(size <= 3){
        return bruteForce(points,begin,end);
    }

    int mid = size/2 + begin;
    Point midpoint;
    midpoint.x = points[mid].x;
    midpoint.y = points[mid].y;

    pair<Point, Point> left = divideAndConquer(points,begin,mid,false);
    pair<Point, Point> right = divideAndConquer(points,mid+1,end,false);
    pair<Point, Point> closest = smallestDistance(left,right);
    double dist = distance(closest);

    // Make strip
    vector<Point> strip;
    for(int i = begin; i < end; i++){
        if(abs(points[i].x - midpoint.x) < dist){
            strip.push_back(points[i]);
        }
    }

    // Get the closest pair in the strip.
    if(strip.size() > 1){
        pair<Point,Point> stripClosest = stripClosestPair(strip);
        // Compare cloest pair in the strip with the previous closest.
        closest = smallestDistance(closest,stripClosest);
    }

    if(display){
        // Draw shortest pairs on left and right

    }


    return closest;
}


int main() {
    freopen("CPDataPoints10k.txt","r",stdin);
    int number;
    cin >> number;
    vector<Point> points;
    for(int i = 0; i < number; i++){
        Point p;
        cin >> p.x >> p.y;
        points.push_back(p);
    }

    sort(points.begin(), points.end(), compareX);
    auto it = &points[points.size()/2];

    pair<Point,Point> closestPair = bruteForce(points,0,points.size());
    Point p1 = closestPair.first;
    Point p2 = closestPair.second;
    double closestDist = sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));

    cout << "Points:" << endl;
    cout << "(" << p1.x << "," << p1.y << ")" << endl;
    cout << "(" << p2.x << "," << p2.y << ")" << endl;
    cout << "Distance: " << closestDist << endl << endl;

    closestPair = divideAndConquer(points,0,points.size(),false);
    p1 = closestPair.first;
    p2 = closestPair.second;
    closestDist = distance(closestPair);
    cout << "Points:" << endl;
    cout << "(" << p1.x << "," << p1.y << ")" << endl;
    cout << "(" << p2.x << "," << p2.y << ")" << endl;
    cout << "Distance: " << closestDist << endl;


    return 0;
}