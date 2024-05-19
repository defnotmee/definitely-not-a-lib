/*
from https://github.com/defnotmee/definitely-not-a-lib

The best cartesian tree.

Given an array v, calculates the following information in O(n):

- fl[i]: biggest j < i such that v[j] <= v[i]. fl[i] = -1 by default
- fr[i]: smallest j > i such that v[j] < v[i]. fr[i] = n by default
- cl[i]: index of the element that minimizes v[j] for fl[i] < j < i. cl[i] = i by default
- cr[i]: index of the element that minimizes v[j] for i < j < fr[i]. cr[i] = i by default
- pai[i]: parent of i on the cartesian tree, that is, in the tree where i has edges to cl[i] and cr[i]. -1 by default.

In case there are repeated elements, the ones with lowest index will be closer to the root of the cartesian tree.

Can also take different comparator functions in its template
*/

#ifndef O_O
#include"template.cpp"
#endif

template<typename T, typename cmp = less<T>>
struct CarTree{
    int n;
    vector<T> v;
    vector<T> fl, fr, cl, cr, pai;
    int root;

    CarTree(vector<T>& _v) : n(_v.size()), v(_v), fl(n), fr(n), cl(n), cr(n), pai(n,-1){
        for(int i = 0; i < n; i++){
            fl[i] = i-1;
            cl[i] = cr[i] = i;
            fr[i] = n;

            int lst = -1;
            while(fl[i] != -1 && cmp()(v[i], v[fl[i]])){
                lst = fl[i];
                fr[fl[i]] = i;
                fl[i] = fl[fl[i]];
            }
            if(lst != -1)
                cl[i] = lst, pai[lst] = i;
            if(fl[i] != -1)
                cr[fl[i]] = i, pai[i] = fl[i];
        }
    }
};