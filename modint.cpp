/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements integers in Z_MOD. Assumes there is a global MOD variable for it to work.
At all points it is assumed that 0 <= x < MOD and that MOD*MOD + MOD fits long long
*/

#ifndef O_O
#include"header.h"
#include"binpow.cpp"
#endif

struct modint{
    ll x;

    // It is assumed 0 <= v. Extra mod is taken for safety, 
    // feel free to use the other constructor if you think it inpacts performance
    // (it won't)
    modint(ll v = 0) : x((v+MOD)%MOD){};

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
        int x = this->x, y = MOD;

        complex<int> cx = {1,0}, cy = {0,1};

        while(x){
            int curdiv = y/x;
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