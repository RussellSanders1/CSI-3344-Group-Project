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

#include "curve.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

color_rgb BLACK(0,0,0);

curve::curve(): sameScale(false) {}

void curve::display(Data_t data, ostream &out) {
    int b = 0;
    for(auto const &i : data){
        out << "dataset[" << b << "]:\n";
        b++;
        for(auto k : i){
            out <<  "(" << k.first << ", " << k.second << ")" << endl;
        }
        out << endl;
    }
}

void curve::draw(Data_t data, SDL_Plotter &g) {
    int margin = 10;
    int colEnd = g.getCol();
    int rowEnd = g.getRow();
    int originX = (margin * (colEnd/100));
    int originY = (margin* (rowEnd/100));
    int xEnd = colEnd - originX;
    int yEnd = rowEnd - originY;
    double scaleFactorX, scaleFactorY;
    //plot axes and ticks
    this->plotAxis(margin, colEnd, rowEnd, g);
    this->plotTickMarks(margin, colEnd, rowEnd, g);
    
    //draw curves
    vector<line> lineSet;
    line l;
    int maxX = -1;
    long double maxY = -1;
    //find the maximum data for all points
    for(auto curveData : data){
        for(auto line : curveData){
            if(line.first > maxX){
                maxX = line.first;
            }
            if(line.second > maxY){
                maxY = line.second;
            }
        }
    }
    //set scale factor for the overall graph
    scaleFactorX = (double)(xEnd - originX) / maxX;
    scaleFactorY = (double)(yEnd - originY) / maxY;
    
    //draw each curve
    for(auto curveData : data){
        //set individual scale if !sameScale
        if(!this->sameScale){
            sort(curveData.begin(), curveData.end());
            maxX = curveData[curveData.size()-1].first;
            maxY = curveData[curveData.size()-1].second;
            scaleFactorX = (double)(xEnd - originX) / maxX;
            scaleFactorY = (double)(yEnd - originY) / maxY;
        }
        for(int p = 0; p < curveData.size() - 1; ++p){
            //add the offsets to the point data
            l.setP1(point(originX + (curveData[p].first * scaleFactorX),
                          ceil(yEnd - (curveData[p].second *
                          scaleFactorY))));
            l.setP2(point(originX + (curveData[p+1].first * scaleFactorX),
                          ceil(yEnd - (curveData[p+1].second *
                          scaleFactorY))));
            lineSet.push_back(l);
        }
        //verify the lines are good
        for(auto line : lineSet){
            assert(goodPoints(line, margin, g));
            line.draw(g);
        }
        //clear vector of lines and change color
        lineSet.clear();
        l.nextColor();
    }
}

void curve::plotAxis(int margin, int maxX, int maxY, SDL_Plotter &g) {
    int minX = margin * (maxX / 100);
    int minY = margin * (maxY / 100);
    for(int x = minX; x < maxX - minX ; x++){
        g.plotPixel(x, maxY - minY, BLACK.getR(),BLACK.getG(),BLACK.getB());
    }
    for(int y = minY; y < maxY - minY; y++){
        g.plotPixel(minX, y, BLACK.getR(),BLACK.getG(),BLACK.getB());
    }
}

void curve::plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter &g) {
    int minX = margin * (maxX / 100);
    int minY = margin * (maxY / 100);
    int intervalX = (maxX - 2*minX) / 10;
    int intervalY = (maxY - 2*minY) / 10;
    int lineLengthX = minX / 10;
    int lineLengthY = minY / 10;
    
    for(int y = minY; y < maxY - minY; y+=intervalY){
        for(int x = minX-lineLengthX; x <= minX+lineLengthX; x++){
            g.plotPixel(x,y, BLACK.getR(),BLACK.getG(),BLACK.getB());
        }
    }
    
    for(int x = maxX - minX; x > minX ; x-= intervalX){
        for(int y = maxY- minY -lineLengthY; y <= maxY - minY+lineLengthY; y++){
            g.plotPixel(x,y, BLACK.getR(),BLACK.getG(),BLACK.getB());
        }
    }
    
}

bool curve::goodPoints(line a, int margin, SDL_Plotter &g){
    bool flag = true;
    int minX = (g.getCol()/ 100) * margin;
    int minY = (g.getRow()/100) * margin;
    int maxX = g.getCol();
    int maxY = g.getRow();
    if(a.getP1().getX() < minX || a.getP1().getY() < minY ||
       a.getP2().getX() < minX || a.getP2().getY() < minY ||
       a.getP1().getX() > maxX || a.getP1().getY() > maxY ||
       a.getP2().getX() > maxX || a.getP2().getY() > maxY){
        flag = false;
    }
    return flag;
}
