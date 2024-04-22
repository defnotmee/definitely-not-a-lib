/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#endif

struct BinLift{
    
    int n, lg;

    struct lift{
        int to;
    };

    // what happens when you go through a, and then go through b?
    constexpr static lift merge(lift a, lift b){
        return lift(b.to);
    }

    matrix<lift> jmp;

    BinLift(vector<int> next, int LG_MAX = 20) : n(next.size()), lg(LG_MAX){

        jmp = matrix<lift>(lg,vector<lift>(next.size()));
        
        // initialize jmp[0][i]
        for(int i = 0; i < next.size(); i++)
            jmp[0][i] = lift(next[i]);


        for(int i = 1; i < lg; i++){
            for(int j = 0; j < next.size(); j++){
                jmp[i][j] = merge(jmp[i-1][j], jmp[i-1][jmp[i-1][j].to]);
            }
        }
    }

    lift k_up(int id, int k){
        lift ret(id); // needs to be an identity element through merge
        while(k){
            ret = merge(ret, jmp[__builtin_ctz(k)][ret.to]);
            k-=k&-k;
        }
    }

};