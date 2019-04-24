#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
using namespace std;

struct Point{
    double x, y;
};

bool compare(const Point &a, const Point &b){
    return a.x < b.x;
}

double distance(const Point &p1, const Point &p2){
    return sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2));
}

double distance(const pair<Point,Point> p){
    return sqrt(pow(p.second.x-p.first.x,2)+pow(p.second.y-p.first.y,2));
}

pair<Point,Point> smallestDistance(const pair<Point,Point> a, const pair<Point, Point> b){
    pair<Point,Point> closest;
    if(distance(a) <= distance(b)){
        closest = a;
    }
    else{
        closest = b;
    }
    return closest;
}


pair<Point,Point> bruteForce(vector<Point> points){
    double closestDist = INT_MAX;
    Point p1,p2;
    for(int i = 0; i < points.size(); i++){
        for(int j = 0; j <points.size(); j++){
            if(&points[i] != &points[j]){
                double dist = sqrt(pow(points[j].x-points[i].x,2)+pow(points[j].y-points[i].y,2));
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
        return bruteForce(points);
    }

    int mid = size/2;
    Point midpoint;
    midpoint.x = points[mid].x;
    midpoint.y = points[mid].y;

    pair<Point, Point> left = divideAndConquer(points,begin,mid,false);
    pair<Point, Point> right = divideAndConquer(points,mid + 1,end,false);
    double dist = min(distance(left),distance(right));
    if(display){
        // Draw shortest pairs on left and right
    }




}





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