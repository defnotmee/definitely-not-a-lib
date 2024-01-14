/*
from https://github.com/defnotmee/definitely-not-a-lib

Adds extra funcitonality to vectors, making them behave like
linear algebra vectors.

You can sum them, subtract them, multiply by scalar and
get their scalar product via operator overloads.
*/

#ifndef O_O
#include"header.h"
#endif


template<typename T>
constexpr vector<T> operator+(vector<T> a, vector<T> b){
    vector<T> ret = a;
    for(int i = 0; i < a.size(); i++)
        ret[i]+=b[i];
    return ret;
}


template<typename T>
constexpr vector<T> operator*(vector<T> a, T b){
    vector<T> ret = a;
    for(int i = 0; i < a.size(); i++)
        ret[i]*=b;
    return ret;
}

template<typename T>
constexpr vector<T> operator*(T b, vector<T> a){
    return a*b;
}

template<typename T>
constexpr vector<T> operator/(vector<T> a, T b){
    return a*(T(1)/b);
}

template<typename T>
constexpr vector<T> operator-(vector<T> a, vector<T> b){
    return a+(b*T(-1));
}

template<typename T>
constexpr T operator*(vector<T> a, vector<T> b){
    T ret = T(0);
    for(int i = 0; i < a.size(); i++)
        ret+=a[i]*b[i];
    return ret;
}


template<typename T>
void operator+=(vector<T> a, vector<T> b){
    a = a + b;
}

template<typename T>
void operator*=(vector<T> a, T b){
    a = a * b;
}

template<typename T>
void operator/=(vector<T> a, T b){
    a = a / b;
}

template<typename T>
void operator-=(vector<T> a, vector<T> b){
    a = a - b;
}
