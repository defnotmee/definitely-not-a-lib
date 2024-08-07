/*
from https://github.com/defnotmee/definitely-not-a-lib

Calculates smallest prime that divides each number for
all x < n and also maintains a list of all primes up to that
in O(n)

By default creates a sieve named sieve of size MAXN.
*/

#ifndef O_O
#include"template.cpp"
#endif

struct Sieve{
    vector<int> primes;
    vector<int> next;

    Sieve(int n){
        next = vector<int>(n);

        for(int i = 2; i < n; i++){
            if(!next[i])
                next[i] = i, primes.push_back(i);
            
            for(ll j : primes){
                if(j*i >= n)
                    break;
                next[j*i] = j;
                if(j == next[i])
                    break;
            }
        }
    }

    inline bool is_prime(int n){
        return next[n] == n;
    }

    // returns pairs in form {prime, exponent}
    // will always return them in ascending order
    vector<pii> factorize(int n){
        vector<pii> ret;

        while(n != 1){
            int p = next[n];
            int ct = 0;
            while(n%p == 0)
                ct++, n/=p;
            ret.push_back({p,ct});
        }
        return ret;
    }
} sieve(MAXN);