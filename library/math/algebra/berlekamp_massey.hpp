/*
from https://github.com/defnotmee/definitely-not-a-lib

Based on https://mzhang2021.github.io/cp-blog/berlekamp-massey/

Finds coefficients of the shortest linear recurrence that
describes a given sequence in O(n^2). If the original linear recurrence
is of order k, 2k terms will be necessary to pinpoint it exactly.

Returns a sequence c0c1c2...ck where if the sequence is s0s1s2...sn
it will hold that si = sum(c(j)*s(i-j-1)) for i > k.
*/

#ifndef O_O
#include"../../utility/template.cpp"
#endif

template<typename T>
vector<T> berlekamp_massey(vector<T> s){
    vector<T> c, oc;
    T ldelta = 0;
    int f = 0;
    for(int i = 0; i < s.size(); i++){
        T delta = s[i];

        for(int j = 0; j < c.size(); j++){
            delta-=c[j]*s[i-j-1];
        }

        if(delta == 0)
            continue;
        if(ldelta == 0){
            c = vector<T>(i+1);
            f = i;
            ldelta = delta;
            continue;
        }

        vector<T> maybe = c;
        vector<T> d = oc;

        for(auto& i : d)
            i*=-1;

        d.insert(d.begin(),T(1));
        
        c.resize(max(c.size(), d.size()+i-f-1));

        T mult = delta/ldelta;
        for(int j = 0; j < d.size(); j++)
            c[j+i-f-1]+=d[j]*mult;

        if(i+oc.size() > f+maybe.size()){
            oc = maybe;
            f = i;
            ldelta = delta;
        }
    }

    return c;

}
