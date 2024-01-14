/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements matrices and some linear algebra stuff for them.

Said linear algebra stuff uses "vector++.cpp", in case you dont need it
you can comment the functions that error.
*/

#ifndef O_O
#include"header.h"
#include"vector++.cpp"
#endif

template<typename T>
struct Matrix{

    matrix<T> v;

    Matrix(int n, int m = -1, int id = 0){
        if(m == -1)
            m = n;

        v = matrix<T>(n, vector<T>(m));

        if(id){
            for(int i = 0; i < min(n,m); i++)
                v[i][i] = T(1);
        }
    }

    Matrix(matrix<T> m) : v (m){}

    vector<T>& operator[] (int id){
        return v[id];
    }

    void transpose(){
        int n = v.size(), m = v[0].size();

        Matrix newv(m,n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                newv[j][i] = v[i][j];
        
        swap(*this, newv);
    }
    
    Matrix operator*(Matrix b){
        Matrix ret(v.size(), b[0].size());

        for(int i = 0; i < v.size(); i++)
            for(int j = 0; j < b.v.size(); j++)
                for(int k = 0; k < b[0].size(); k++)
                    ret[i][k]+=v[i][j]*b[j][k];
        
        return ret;
    }

    // Linear algebra starts here:

    /*
    Does gaussian elimination and takes optional
    results array in case we are trying to solve a system of
    linear equations.

    Assumes to be a square matrix.

    Returns determinant of the matrix*/

    T gaussjordanize(vector<T>& results){
        for(int i = 0; i < results.size(); i++)
            v[i].push_back(results[i]);
        
        T det = T(1);

        int line = 0;
        for(int col = 0; col < v.size(); col++){

            int pivot = line;
            while(pivot < v.size() && v[pivot][col] == T(0))
                pivot++;
            
            if(pivot == v.size())
                continue;
            

            swap(v[line], v[pivot]);
            if(line != pivot)
                det *= T(-1);
            
            det*=v[line][col];
            v[line]/=v[line][col];

            for(int i = 0; i < v.size(); i++){
                if(i == line)
                    continue;
                
                v[i] -= v[line]*v[i][col];
            }

            line++;
        }

        for(int i = 0; i < results.size(); i++){
            results[i] = v[i].back();
            v[i].pop_back();
        }

        return det * (line == v.size());
    }

    T gaussjordanize(){
        vector<T> _;

        return gaussjordanize(_);
    }
};