#include "constants.h"

using namespace std;

int main(int argc, char** argv) {
    SDL_Plotter g(ROW_MAX, COL_MAX);
    char input = '\0';

	srand(time(0));

    while (!g.getQuit()) {
        drawMenu(g);
        input = '\0';

        while (!g.getQuit() && input != BRUTEPAIR_OPTION
               && input != DIVIDEPAIR_OPTION && input != BRUTEHULL_OPTION
               && input != DIVIDEHULL_OPTION) {
            if (g.kbhit()) {
                input = g.getKey();
            }
        }

        clearScreen(g);

        switch(input) {
            case BRUTEPAIR_OPTION:
                caseBrutePair(g);
                break;

            case BRUTEHULL_OPTION:
                caseBruteHull(g);
                break;

            case DIVIDEHULL_OPTION:
                caseDivideHull(g);
                break;

            default: break;
        }

        clearScreen(g);
    }

	return 0;
}
