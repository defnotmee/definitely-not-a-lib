/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements integers in Z_MOD. Assumes there is a global MOD variable for it to work.
At all points it is assumed that 0 <= x < MOD and that MOD*MOD + MOD fits usigned long long

If you only want to one value of MOD, check the "mint" alias at the bottom of the code.
*/

#ifndef O_O
#include"header.h"
#include"binpow.cpp"
#endif

// in case the modulo is not constant (given on input), use this instead
// to instead use whatever is in the global variable MOD:
// template<ull _M>
template<ull MOD>
struct modint{
    ull x;

    // It is assumed -MOD <= v. Extra mod is taken for safety.
    // You can just call this if you're lazy instead of doing somethhing
    // for every operator (for example, modint(x+b.x))
    constexpr modint(ll v = 0) : x((v+MOD)%MOD){};

    modint(ll v, ll raw) : x(v){};

    // only on C++20
    bool operator<=>(const modint&) const = default;

    modint operator+(modint b){
        return modint(x+b.x - MOD*(x+b.x >= MOD),1);
    }

    modint operator-(modint b){
        return modint(x-b.x + MOD*(x-b.x < 0),1);
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
        x+=b.x;
        x-=MOD*(x>=MOD);
    }

    void operator-=(modint b){
        x-=b.x;
        x+=MOD*(x<0);
    }
    
    void operator*=(modint b){
        (x*=b.x)%=MOD;
    }

    void operator/=(modint b){
        *this = *this/b;
    }
};

using mint = modint<MOD>;