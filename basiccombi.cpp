/*
from https://github.com/defnotmee/definitely-not-a-lib

Calculates factorials and binomials modulo p for all 
numbers from 0 to n-1. By default creates the struct
for n = MAXN and names it combi.

Idea for O(n) inverse of each number from this blog:
https://codeforces.com/blog/entry/83075
*/


#ifndef O_O
#include"header.h"
#include"modint.cpp"
#endif

struct Combi{
    // note that inv[0] = 1 in this impl
    vector<modint> fac, inv, invfac;

    Combi(int n = MAXN){
        fac = inv = invfac = vector<modint>(n,1);

        for(int i = 2; i < n; i++){
            fac[i] = fac[i-1]*i;
            inv[i] = (inv[MOD%i])*(MOD-(MOD/i));
            invfac[i] = invfac[i-1]*inv[i];
        }
    }

    modint choose(int n, int k){
        if(n < k)
            return 0;
        return fac[n]*invfac[k]*invfac[n-k];
    }
} combi;