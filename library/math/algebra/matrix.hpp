/*
from https://github.com/defnotmee/definitely-not-a-lib

Implements matrices and linear algebra stuff for them.

Includes multiplication, addition, solving system of equation,
finding ranks, etc
*/

#ifndef O_O
#include"../../utility/template.cpp"
#endif

template<typename T>
struct Matrix{

    int n, m;
    valarray<valarray<T>> v;

    Matrix(int _n, int _m, int id = 0) : n(_n), m(_m), v(valarray<T>(m),n) {
        if(id){
            for(int i = 0; i < min(n,m); i++)
                v[i][i] = 1;
        }
    }

    valarray<T>& operator[] (int x){
        return v[x];
    }


    Matrix transpose(){
        Matrix newv(m,n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                newv[j][i] = (*this)[i][j];
        
        return newv;
    }
    
    Matrix operator+(Matrix& b){
        Matrix ret(*this);
        return ret.v+=b.v;
    }

    Matrix& operator+=(Matrix& b){
        return v += b.v;
    }

    Matrix operator*(Matrix b){
        Matrix ret(n, b.m);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int k = 0; k < b.m; k++)
                    ret[i][k] += v[i][j]*b.v[j][k];
        
        return ret;
    }

    Matrix& operator*=(Matrix b){
        return *this = *this*b;
    }

    Matrix power(ll exp){
        Matrix in = *this;
        Matrix ret(n, n, 1);

        while(exp){
            if(exp&1)
                ret*=in;
            in*=in;
            exp>>=1;
        }
        return ret;
    }

    /*
    Alters current matrix.

    Does gaussian elimination and puts matrix in
    upper echelon form (possibly reduced).

    Returns the determinant of the square matrix with side equal to the number
    of rows of the original matrix.
    */

    T gaussjordanize(int reduced = 0){
        T det = T(1);

        int line = 0;
        for(int col = 0; col < m; col++){

            int pivot = line;
            while(pivot < n && v[pivot][col] == T(0))
                pivot++;
            
            if(pivot >= n)
                continue;

            swap(v[line], v[pivot]);

            if(line != pivot)
                det *= T(-1);
        
            det*=v[line][line];
            
            v[line]/=T(v[line][col]);

            if(reduced)
                for(int i = 0; i < line; i++){
                    v[i] -= T(v[i][col])*v[line];
                }
            
            for(int i = line+1; i < n; i++){
                v[i] -= T(v[i][col])*v[line];
            }

            line++;
        }

        return det * (line == n);
    }

    /*
    When called on any matrix, puts it in reduced row echelon form and solves the system of equations
    it represents. In particular, if called on matrix A, finds a vector x such that Ax = y

    Returns {possible x, number of solutions (2 if there are infinite solutions)}

    In case theres no solution, returns {{},0}
    */ 
    pair<vector<T>,int> solve_system(vector<T> y){
        
        Matrix aug(n, m+1);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                aug[i][j] = v[i][j];
            aug[i][m] = y[i];
        }

        aug.gaussjordanize(1);

        int solcount = n < m ? 2 : 1;
        
        vector<T> x(m);

        for(int i = n-1; i >= 0; i--){
            if(i < m && aug[i][i] == T(0))
                solcount = 2;

            int pivot = 0;
            while(pivot < m && aug[i][pivot] == T(0))
                pivot++;
            
            if(pivot == m){
                if(aug[i][m] != T(0)){
                    return {{},0};
                }
                continue;
            }

            x[pivot] = aug[i][m];

            for(int j = pivot+1; j < m; j++){
                x[pivot]-=x[j]*aug[i][j];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                v[i][j] = aug[i][j];
        }

        return {x, solcount};

    }

    /*
    Finds a possible solution for the system of linear equations, as well as a
    basis for the solution. The set of solutions will be a linear combination of
    the basis, added to the initial answer provided.

    First return value is the initial solution, and the second is the basis of the solution.
    If there is no solution, both return values will be empty vectors.
    */
    pair<vector<T>, vector<vector<T>>> basis_solution(vector<T> y){
        auto [x0, solcount] = solve_system(y);

        if(solcount == 0){
            return {};
        }

        vector<int> pivot(n);
        vector<int> pivoted(m);
        for(int i = 0; i < n; i++){
            while(pivot[i] < m && v[i][pivot[i]] == T(0))
                pivot[i]++;
            if(pivot[i] < m)
                pivoted[pivot[i]] = 1;
        }

        vector<vector<T>> basis;
        for(int i = 0; i < m; i++){
            if(pivoted[i])
                continue;
            vector<T> cbasis(m);
            cbasis[i] = 1;
            for(int j = 0; j < n; j++){
                if(pivot[j] != m)
                    cbasis[pivot[j]] += T(-1)*v[j][i];
            } 
            basis.push_back(cbasis);
        }
        assert(bool(solcount > 1) == bool(basis.size()));
        
        return {x0,basis};
    }
    
     /*
    Does not alter current matrix.
    Returns {inverse matrix, is curent matrix invertable}
    */
    pair<Matrix<T>, bool> find_inverse(){
        int n = v.size();
        Matrix<T> aug(n, 2*n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                aug[i][j] = v[i][j];
            
        for(int i = 0; i < n; i++)
            aug[i][n+i] = 1;

        T det = aug.gaussjordanize(1);

        Matrix<T> ret(n,n);
        for(int i = 0; i < n; i++){
            ret[i] = valarray<T>(aug[i][slice(n,n,1)]);
        }

        return {ret, det != T(0)};
    }

    // Returns rank of matrix. Does not alter it.
    int get_rank() const {
        if(m == 0)
            return 0;

        Matrix<T> aux(*this);

        aux.gaussjordanize();

        int resp = 0;

        for(int i = 0; i < n; i++)
            resp += (aux[i] != valarray<mint>(m)).sum();

        return resp;
    }

};