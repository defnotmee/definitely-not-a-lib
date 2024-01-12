/*
from https://github.com/defnotmee/definitely-not-a-lib

Inherits std::vector and adds linear algebra basic functionality.

You can sum, subtract, multiply by a scalar (sadly you need to do
v*2 instead of 2*v) and get dot product
*/

#ifndef O_O
#include"header.h"
#endif

template<typename T>
struct Vector : vector<T>{

    using vector<T>::vector;

    Vector operator+(Vector b){
        for(int i = 0; i < this->size(); i++)
            b[i]+=(*this)[i];
        return b;
    }

    Vector operator*(T b){
        Vector ret = *this;
        for(T& i : ret)
            i*=b;
        return ret;
    }

    T operator*(Vector b){
        T ret = T();
        for(int i = 0; i < this->size(); i++)
            ret += (*this)[i]*b[i];
        return ret;
    }

    Vector operator-(Vector b){
        b = b*-1;
        return *this+b;
    }

    void operator+=(Vector b){
        *this = *this+b;
    }
    
    void operator-=(Vector b){
        *this = *this-b;
    }

    void operator*=(T b){
        *this = *this*b;
    }
};