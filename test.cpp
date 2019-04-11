
#include "curve.h"
#include <iostream>
#include <cmath>

using namespace std;

const int ROW_MAX = 500;
const int COL_MAX = 1000;

int main(int argc, char ** argv){
    SDL_Plotter g(ROW_MAX,COL_MAX);
    point p(50,50);
    curve c;
    color_rgb color;
    char key;
    Data_t d;
    
    DataSet_t set1;
    set1.push_back(make_pair(0,0));
    set1.push_back(make_pair(1,10));
    set1.push_back(make_pair(2,20));
    set1.push_back(make_pair(3,40));
    set1.push_back(make_pair(4,80));
    set1.push_back(make_pair(5,160));
    set1.push_back(make_pair(6,320));
    set1.push_back(make_pair(7,640));
    set1.push_back(make_pair(8,1280));
    set1.push_back(make_pair(9,2560));
    set1.push_back(make_pair(10,5120));
    d.push_back(set1);
    
    DataSet_t set2;
    for(int i = 0; i < 10000; i++){
        set2.push_back(make_pair(i,i));
    }
    d.push_back(set2);
    
    DataSet_t set3;
    for(int i = 0; i < 10000; i++){
        set3.push_back(make_pair(i,(i*i)));
    }
    d.push_back(set3);
    
    DataSet_t set4;
    for(int i = 0; i < 1000; i++){
        set4.push_back(make_pair(i,(static_cast<long double>(i)*i*i)));
    }
    d.push_back(set4);
    
    DataSet_t set5;
    for(int i = 1; i < 10000000; i+=1000){
        set5.push_back(make_pair(i,log(i)));
    }
    d.push_back(set5);
    
    c.setSameScale(true);
    c.draw(d,g);
    while(!g.getQuit()){
        if(g.kbhit()){
            switch(g.getKey()){
                case 'S':
                    c.setSameScale(!c.getSameScale());
                    g.clear();
                    c.draw(d,g);
                    break;
            }
        }
        g.update();
    }
    
    return 0;
}