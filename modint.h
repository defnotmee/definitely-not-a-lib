/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements integers in Z_MOD. Assumes there is a global MOD variable for it to work.
At all points it is assumed that 0 <= x < MOD and that MOD*MOD + MOD fits long long
*/

#ifndef O_O
#include"header.h"
#endif

struct modint{
    ll x;

    // only on C++20
    bool operator<=>(const modint&) const = default;

    modint operator+(modint b){
        return {(x+b.x)%MOD};
    }

    modint operator-(modint b){
        return {(x-b.x+MOD)%MOD};
    }

    modint operator*(modint b){
        return {(x*b.x%MOD)};
    };

    void operator+=(modint b){
        (x+=b.x)%=MOD;
    }

    void operator-=(modint b){
        (x-=b.x-MOD)%=MOD;
    }
    
    void operator*=(modint b){
        (x*=b.x)%=MOD;
    }

    modint(ll v = 0){ // it is assumed 0 <= v < MOD
        x = v;
    }
};