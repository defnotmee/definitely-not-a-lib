/*
from https://github.com/defnotmee/definitely-not-a-lib

Create a vector that can be accessed with indexes from [-n to n-1].
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T>
struct offvec{

    vector<T> v;
    int offset;

    offvec(int n = 0, T def = T()){
        offset = n;
        v = vector<T>(2*n, def);
    }

    T& operator[](int id){
        return v[id+offset];
    }
};