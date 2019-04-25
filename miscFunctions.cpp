#include "miscFunctions.h"

void clearScreen(SDL_Plotter &g) {
    for (int r = 0; r < ROW_MAX; r++) {
        for (int c = 0; c < COL_MAX; c++) {
            g.plotPixel(r, c, 255, 255, 255);
        }
    }

    return;
}


void drawCircles(vector<circle> &circles, SDL_Plotter &g) {
    for (int i = 0; i < circles.size(); i++) {
        circles[i].draw(g);
    }

    g.update();

    return;
}

void drawMenu(SDL_Plotter &g) {
    font f;

    f.plotString(point(200, 150), 4, "CSI 3344", BLACK, g);
    f.plotString(point(100, 200), 4, "GROUP PROJECT", BLACK, g);

    f.plotString(point(100, 400), 1, "PRESS 1 FOR BRUTE FORCE CLOSEST PAIR", BLACK, g);
    f.plotString(point(100, 450), 1, "PRESS 2 FOR DIVIDE AND CONQUER CLOSEST PAIR", BLACK, g);
    f.plotString(point(100, 500), 1, "PRESS 3 FOR BRUTE FORCE CONVEX HULL", BLACK, g);
    f.plotString(point(100, 550), 1, "PRESS 4 FOR DIVIDE AND CONQUER CONVEX HULL", BLACK, g);
    g.update();

    return;
}

void generateRandomPoints(vector<circle> &circles, SDL_Plotter &g) {
    for (int i = 0; i < MIN_POINTS + rand() % (MAX_POINTS + 1 - MIN_POINTS); i++) {
        circles.push_back(circle(point((RADIUS + rand() % ((COL_MAX - RADIUS) + 1 - RADIUS)),
                                       (RADIUS + rand() % ((ROW_MAX - RADIUS) + 1 - RADIUS))),
                                 RADIUS, color_rgb(0, 0, 0)));
    }

    eliminateDuplicates(circles);

    return;
}

void printHull(vector<circle> &hull, ostream &out) {
	if (hull.size() >= 3) {
        out << "The points in Convex Hull are: " << endl;
        for (int i = 0; i < hull.size(); i++) {
            out << "(" << hull[i].getOrigin().getX() << ", " << hull[i].getOrigin().getY() << ") ";
        }
	}

	out << endl;

	return;
}


void printPair(line a, ostream &out) {
    if (a.getP1() == a.getP2()) {
        return;
    }
    out << "Closest pair: (" << a.getP1().getX() << ", " << a.getP1().getY();
    out << ") (" << a.getP2().getX() << ", " << a.getP2().getY() << ")" << endl;
}

bool isStraightLine(vector<circle> &circles) {
    bool isStraight = true;
    sort(circles.begin(), circles.end());
    line temp(circles[0].getOrigin(), circles[circles.size() - 1].getOrigin());

    for (int i = 1; i < circles.size() - 1 && isStraight; i++) {
        if (!temp.intersects(circles[i].getOrigin())) {
            isStraight = false;
        }
    }

    return isStraight;
}

void eliminateDuplicates(vector<circle> &circles) {
    set<circle> s;

    for (int i = 0; i < circles.size(); i++) {
        s.insert(circles[i]);
    }

    circles.clear();

    for (auto i: s) {
        circles.push_back(i);
    }

    return;
}

void caseBrutePair(SDL_Plotter &g) {
    char input = '\0';
    vector<circle> circles;
    bool solutionOnScreen = false;
    line closestPair;
    int x = 0, y = 0;

    while(!g.getQuit() && input != LEFT_ARROW) {
        if(g.kbhit()) {
            input = g.getKey();
            cout << g.getKey() << endl;
            switch(input){
                case RANDOM_OPTION:
                    caseRandom(solutionOnScreen, circles, g);
                    break;

                case START_OPTION:
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

                case ERASE_OPTION:
                    clearScreen(g);
                    circles.clear();
                    break;

                case BACK_OPTION:
                    clearScreen(g);
                    break;

                case 'L':
                    for (int i = 0; i < 5; i++) {
                        circles.push_back(circle(point(400, 400 + i * 20), RADIUS, BLACK));
                    }

                    drawCircles(circles, g);
                    break;

                case IMPORT_OPTION:
                    caseImport(circles, g);
                    break;

                default: break;
            }
        }

        else if (g.getMouseClick(x, y)) {
            cout << "click" << endl;
            storeMouseClick(x, y, circles, g);
        }

        g.update();
    }

    return;
}

void caseBruteHull(SDL_Plotter &g) {
    char input = '\0';
    vector<circle> circles;
    bool solutionOnScreen = false;
    vector<circle> hull;
    int x = 0, y = 0;

    while(!g.getQuit() && input != LEFT_ARROW){
        if(g.kbhit()){
            input = g.getKey();
            cout << g.getKey() << endl;
            switch(input){
                case RANDOM_OPTION:
                    caseRandom(solutionOnScreen, circles, g);
                    break;

                case START_OPTION:
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

                case ERASE_OPTION:
                    clearScreen(g);
                    circles.clear();
                    hull.clear();
                    break;

                case BACK_OPTION:
                    clearScreen(g);
                    break;

                case 'L':
                    for (int i = 0; i < 5; i++) {
                        circles.push_back(circle(point(400 + i * 20, 400), RADIUS, BLACK));
                    }

                    drawCircles(circles, g);
                    break;

                case IMPORT_OPTION:
                    caseImport(circles, g);
                    break;

                default: break;
            }
        }

        else if (g.getMouseClick(x, y)) {
            cout << "click" << endl;
            storeMouseClick(x, y, circles, g);
        }

        g.update();
    }

    return;
}

void caseDivideHull(SDL_Plotter &g) {
    char input = '\0';
    vector<circle> circles;
    bool solutionOnScreen = false;
    vector<circle> hull;
    int x = 0, y = 0;

    while (!g.getQuit() && input != LEFT_ARROW) {
        if(g.kbhit()){
            input = g.getKey();
            cout << g.getKey() << endl;
            switch(input){
                case RANDOM_OPTION:
                    caseRandom(solutionOnScreen, circles, g);
                    break;

                case START_OPTION:
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

                case ERASE_OPTION:
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

                case IMPORT_OPTION:
                    caseImport(circles, g);
                    break;

                default: break;
            }
        }

        else if (g.getMouseClick(x, y)) {
            cout << "click" << endl;
            storeMouseClick(x, y, circles, g);
        }

        g.update();
    }

}

void caseRandom(bool &solutionOnScreen, vector<circle> &circles, SDL_Plotter &g) {
    if (solutionOnScreen) {
        clearScreen(g);
        solutionOnScreen = false;
    }
    generateRandomPoints(circles, g);
    drawCircles(circles, g);

    return;
}

void caseImport(vector<circle> &circles, SDL_Plotter &g) {
    ifstream in;
    string tempString;
    int x = 0, y = 0;

    in.open(INPUT_FILE_NAME);
    getline(in, tempString);

    while (in >> x >> y) {
        circles.push_back(circle(point(x, y), RADIUS, BLACK));
    }
    eliminateDuplicates(circles);
    drawCircles(circles, g);
    in.close();

    return;
}

void storeMouseClick(int x, int y, vector<circle> &circles, SDL_Plotter &g) {
    if (x > RADIUS && y > RADIUS && x <= (COL_MAX - RADIUS) && y <= (ROW_MAX - RADIUS)) {
        circles.push_back(circle(point(x, y), RADIUS, BLACK));
        eliminateDuplicates(circles);
        circles[circles.size() - 1].draw(g);
    }

    return;
}
