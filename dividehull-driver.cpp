/*
#include "constants.h"

using namespace std;

// Driver code
int main(int argc, char** argv) {
	vector<circle> a;
	a.push_back(circle(point(0, 0), RADIUS, BLACK));
	a.push_back(circle(point(1, -4), RADIUS, BLACK));
	a.push_back(circle(point(-1, -5), RADIUS, BLACK));
	a.push_back(circle(point(-5, -3), RADIUS, BLACK));
	a.push_back(circle(point(-3, -1), RADIUS, BLACK));
	a.push_back(circle(point(-1, -3), RADIUS, BLACK));
	a.push_back(circle(point(-2, -2), RADIUS, BLACK));
	a.push_back(circle(point(-1, -1), RADIUS, BLACK));
	a.push_back(circle(point(-2, -1), RADIUS, BLACK));
	a.push_back(circle(point(-1, 1), RADIUS, BLACK));

	// sorting the set of points according
	// to the x-coordinate
	sort(a.begin(), a.end());
	vector<point> ans = divideHull(a);

	cout << "convex hull: " << endl;
	for (int i = 0; i < ans.size(); i++) {
        cout << "(" << ans[i].getX() << ", " << ans[i].getY() << ") ";
	}

	return 0;
}
*/


