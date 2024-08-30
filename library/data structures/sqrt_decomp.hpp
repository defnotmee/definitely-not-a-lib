/*
from https://github.com/defnotmee/definitely-not-a-lib

Divides an array into blocks of sqrt. In this case,
its doing range addition update and range maximum query.

TODO: clean code, make it more general
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

const int LEN = 400;

template<typename T = ll>
struct decomp{
    vector<T> elem;
    vector<T> block, lz;

    decomp(int n = 0){
        elem = vector<T>(n);
        block = vector<T>((n+LEN-1)/LEN);
        lz = vector<T>((n+LEN-1)/LEN);
    }

    void reconstruct(int bid){
        block[bid] = 0;
        for(int i = bid*LEN; i < min(int(elem.size()), (bid+1)*LEN); i++){
            block[bid] = max(block[bid], elem[i]);
        }
        block[bid]+=lz[bid];
    }

    void update(int l, int r, T x){
        int bl = l/LEN+1, br = r/LEN;

        if(bl >= br){
            for(int i = l; i <= r; i++)
                elem[i]+=x;

            reconstruct(br);
            if(bl-1 != br)
                reconstruct(bl-1);
        } else {
            for(int i = l; i < bl*LEN; i++)
                elem[i]+=x;
            for(int i = bl; i < br; i++)
                lz[i]+=x, block[i]+=x;
            for(int i = br*LEN; i <= r; i++)
                elem[i]+=x;

            reconstruct(bl-1);
            reconstruct(br);
        }
    }

    T query(int l, int r){
        int bl = l/LEN+1, br = r/LEN;
        T ret = T();

        if(bl >= br){
            for(int i = l; i <= r; i++)
                ret = max(ret,elem[i]+lz[i/LEN]);
        } else {
            for(int i = l; i < bl*LEN; i++)
                ret = max(ret,elem[i]+lz[bl-1]);
            for(int i = bl; i < br; i++)
                ret = max(ret,block[i]);
            for(int i = br*LEN; i <= r; i++)
                ret = max(ret,elem[i]+lz[br]);
        }
        return ret;
    }
};