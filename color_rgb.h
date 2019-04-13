/*
 * Author: Russell Sanders
 * Assignment Title: Programming_Assignment_1
 * Assignment Description: This program plots data given in
 * sets on the SDL_Plotter in the form of "curves" consisting
 * of lines determined by point data in the data sets
 * Due Date: 1/28/2019
 * Date Created: 1/27/2019
 * Date Last Modified: 2/5/2019
 */

#ifndef PROJECT1_COLOR_RGB_H
#define PROJECT1_COLOR_RGB_H


class color_rgb {
public:
    /*
     * description: constructor
     * return: none
     * precondition: none
     * postcondition: color_rgb instance created
    */
    color_rgb();
    /*
     * description: custom constructor
     * return: none
     * precondition: r, g ,b valid
     * postcondition: this instance created wit values of r, g, b
    */
    color_rgb(int r, int g, int b);
    /*
     * description: virtual destructor
     * return: none
     * precondition: this instance exists
     * postcondition: this instance doesn't exist
    */
    virtual ~color_rgb() = default;

    /*
     * description: returns r from color
     * return: int
     * precondition: this instance exists
     * postcondition: r is returned by value
    */
    int getR();
    /*
     * description: returns g from color
     * return: int
     * precondition: this instance exists
     * postcondition: g is returned by value
    */
    int getG();
    /*
     * description: returns b from color
     * return: int
     * precondition: this instance exists
     * postcondition: b is returned by value
    */
    int getB();

    /*
     * description: sets this->r
     * return: void
     * precondition: r passed by value
     * postcondition: this->r contains value of r
    */
    void setR(int r);
    /*
    * description: sets this->g
    * return: void
    * precondition: g passed by value
    * postcondition: this->g contains value of g
   */
    void setG(int g);
    /*
    * description: sets this->b
    * return: void
    * precondition: b passed by value
    * postcondition: this->b contains value of b
   */
    void setB(int b);

    /*
     * description: assigns this the values in c
     * return: void
     * precondition: this instance exists, c is valid
     * postcondition: this instance contains values in c
    */
    void operator=(const color_rgb& c);

private:
    int r,g,b;
};


#endif //PROJECT1_COLOR_RGB_H

