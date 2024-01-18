/*
from https://github.com/defnotmee/definitely-not-a-lib

Thanks -is-this-fft- for your blog https://codeforces.com/blog/entry/111371

References for implementation: 
https://cp-algorithms.com/algebra/fft.html
http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h
*/

#ifndef O_O
#include"header.h"
#include"modint.cpp"
#endif

using cd = complex<double>;

template<typename T>
void fft(vector<complex<T>>& v, bool inverse = 0){
    int n = v.size();
    int lg = log2(n);

    static vector<cd> roots;

    roots.resize(n,cd(1,0));

    for(static int len = 2; len < n; len<<=1){
        cd z = polar(T(1), acos(T(-1))/len);
        for(int i = len; i < 2*len; i++){
            roots[i] = roots[i/2] * ((i&1) ? z : T(1));
        }
    }

    vector<int> rev(n);

    for(int i = 1; i < n; i++){
        rev[i] = (rev[i>>1]>>1)+((i&1)<<lg-1);
    }

    for(int i = 1; i < n; i++)
        if(rev[i] > i)
            swap(v[i],v[rev[i]]);
    
    for(int len = 1; len < n; len<<=1){
        for(int block = 0; block < n; block+=2*len){
            for(int l = block; l < block+len; l++){
                cd cur = roots[l-block+len]*v[l+len];
                tie(v[l], v[l+len]) =
                    make_pair(v[l]+cur, v[l]-cur);
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
    int n = 1;

    while(n+1 < a.size()+b.size())
        n<<=1;

    vector<cd> in(n);

    for(int i = 0; i < a.size(); i++)
        in[i].real(a[i]);
    for(int i = 0; i < b.size(); i++)
        in[i].imag(b[i]);

    fft(in);

    vector<cd> newin(n);

    for(int i = 0; i < n; i++){
        int opos = (n-i)&(n-1);
        newin[i] = (in[opos]+conj(in[i]))
        *(in[opos]-conj(in[i]))*cd(0, -0.25/n);
    }
    
    fft(newin);

    vector<ll> ret(a.size()+b.size()-1);
    for(int i = 0; i < a.size()+b.size()-1; i++){
        ret[i] = round(newin[i].real());
    }

    return ret;

}

template<ull M = MOD>
vector<modint<M>> convolutionmod(vector<ll>& a, vector<ll>& b){
    
    const int len = sqrt(MOD);
    int n = 1;
    while(n+1 < a.size()+b.size())
        n<<=1;

    vector<cd> ca(n), cb(n);

    for(int i = 0; i < a.size(); i++)
        ca[i] = cd(a[i]%len, a[i]/len);
    
    for(int i = 0; i < b.size(); i++)
        cb[i] = cd(b[i]%len, b[i]/len);

    fft(ca), fft(cb);

    vector<cd> p1(n), p2(n);

    for(int i = 0; i < n; i++){
        int opos = (n-i)&(n-1);

        // also inverting for fft inverse
        p1[i] = (ca[opos]+conj(ca[i]))*cb[opos]*(0.5/n);
        p2[i] = (ca[opos]-conj(ca[i]))*cb[opos]*cd(0,-0.5/n);
    }

    fft(p1), fft(p2);

    vector<modint<M>> ret(a.size()+b.size()-1);

    for(int i = 0; i < ret.size(); i++){
        modint<M> small = round(p1[i].real()),
            mid = (ll)round(p1[i].imag()) + (ll)round(p2[i].real()),
            big = round(p2[i].imag());

        ret[i] = small + mid*len + big*len*len;

    }

    return ret;
}