/*
from https://github.com/defnotmee/definitely-not-a-lib

Does binary exponentation. By default can handle exponents
< 2^63, for more you just edit the constants in the function.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T>
T power(T cur, ll exp){
    T ret = T(1); // works for modint.cpp by default

    while(exp){
        if(exp&1)
            ret*=cur;
        cur*=cur;
        exp>>=1;
    }
    return ret;
}