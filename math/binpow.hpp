/*
from https://github.com/defnotmee/definitely-not-a-lib

Does binary exponentation. By default can handle exponents
< 2^30, for more you just edit the constants in the function.
*/

#ifndef O_O
#include"template.cpp"
#endif

template<typename T>
T power(T cur, int exp){
    T resp = T(1); // works for modint.cpp and matrix.cpp by default

    while(exp){
        if(exp&1)
            resp*=cur;
        cur*=cur;
        exp>>=1;
    }
    return resp;
}