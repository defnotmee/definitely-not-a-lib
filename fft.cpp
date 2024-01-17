/*
from https://github.com/defnotmee/definitely-not-a-lib

Thanks -is-this-fft- for your blog https://codeforces.com/blog/entry/111371

Based on https://cp-algorithms.com/algebra/fft.html
*/

#ifndef O_O
#include"header.h"
#endif

using cd = complex<double>;

void fft(vector<cd>& v, bool inverse = 0){
    int n = v.size();
    int lg = log2(n);

    auto rev =[&](int id){
        int add = 1<<lg-1;
        int ret = 0;

        while(id){
            if(id&1)
                ret+=add;
            add>>=1;
            id>>=1;
        }

        return ret;
    };

    for(int i = 0; i < n; i++){
        int x = rev(i);
        if(i < x)
            swap(v[i], v[x]);
    }
    
    for(int len = 1; len < n; len<<=1){
        cd base = polar(1.0, M_PI/len);
        
        for(int block = 0; block < n; block+=2*len){
            cd z(1,0);
            for(int l = block; l < block+len; l++){
                cd cur = z*v[l+len];
                tie(v[l], v[l+len]) =
                    make_pair(v[l]+cur, v[l]-cur);
                z*=base;
            }
        }
    }

    if(inverse){
        reverse(1+all(v));
        for(auto& i : v)
            i/=n;
    }
}


vector<ll> convolution(vector<ll>& a, vector<ll>& b){
    int mx = max(a.size(),b.size());
    int lg = log2(4*mx);
    int sz = 1<<lg;

    vector<cd> na(sz), nb(sz);

    for(int i = 0; i < a.size(); i++)
        na[i].real(a[i]);
    for(int i = 0; i < b.size(); i++)
        nb[i].real(b[i]);

    fft(na), fft(nb);

    for(int i = 0; i < sz; i++)
        na[i] *= nb[i];

    fft(na,1);

    vector<ll> ret(sz);
    for(int i = 0; i < sz; i++){
        ret[i] = round(na[i].real());
    }

    return ret;

}