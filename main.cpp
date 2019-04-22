#include "constants.h"

using namespace std;

int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    int tempX = 0, tempY = 0;
    char input = '\0';
    vector<circle> circles;
	vector<point> hull;

	srand(time(0));

    while (!g.getQuit()) {
        drawMenu(g);
        input = '\0';

        while (!g.getQuit() && input != '1' && input != '2' && input != '3' && input != '4') {
            if (g.kbhit()) {
                input = g.getKey();
            }
        }

        clearScreen(g);

        switch(input) {
            case '3':
                while(!g.getQuit() && input != LEFT_ARROW){
                    if(g.kbhit()){
                        input = g.getKey();
                        cout << g.getKey() << endl;
                        switch(input){
                            case 'R':
                                generateRandomPoints(circles, g);
                                break;

                            case '(':
                                if (circles.size() >= 3) {
                                    hull = bruteHull(circles, g);
                                    printHull(hull);
                                }
                                break;

                            case 'E':
                                clearScreen(g);
                                circles.clear();
                                hull.clear();
                                break;

                            case RIGHT_ARROW:
                                clearScreen(g);
                                break;

                            case 'L':
                                for (int i = 0; i < 5; i++) {
                                    circles.push_back(circle(point(400 + i * 20, 400), RADIUS, color_rgb(0, 0, 0)));
                                }

                                drawCircles(circles, g);
                                break;

                            default: break;
                        }
                    }

                    else if (g.getMouseClick(tempX, tempY)) {
                        cout << "click" << endl;
                        if (tempX > RADIUS && tempY > RADIUS && tempX <= (COL_MAX - RADIUS) && tempY <= (ROW_MAX - RADIUS)) {
                            circles.push_back(circle(point(tempX, tempY), RADIUS, color_rgb(0, 0, 0)));
                            circles[circles.size() - 1].draw(g);
                        }
                    }

                    g.update();
                }
                break;

            default: break;
        }
        clearScreen(g);
    }

	return 0;
}
