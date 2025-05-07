/*
from https://github.com/defnotmee/definitely-not-a-lib

Fast matrix multiplication with modulo. Useful for matrix
exponentiation problems and such.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<ull M = MOD>
void mat_mul(matrix<ll> a, matrix<ll> b){
    matrix<ll> ret(a.size(), vector<ll>(b[0].size()));
    
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b[0].size(); j++){
            int ct = LONG_LONG_MAX/(M*M);
            for(int k = 0; k < b.size(); k++, ct--){
                ret[i][j] += a[i][k]*b[k][i];
                if(ct)  
                    ret[i][j]%=M;
            }
            ret[i][j]%=M;
        }
    }

    return ret;
}
