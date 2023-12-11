/*
from https://github.com/defnotmee/definitely-not-a-lib

Sadly I already use "matrix" for vector<vector<int>> on
my template so ill have to use Matrix for this one :(
*/

#ifndef O_O
#include"header.h"
#endif

// you dont even need to call Matrix<SZ, T>, you can just
// edit the parameters here
template<const int SZ = 2, typename T = ll>
struct Matrix{

    using arr = array<array<T,SZ>, SZ>;

    arr v;

    // if id = 1, returns identity matrix, else returns empty matrix
    Matrix(int id = 0){
        v = arr({});

        if(id)
        for(int i = 0; i < SZ; i++)
            v[i][i] = 1;
    }

    Matrix operator*(Matrix b){
        Matrix ret();

        for(int i = 0; i < SZ; i++){
            for(int j = 0; j < SZ; j++){
                for(int k = 0; k < SZ; k++){
                    ret.v[i][k]+= v[i][j]*b.v[j][k];
                }
            }
        }

        return ret;
    }

    void operator*=(Matrix b){
        *this = *this * b;
    }
};