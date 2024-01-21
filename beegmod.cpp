/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements modulo operations for big MOD. Important for
number theory stuff.
*/

#ifndef O_O
#include"header.h"
#endif

inline ull modadd(ull a, ull b, ull m){
    return min(a+b,a+b-m);
}

inline ull modsub(ull a, ull b, ull m){
    return min(a-b,a-b+m);
}

// stolen from https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModMulLL.h
// works for a,b,m < 7.2e18
inline ull modmul(ull a, ull b, ull m){
    ull ret = a*b - m*ull(dbll(a)*b/m);
    return min({ret,ret+m,ret-m});
}

ull inverse(ull a, ull m){
    complex<ull> ca{1,0}, cb{0,1};

    while(a){
       ull curdiv = a/m;
        ca-=cb*curdiv;
        a-=m*curdiv;
        swap(a,m);
        swap(ca,cb);
    }

    return min(cb.real(), -cb.real());
}

ull divmul(ull a, ull b, ull m){
    return modmul(a,inverse(b,m),m);
}

ull power(ull in, ull exp, ull m){
    ull ret = 1;
    while(exp){
        if(exp&1)
            ret = modmul(ret,in,m);
        in = modmul(in,in,m);
        exp>>=1;
    }
    return ret;
}