#include "constants.h"

using namespace std;

int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    char input = '\0';

	srand(time(0));

    while (!g.getQuit()) {
        drawMenu(g);
        input = '\0';

        while (!g.getQuit() && input != PAIR_OPTION && input != HULL_OPTION
               && input != CONTROLS_OPTION) {
            if (g.kbhit()) {
                input = g.getKey();
            }
        }

        clearScreen(g);

        switch(input) {
            case CONTROLS_OPTION:
                drawControls(g);
                while (!g.kbhit()) {

                }
                break;

            case PAIR_OPTION:
                casePair(g, cout);
                break;

            case HULL_OPTION:
                caseHull(g, cout);
                break;

            default: break;
        }

        clearScreen(g);
    }

	return 0;
}

