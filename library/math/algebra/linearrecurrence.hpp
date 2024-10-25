/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T>
T get_kth_term(vector<T> s, vector<T> c, ll k){

    Poly<T> charac(c.size()+1);
    for(int i = 0; i < c.size(); i++)
        charac[i] = c[c.size()-i-1]*-1;
    charac.p.back() = 1;
    
    Poly<T> retp(c.size());
    retp[0] = 1;
    Poly<T> mul(c.size());
    if(c.size() == 1)
        mul[0] = c[0];
    else mul[1] = 1;

    while(k){
        if(k&1){
            retp*=mul;
            retp%=charac;
        }

        mul*=mul;
        mul%=charac;

        k>>=1;
    }

    T ret = 0;

    for(int i = 0; i < c.size(); i++){
        ret+=s[i]*retp[i];
    }

    return ret;
}