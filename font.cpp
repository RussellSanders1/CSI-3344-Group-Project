#include "font.h"

font::font() {
    string fileName;
    ifstream input;
    int row, col;

    //loop used to copy all text files to the alphabet array
    for (int a = 0; a < NUM_FONT; a++) {
        //turns a into the string that corresponds to the letter represented by the array at index a
        //and starts the filename
        fileName = getFontString(a);
        //adds .txt to the string just created in order to make it a file name
        fileName += ".txt";

        //resets the input stream
        input.clear();
        //opens the file
        input.open(fileName.c_str());

        //takes the dimensions of the letter
        input >> row >> col;

        //inputs the letter file into the array
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                input >> alphabet[a][r][c];
            }
        }

        //closes the file
        input.close();
    }

    //closes the file
    input.close();
}

string font::getFontString(int a) {
    //translates the int passed into the character that int represents in the alphabet array
    //returns a string to make it easier to create a file name
    string s;
    switch (a) {
        case 0: s = "A";
                break;

        case 1: s = "B";
                break;

        case 2: s = "C";
                break;

        case 3: s = "D";
                break;

        case 4: s = "E";
                break;

        case 5: s = "F";
                break;

        case 6: s = "G";
                break;

        case 7: s = "H";
                break;

        case 8: s = "I";
                break;

        case 9: s = "J";
                break;

        case 10: s = "K";
                 break;

        case 11: s = "L";
                 break;

        case 12: s = "M";
                 break;

        case 13: s = "N";
                 break;

        case 14: s = "O";
                 break;

        case 15: s = "P";
                 break;

        case 16: s = "Q";
                 break;

        case 17: s = "R";
                 break;

        case 18: s = "S";
                 break;

        case 19: s = "T";
                 break;

        case 20: s = "U";
                 break;

        case 21: s = "V";
                 break;

        case 22: s = "W";
                 break;

        case 23: s = "X";
                 break;

        case 24: s = "Y";
                 break;

        case 25: s = "Z";
                 break;

        case 26: s = "0";
                 break;

        case 27: s = "1";
                 break;

        case 28: s = "2";
                 break;

        case 29: s = "3";
                 break;

        case 30: s = "4";
                 break;

        case 31: s = "5";
                 break;

        case 32: s = "6";
                 break;

        case 33: s = "7";
                 break;

        case 34: s = "8";
                 break;

        case 35: s = "9";
                 break;

        case 36: s = "colon";
                 break;

        case 37: s = "!";
                 break;

        case 38: s = "space";
                 break;
    }

    return s;
}

int font::getFontNum(char c) {
    //turns the char passed into the int that char represents in the alphabet array
    int s;

    switch (c) {
        case 'A': s = 0;
                  break;

        case 'B': s = 1;
                  break;

        case 'C': s = 2;
                break;

        case 'D': s = 3;
                break;

        case 'E': s = 4;
                break;

        case 'F': s = 5;
                break;

        case 'G': s = 6;
                break;

        case 'H': s = 7;
                break;

        case 'I': s = 8;
                break;

        case 'J': s = 9;;
                break;

        case 'K': s = 10;
                 break;

        case 'L': s = 11;
                 break;

        case 'M': s = 12;
                 break;

        case 'N': s = 13;
                 break;

        case 'O': s = 14;
                 break;

        case 'P': s = 15;
                 break;

        case 'Q': s = 16;
                 break;

        case 'R': s = 17;
                 break;

        case 'S': s = 18;
                 break;

        case 'T': s = 19;
                 break;

        case 'U': s = 20;
                 break;

        case 'V': s = 21;
                 break;

        case 'W': s = 22;
                 break;

        case 'X': s = 23;
                 break;

        case 'Y': s = 24;
                 break;

        case 'Z': s = 25;
                 break;

        case '0': s = 26;
                 break;

        case '1': s = 27;
                 break;

        case '2': s = 28;
                 break;

        case '3': s = 29;
                 break;

        case '4': s = 30;
                 break;

        case '5': s = 31;
                 break;

        case '6': s = 32;
                 break;

        case '7': s = 33;
                 break;

        case '8': s = 34;
                 break;

        case '9': s = 35;
                 break;

        case ':': s = 36;
                 break;

        case '!': s = 37;
                 break;

        case ' ': s = 38;
                  break;
    }

    return s;
}

void font::plotChar(point &p, int scale, char c, SDL_Plotter &g, color_rgb color) {
    int a;

    //translates the passed char into the index of the alphabet array that contains that char
    a = getFontNum(c);

    //plots the char
    for (int y = 0; y < MAX_ROW_LETTER; y++) {
        for (int x = 0; x < MAX_COLUMN_LETTER; x++) {
            //print a square based on scale
            for (int row = 0; row < scale; row++) {
                for (int col = 0; col < scale; col++) {
                    if (alphabet[a][y][x] == '1') {
                        g.plotPixel(p.getX() + x * scale + col, p.getY() + y * scale + row, color.getR(), color.getG(), color.getB());
                    }
                }
            }
        }
    }

    //moves the point over so the letters do not overlap
    p.setX(p.getX() + (MAX_COLUMN_LETTER + 1) * scale);

    return;
}

void font::plotString(point currentPosition, int scale, string message, color_rgb color, SDL_Plotter &g) {
    char currentLetter;

    //loops through the whole string passed, plotting each char
    for (int i = 0; i < message.length(); i++) {
        //gets the char at index i of the passed string
        currentLetter = message[i];

        //calls the plotChar function to plot it
        plotChar(currentPosition, scale, currentLetter, g, color);
    }

    return;
}

void font::eraseString(point currentPosition, int scale, string message, SDL_Plotter &g) {
    char currentLetter;

    color_rgb color(0, 0, 0);

    //draws over the string with given scale and starting position in black
    //loops through the string getting each char
    for (int i = 0; i < message.length(); i++) {
        currentLetter = message[i];

        plotChar(currentPosition, scale, currentLetter, g, color);
    }

    return;
}

