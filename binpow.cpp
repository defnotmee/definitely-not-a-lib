/*
from https://github.com/defnotmee/definitely-not-a-lib

Does binary exponentation. By default can handle exponents
< 2^30, for more you just edit the constants in the function.
*/

#ifndef O_O
#include"header.h"
#endif

template<typename T>
T power(T cur, int exp){
    T resp = T(1); // works for modint.cpp and matrix.cpp by default

    // edit this to 60 if you change the exp to long long
    for(int i = 0; i < 30; i++){
        if((exp>>i)&1)
            resp *= cur;
        cur*=cur;
    }

    return resp;
}