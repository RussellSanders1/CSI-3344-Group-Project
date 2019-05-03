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
    f.plotString(point(75, 200), 4, "GROUP PROJECT", BLACK, g);

    f.plotString(point(100, 400), 2, "PRESS 1 FOR CLOSEST PAIR", BLACK, g);
    f.plotString(point(100, 450), 2, "PRESS 2 FOR CONVEX HULL", BLACK, g);
    f.plotString(point(100, 500), 2, "PRESS C FOR CONTROLS", BLACK, g);
    g.update();

    return;
}

void drawControls(SDL_Plotter &g) {
    font f;

    f.plotString(point(250, 150), 3, "CONTROLS", BLACK, g);
    f.plotString(point(100, 250), 1, "PRESS R TO GENERATE RANDOM POINTS", BLACK, g);
    f.plotString(point(100, 280), 1, "PRESS E TO ERASE THE SCREEN", BLACK, g);
    f.plotString(point (100, 310), 1, "PRESS B FOR TO RUN A BRUTE FORCE SOLUTION", BLACK, g);
    f.plotString(point (100, 340), 1, "PRESS D FOR TO RUN A DIVIDE AND CONQUER SOLUTION", BLACK, g);
    f.plotString(point (100, 370), 1, "PRESS I TO IMPORT POINTS FROM THE DATA FILE", BLACK, g);
    f.plotString(point (100, 400), 1, "PRESS S TO SET NORMAL SPEED", BLACK, g);
    f.plotString(point (100, 430), 1, "PRESS F TO SET FAST MODE!", BLACK, g);
    f.plotString(point (100, 460), 1, "PRESS THE LEFT ARROW TO GO BACK A SCREEN", BLACK, g);
    f.plotString(point (100, 490), 1, "CLICK ANYWHERE IN A SOLUTION TO PLOT A POINT!", BLACK, g);
    f.plotString(point (100, 520), 1, "PRESS A TO TOGGLE ANIMATION", BLACK, g);
    f.plotString(point (80, 580), 2, "PRESS ANY KEY TO CONTINUE", BLACK, g);

    g.update();
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
	else {
        out << "Convex Hull not possible.";
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

    out << "Distance: " << a.distance() << endl;

    return;
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

void casePair(SDL_Plotter &g, ostream &out) {
    char input = '\0';
    vector<circle> circles;
    bool fastMode = false;
    bool solutionOnScreen = false;
    bool animationMode = true;
    line closestPair;
    int x = 0, y = 0;

    while(!g.getQuit() && input != BACK_OPTION) {
        if(g.kbhit()) {
            input = g.getKey();
            switch(input){
                case RANDOM_OPTION:
                    caseRandom(solutionOnScreen, circles, g);
                    out << "Generating random points..." << endl;
                    break;

                case DIVIDE_OPTION:
                    if (circles.size() > 1) {
                        if (solutionOnScreen) {
                            clearScreen(g);
                            drawCircles(circles, g);
                        }
                        if (animationMode) {
                            closestPair = dividePair(circles, 0, circles.size() - 1, g, fastMode);
                        }
                        else {
                            closestPair = dividePairSimple(circles, 0, circles.size() - 1);
                        }
                        printPair(closestPair, cout);
                        solutionOnScreen = true;
                    }
                    break;

                case BRUTE_OPTION:
                    if (circles.size() > 1) {
                        if (solutionOnScreen) {
                            clearScreen(g);
                            drawCircles(circles, g);
                        }
                        if (animationMode) {
                            closestPair = brutePair(circles, g, fastMode);
                        }
                        else {
                            closestPair = brutePairSimple(circles);
                        }
                        printPair(closestPair, cout);
                        solutionOnScreen = true;
                    }
                    break;


                case ERASE_OPTION:
                    clearScreen(g);
                    circles.clear();
                    out << "Clearing the screen..." << endl;
                    break;

                case BACK_OPTION:
                    clearScreen(g);
                    break;

                case IMPORT_OPTION:
                    caseImport(circles, g);
                    out << "Importing points from 'points.txt'..." << endl;
                    break;

                case FAST_OPTION:
                    fastMode = true;
                    out << "Fast mode set!" << endl;
                    break;

                case SLOW_OPTION:
                    fastMode = false;
                    out << "Normal speed set!" << endl;
                    break;

                case ANIMATION_OPTION:
                    if (animationMode) {
                        cout << "Disabling animation." << endl;
                        animationMode = false;
                    }
                    else {
                        cout << "Enabling animation mode." << endl;
                        animationMode = true;
                    }
                    break;


                default: break;
            }
        }

        else if (g.getMouseClick(x, y)) {
            storeMouseClick(x, y, circles, g);
        }

        g.update();
    }

    return;
}


void caseHull(SDL_Plotter &g, ostream &out) {
    char input = '\0';
    vector<circle> circles;
    bool solutionOnScreen = false;
    bool fastMode = false;
    bool animationMode = true;
    vector<circle> hull;
    int x = 0, y = 0;

    while(!g.getQuit() && input != BACK_OPTION){
        if(g.kbhit()){
            input = g.getKey();
            switch(input){
                case RANDOM_OPTION:
                    caseRandom(solutionOnScreen, circles, g);
                    out << "Generating random points..." << endl;
                    break;

                case BRUTE_OPTION:
                    if (circles.size() >= 3) {
                        if (solutionOnScreen) {
                            clearScreen(g);
                            drawCircles(circles, g);
                        }
                        if (animationMode) {
                            hull = bruteHull(circles, g, fastMode);
                        }
                        else {
                            hull = bruteHullSimple(circles);
                        }
                        printHull(hull, cout);
                        solutionOnScreen = true;
                    }
                    break;

                case DIVIDE_OPTION:
                    if (circles.size() >= 3) {
                        if (solutionOnScreen) {
                            clearScreen(g);
                            drawCircles(circles, g);
                        }
                        if (animationMode) {
                            hull = divideHull(circles, g, fastMode);
                        }
                        else {
                            hull = divideHullSimple(circles);
                        }
                        printHull(hull, cout);
                        solutionOnScreen = true;
                    }
                    break;

                case ERASE_OPTION:
                    clearScreen(g);
                    circles.clear();
                    hull.clear();
                    out << "Clearing the screen..." << endl;
                    break;

                case BACK_OPTION:
                    clearScreen(g);
                    break;

                case IMPORT_OPTION:
                    caseImport(circles, g);
                    out << "Importing points from 'points.txt'..." << endl;
                    break;

                case FAST_OPTION:
                    fastMode = true;
                    out << "Fast mode set!" << endl;
                    break;

                case SLOW_OPTION:
                    fastMode = false;
                    out << "Normal speed set!" << endl;
                    break;

                case ANIMATION_OPTION:
                    if (animationMode) {
                        cout << "Disabling animation." << endl;
                        animationMode = false;
                    }
                    else {
                        cout << "Enabling animation mode." << endl;
                        animationMode = true;
                    }
                    break;

                default: break;
            }
        }

        else if (g.getMouseClick(x, y)) {
            storeMouseClick(x, y, circles, g);
        }

        g.update();
    }

    return;
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
        drawCircles(circles, g);
    }

    return;
}
