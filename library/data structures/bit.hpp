/*
from https://github.com/defnotmee/definitely-not-a-lib

Usage: BIT(n) -> creates array arr of size n where you can
make point updates and prefix queries (0-indexed!) in O(log(n))

BIT::merge(a, b) -> merges b into element a. By default a+=b.
(must be commutative and associative)

BIT::update(id, x) -> merge(arr[i],x) for every i <= id

BIT::query(id) -> initializes ret = T(), does merge(ret, arr[i])
for every i <= id, returns ret.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T = ll>
struct BIT{
    vector<T> bit;

    BIT(int n = 0){
        bit = vector<T>(n+1);
    }
    
    static void merge(T& a, T b){
        a+=b;
    }

    void update(int id, T x){
        id++;
        while(id < bit.size()){
            merge(bit[id],x);
            id+=id&-id;
        }
    }

    T query(int id){
        id++;
        T ret = T();
        while(id){
            merge(ret,bit[id]);
            id-=id&-id;
        }
        return ret;
    }
};