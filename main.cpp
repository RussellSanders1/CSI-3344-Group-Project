#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include "point.h"
#include "SDL_Plotter.h"
using namespace std;

// A global point needed for sorting points with reference
// to the first point Used in compare function of qsort()
point p0;

// A utility function to find next to top in a stack
point nextToTop(stack<point> &S)
{
    point p = S.top();
    S.pop();
    point res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(point p1, point p2)
{
    return (p1.getX() - p2.getX())*(p1.getX() - p2.getX()) +
           (p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(point p, point q, point r)
{
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
              (q.getX() - p.getX()) * (r.getY() - q.getY());
    
    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const point &p1, const point &p2){

// Find orientation
    int o = orientation(p0, p1, p2);
    if (o == 0)
        return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1;
    
    return (o == 2)? -1: 1;
}

// Prints convex hull of a set of n points.
void convexHull(set<point> &points, int n){
    
    priority_queue<point, set<point>, decltype(compare)> queue(compare, points);
    
// Find the bottommost point
    //int ymin = queue.top().getY();

// Place the bottom-most point at first position
    //swap(points[0], points[min]);

// Sort n-1 points with respect to the first point.
// A point p1 comes before p2 in sorted ouput if p2
// has larger polar angle (in counterclockwise
// direction) than p1
    p0 = queue.top();
    //sort(++points.begin(), points.end(), compare);
    //qsort(&points[1], n-1, sizeof(point), compare);

// If two or more points make same angle with p0,
// Remove all but the one that is farthest from p0
// Remember that, in above sorting, our criteria was
// to keep the farthest point at the end when more than
// one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) i++;
        
        points[m] = points[i];
        m++; // Update size of modified array
    }

// If modified array of points has less than 3 points,
// convex hull is not possible
    if (m < 3) return;

// Create an empty stack and push first three points
// to it.
    stack<point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

// Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

// Now stack has the output points, print contents of stack
    while (!S.empty())
    {
        point p = S.top();
        cout << "(" << p.getX() << ", " << p.getY() <<")" << endl;
        S.pop();
    }
}

// Driver program to test above functions
int main(int argc, char** argv){
    SDL_Plotter g(500,1000);
    
    set<point> points = {point(0,3), point(1,1), point(2,2), point(4,4),
                            point(0,0), point(1,2), point(3,1), point(3,3)};
    int n = points.size();
    convexHull(points, n);
    return 0;
}


