/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements integers in Z_MOD.
At all points it is assumed that 0 <= x < MOD and that MOD*MOD + MOD fits unsigned long long

If you want non-const MOD, use beegmod.cpp

*** If you only want to one value of MOD, check the "mint" alias at the bottom of the code. ***
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<ull M> 
struct modint{
    ull x;

    // It is assumed -M <= v.
    constexpr modint(ll v = 0) : x(v >= M ? (v+M)%M : v){};

    bool operator==(const modint& o){
        return x == o.x;
    }

    // Example on how to implement operators if youre lazy:
    // modint operator+(modint b){
    //     return x+b.x;
    // }

    modint operator+(modint b) const{
        return min(x+b.x, x+b.x-M);
    }

    modint operator-(modint b) const{
        return min(x-b.x, x-b.x+M);
    }

    modint operator*(modint b) const {
        return x*b.x%M;
    };

    modint inverse(){
        ll x = this->x, y = M;

        complex<ll> cx = {1,0}, cy = {0,1};

        while(x){
            ll curdiv = y/x;
            y-=curdiv*x;
            cy-=curdiv*cx;
            swap(cx, cy);
            swap(x, y);
        }

        return cy.real();
    }

    modint operator/(modint b) const {
        return *this*b.inverse();
    }

    void operator+=(modint b){
        x = min(x+b.x, x+b.x-M);
    }

    void operator-=(modint b){
        x = min(x-b.x, x-b.x+M);
    }
    
    void operator*=(modint b){
        (x*=b.x)%=M;
    }

    void operator/=(modint b){
        *this = *this/b;
    }
};

using mint = modint<MOD>;