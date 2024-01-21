/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements primality check with miller-rabin in O(7logn) and
prime factorization in O(n^(1/4)) with pollard-rho.

Primality checking is [supposedly] deterministic but factoring
is a monte carlo algorithm.

Pollard-rho impl is heavily based on:
https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/Factor.h
*/

#ifndef O_O
#include"header.h"
#include"beegmod.cpp"
#endif

bool is_prime(ull n){
    if(n <= 1)
        return false;

    ull ctz = countr_zero(n-1);
    ull d = n>>ctz;

    auto primes = {2, 3, 5, 13, 19, 73, 193, 407521, 299210837};
    // all primes up to 37 is a reasonable option too
    auto bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    
    for(ull p : primes)
        if(n == p)
            return 1;

    for(ull base : bases){
        ull cur = power(base,d,n);
        if(cur == 1)
            continue;
        for(int i = 0; i < ctz; i++){
            if(cur == n-1)
                goto NEXT;
            cur = modmul(cur,cur,n);
        }
        return false;
        NEXT:;
    }

    return true;

}

template<typename T>
void pollard(T n, vector<T>& v){
    if(n == 1)
        return;
    if(is_prime(n)){
        v.push_back(n);
        return;
    }

    static mt19937_64 rng(RANDOM);
    uniform_int_distribution<T> rg(0,n-1);
    T c = rg(rng);
    T x, y;
    x = y = rg(rng);

    auto next = [&](T x){
        return modadd(modmul(x,x,n),c,n);
    };
    
    T prod = 2;
    T g = 1;
    while((g = gcd(prod,n)) == 1){
        for(int i = 0; i < 50; i++){
            if(x == y)
                x = y = rg(rng), c = rg(rng);
            x = next(x);
            y = next(next(y));
            ll cur = modmul(abs(x-y),prod,n);
            if(cur)
                prod = cur;
        }
    }

    pollard(g,v);
    pollard(n/g,v);
}

template<typename T>
vector<T> factorize(T n, bool sorted = 0){
    vector<T> ret;

    pollard(n,ret);

    if(sorted)
        sort(all(ret));

    return ret;
}