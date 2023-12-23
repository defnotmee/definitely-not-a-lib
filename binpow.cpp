/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"header.h"
#endif

template<typename T>

T power(T cur, int exp){
    T resp = T(1);

    // this assumes exp < 2^30, feel free to change
    for(int i = 0; i < 30; i++){
        if((exp>>i)&1)
            resp *= cur;
        cur*=cur;
    }

    return resp;
}