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

    // It is assumed 0 <= v. Extra mod is taken for safety, 
    // feel free to comment if you think it will inpact runtime
    // (it won't)
    modint(ll v = 0){ 
        x = v%MOD;
    }

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
};