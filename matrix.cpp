/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements linear algebra stuff for matrices.
*/

#ifndef O_O
#include"header.h"
#include"vector2.cpp"
#endif

template<typename T = ll>
struct Matrix{

    Vector<Vector<T>> v;

    Matrix(int n = 0, int id = 0) : v(n, Vector<T>(n)) {
        if(id){
            for(int i = 0; i < n; i++)
                v[i][i] = T(1);
        }
    }

    Vector<T>& operator[](int id){
        return v[id];
    }

    void transpose(){
        for(int i = 0; i < v.size(); i++){
            for(int j = i+1; j < v.size(); j++)
                swap(v[i][j],v[j][i]);
        }
    }

    Matrix operator*(Matrix b){
        Matrix ret(v.size());

        for(int i = 0; i < v.size(); i++)
            for(int j = 0; j < v.size(); j++)
                for(int k = 0; k < v.size(); k++)
                    ret[i][k] += v[i][j]*b[j][k];
        
        return ret;
    }

    void operator*=(Matrix b){
        *this = *this*b;
    }
};