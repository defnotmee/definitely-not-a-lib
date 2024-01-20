/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements integers in Z_MOD. Assumes there is a global MOD variable for it to work.
At all points it is assumed that 0 <= x < MOD and that MOD*MOD + MOD fits unsigned long long

If you only want to one value of MOD, check the "mint" alias at the bottom of the code.
*/

#ifndef O_O
#include"header.h"
#endif

template<ull M> // comment if non-const MOD
struct modint{
    static const ull MOD = M; // comment if non-const MOD
    ull x;

    // It is assumed -MOD <= v. Extra mod is taken for safety.
    // You can just call this if you're lazy when implementing operators
    // you can just return modint(x+b.x) for example.
    constexpr modint(ll v = 0) : x((v+MOD)%MOD){};

    constexpr modint(ll v, ll raw) : x(v){};

    // only on C++20
    bool operator<=>(const modint&) const = default;

    modint operator+(modint b){
        return modint(min(x+b.x, x+b.x-MOD),1);
    }

    modint operator-(modint b){
        return modint(min(x-b.x, x-b.x+MOD),1);
    }

    modint operator*(modint b){
        return modint((x*b.x%MOD),1);
    };

    modint inverse(){
        ll x = this->x, y = MOD;

        complex<ll> cx = {1,0}, cy = {0,1};

        while(x){
            ll curdiv = y/x;
            y-=curdiv*x;
            cy-=curdiv*cx;
            swap(cx, cy);
            swap(x, y);
        }

        return modint(cy.real());
    }

    modint operator/(modint b){
        return *this*b.inverse();
    }

    void operator+=(modint b){
        x = min(x+b.x, x+b.x-MOD);
    }

    void operator-=(modint b){
        x = min(x-b.x, x-b.x+MOD);
    }
    
    void operator*=(modint b){
        (x*=b.x)%=MOD;
    }

    void operator/=(modint b){
        *this = *this/b;
    }
};

using mint = modint<MOD>; // comment if non const MOD