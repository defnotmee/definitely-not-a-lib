/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements matrices and some linear algebra stuff for them.

Said linear algebra stuff uses "vector++.cpp", so copy it too
if you want to use it 
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

    void operator*=(Matrix b){
        *this = *this*b;
    }

    Matrix power(ll exp){
        Matrix in = *this;
        Matrix ret(in.v.size(), -1, 1);

        for(;exp; exp>>=1){
            if(exp&1)
                ret*=in;
            in*=in;
        }

        return ret;
    }

    #ifdef vectorpp

    /*
    Alters current matrix.

    Does gaussian elimination and puts matrix in
    upper echelon form (possibly reduced)

    Returns determinant of the matrix square matrix induced
    by the number of lines of the matrix
    */

    T gaussjordanize(int reduced = 0){
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

            if(reduced)
                for(int i = 0; i < line; i++){
                    v[i] += T(-1)*v[i][col]*v[line];
                }
            
            for(int i = line+1; i < v.size(); i++){
                v[i] += T(-1)*v[i][col]*v[line];
            }

            line++;
        }

        return det * (line == v.size());
    }

    /*
    Alters current Matrix.

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
    
    /*
    Does not alter current matrix.
    Returns {inverse matrix, is curent matrix invertable}
    */
    pair<Matrix<T>, bool> find_inverse(){
        int n = v.size();
        Matrix<T> aug = *this;
        Matrix<T> ret(n, -1, 1);

        for(int i = 0; i < n; i++)
            aug[i].insert(aug[i].end(), all(ret[i]));

        T det = aug.gaussjordanize(1);

        for(int i = 0; i < n; i++){
            ret[i] = vector<T>(n+all(aug[i]));
        }

        return {ret, det != T(0)};
    }

    #endif
};