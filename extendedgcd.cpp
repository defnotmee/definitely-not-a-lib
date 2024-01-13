/*
from https://github.com/defnotmee/definitely-not-a-lib

based on https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
*/

#ifndef O_O
#include"header.h"
#endif

auto gcd_ex(ll x, ll y){
    complex<ll> cx = {1,0}, cy = {0,1};

    while(x){
        ll curdiv = y/x;

        y-=curdiv*x;
        cy-=cx*curdiv;

        swap(cx, cy);
        swap(x,y);
    }

    struct res{ll gcd, a, b;};
    return res{y,cy.real(),cy.imag()};
}