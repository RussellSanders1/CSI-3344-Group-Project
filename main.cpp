#include "constants.h"

using namespace std;

int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    int tempX = 0, tempY = 0;
    char input = '\0';
    vector<circle> circles;
	vector<circle> hull;
	line closestPair;
	bool solutionOnScreen = false;
	string tempString;
	ifstream in;

	srand(time(0));

    while (!g.getQuit()) {
        drawMenu(g);
        solutionOnScreen = false;
        input = '\0';

        while (!g.getQuit() && input != '1' && input != '2' && input != '3' && input != '4') {
            if (g.kbhit()) {
                input = g.getKey();
            }
        }

        clearScreen(g);

        switch(input) {
            case '1':
                while(!g.getQuit() && input != LEFT_ARROW) {
                    if(g.kbhit()) {
                        input = g.getKey();
                        cout << g.getKey() << endl;
                        switch(input){
                            case 'R':
                                if (solutionOnScreen) {
                                    clearScreen(g);
                                    solutionOnScreen = false;
                                }
                                generateRandomPoints(circles, g);
                                drawCircles(circles, g);
                                break;

                            case '(':
                                if (circles.size() > 1) {
                                    if (solutionOnScreen) {
                                        clearScreen(g);
                                        drawCircles(circles, g);
                                    }
                                    closestPair = brutePair(circles, g);
                                    printPair(closestPair, cout);
                                    solutionOnScreen = true;
                                }
                                break;

                            case 'E':
                                clearScreen(g);
                                circles.clear();
                                break;

                            case RIGHT_ARROW:
                                clearScreen(g);
                                break;

                            case 'L':
                                for (int i = 0; i < 5; i++) {
                                    circles.push_back(circle(point(400, 400 + i * 20), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                break;

                            case 'I':
                                in.clear();
                                in.open(INPUT_FILE_NAME);
                                getline(in, tempString);

                                while (in >> tempX >> tempY) {
                                    circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                in.close();
                                break;

                            default: break;
                        }
                    }

                    else if (g.getMouseClick(tempX, tempY)) {
                        cout << "click" << endl;
                        if (tempX > RADIUS && tempY > RADIUS && tempX <= (COL_MAX - RADIUS) && tempY <= (ROW_MAX - RADIUS)) {
                            circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                            circles[circles.size() - 1].draw(g);
                        }
                    }

                    g.update();
                }
                break;

            case '3':
                while(!g.getQuit() && input != LEFT_ARROW){
                    if(g.kbhit()){
                        input = g.getKey();
                        cout << g.getKey() << endl;
                        switch(input){
                            case 'R':
                                if (solutionOnScreen) {
                                    clearScreen(g);
                                    solutionOnScreen = false;
                                }
                                generateRandomPoints(circles, g);
                                drawCircles(circles, g);
                                break;

                            case '(':
                                if (circles.size() >= 3) {
                                    if (solutionOnScreen) {
                                        clearScreen(g);
                                        drawCircles(circles, g);
                                    }
                                    hull = bruteHull(circles, g);
                                    printHull(hull, cout);
                                    solutionOnScreen = true;
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
                                    circles.push_back(circle(point(400 + i * 20, 400), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                break;

                            case 'I':
                                in.clear();
                                in.open(INPUT_FILE_NAME);
                                getline(in, tempString);

                                while (in >> tempX >> tempY) {
                                    circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                in.close();
                                break;

                            default: break;
                        }
                    }

                    else if (g.getMouseClick(tempX, tempY)) {
                        cout << "click" << endl;
                        if (tempX > RADIUS && tempY > RADIUS && tempX <= (COL_MAX - RADIUS) && tempY <= (ROW_MAX - RADIUS)) {
                            circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                            circles[circles.size() - 1].draw(g);
                            eliminateDuplicates(circles);
                        }
                    }

                    g.update();
                }
                break;

            case '4':
                while (!g.getQuit() && input != LEFT_ARROW) {
                    if(g.kbhit()){
                        input = g.getKey();
                        cout << g.getKey() << endl;
                        switch(input){
                            case 'R':
                                if (solutionOnScreen) {
                                    clearScreen(g);
                                    solutionOnScreen = false;
                                }
                                generateRandomPoints(circles, g);
                                drawCircles(circles, g);
                                break;

                            case '(':
                                if (circles.size() >= 3) {
                                    if (solutionOnScreen) {
                                        clearScreen(g);
                                        drawCircles(circles, g);
                                    }
                                    hull = divideHull(circles, g);
                                    printHull(hull, cout);
                                    solutionOnScreen = true;
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
                                for (int i = 0; i < 10; i++) {
                                    circles.push_back(circle(point(400 + i * 20, 400), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                break;

                            case 'I':
                                in.clear();
                                in.open(INPUT_FILE_NAME);
                                getline(in, tempString);

                                while (in >> tempX >> tempY) {
                                    circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                                }

                                drawCircles(circles, g);
                                in.close();
                                break;

                            default: break;
                        }
                    }

                    else if (g.getMouseClick(tempX, tempY)) {
                        cout << "click" << endl;
                        if (tempX > RADIUS && tempY > RADIUS && tempX <= (COL_MAX - RADIUS) && tempY <= (ROW_MAX - RADIUS)) {
                            circles.push_back(circle(point(tempX, tempY), RADIUS, BLACK));
                            circles[circles.size() - 1].draw(g);
                        }
                    }

                    g.update();
                }
                break;

            default: break;
        }

        clearScreen(g);
        circles.clear();
        hull.clear();
    }

	return 0;
}
