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
    Does gaussian elimination and puts matrix in
    upper echelon form (not reduced, since its 2x slower)

    Returns determinant of the matrix square matrix induced
    by the number of lines of the matrix
    */

    T gaussjordanize(){
        T det = T(1);

        int line = 0;
        for(int col = 0; col < v.size(); col++){

            int pivot = line;
            while(pivot < v.size() && v[pivot][col] == T(0))
                pivot++;
            
            if(pivot >= v.size())
                continue;
            

            swap(v[line], v[pivot]);
            if(line != pivot)
                det *= T(-1);
            
            det*=v[line][col];
            v[line]/=v[line][col];

            for(int i = line+1; i < v.size(); i++){
                v[i] -= v[line]*v[i][col];
            }

            line++;
        }

        return det * (line == v.size());
    }

    /*
    Needs to be called in a square matrix that represents a system of linear
    equations.
    Returns {possible solution, number of solutions (2 if infinite solutions)}
    */ 
    pair<vector<T>,int> solve_system(vector<T> results){
        for(int i = 0; i < results.size(); i++)
            v[i].push_back(results[i]);

        T det = gaussjordanize();

        int ret = 1 + (det == T(0));

        int n = results.size();
        
        for(int i = n-1; i >= 0; i--){
            int pivot = 0;
            while(pivot < n && v[i][pivot] == T(0))
                pivot++;
            
            if(pivot == n){
                if(v[i].back() != T(0))
                    ret = 0;
            } else swap(v[i], v[pivot]);
        }

        for(int i = n-1; i >= 0; i--){
            for(int j = i+1; j < n; j++)
                v[i].back()-=v[i][j]*v[j].back();
        }

        for(int i = 0; i < n; i++)
            results[i] = v[i].back(), v[i].pop_back();

        return {results, ret};

    }
};
