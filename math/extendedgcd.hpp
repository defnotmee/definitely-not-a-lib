/*
from https://github.com/defnotmee/definitely-not-a-lib

based on https://cp-algorithms.com/algebra/extended-euclid-algorithm.html

Given 2 numbers x, y, returns {gcd(x,y), alpha, beta} such that alpha*x + beta*y = gcd(x,y)
*/

#ifndef O_O
#include"template.cpp"
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

    struct res{ll gcd, alpha, beta;};
    return res{y,cy.real(),cy.imag()};
}