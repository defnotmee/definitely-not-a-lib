/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"header.h"
#endif

template<typename T = ll>
struct point{
    T x, y;

    inline point operator+(point b){
        return {x+b.x, y+b.y};
    }

    inline point operator-(point b){
        return {x-b.x, y-b.y};
    }

    inline point operator*(T scale){
        return {x*scale, y*scale};
    }

    inline T cross(point b){
        return x*b.y-b.x*y;
    }

    inline T dot(point b){
        return x*b.x + y*b.y;
    }

    inline T dist2(){
        return x*x+y*y;
    }

    inline T dist(){
        return sqrt(dist2());
    }
};