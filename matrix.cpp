/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements linear algebra stuff for matrices.
*/

#ifndef O_O
#include"header.h"
#include"vector2.cpp"
#endif

template<typename T>
struct Matrix{

    Vector<Vector<T>> v;

    Matrix(int n = 0, int id = 0) : v(n, Vector<T>(n)) {
        if(id){
            for(int i = 0; i < n; i++)
                v[i][i] = T(1);
        }
    }

    Matrix(matrix<int> m) : v(m){};

    Vector<T>& operator[](int id){
        return v[id];
    }

    void transpose(){
        for(int i = 0; i < v.size(); i++){
            for(int j = i+1; j < v.size(); j++)
                swap(v[i][j],v[j][i]);
        }
    }

    // *this and b are assumed to be square matrices
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

    // second is how much the determinant is scaled by
    pair<Vector<T>,T> gaussjordanize(Vector<T> res){
        int n = v.size();

        T scale = T(1);

        for(int i = 0; i < n; i++)
            v[i].push_back(res[i]);

        int lin = 0;
        for(int col = 0; col < n; col++){
            int nxt = lin;
            while(nxt < n && v[nxt][col] == 0){
                nxt++;
            }
            if(nxt == n)
                continue;
            
            swap(v[nxt],v[lin]);
            if(nxt != lin)
                scale*=-1;

            for(int i = 0; i < n; i++){
                if(i == lin)
                    continue;
                v[i] = v[i]*v[lin][col]-v[lin]*v[i][col];
                scale*=v[lin][col];
            }

            lin++;
        }

        Vector<T> ret(n);

        for(int i = 0; i < n; i++)
            ret[i] = v[i].back(), v[i].pop_back();
        
        return {ret,scale};
    }

    T determinant(){
        Matrix<T> copia = *this;
        auto [_, scale] = copia.gaussjordanize(Vector<T>(v.size()));

        T resp = T(1);

        for(int i = 0; i < v.size(); i++)
            resp*=copia[i][i];
        
        return resp/scale;
    }
};