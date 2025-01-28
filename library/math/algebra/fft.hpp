/*
from https://github.com/defnotmee/definitely-not-a-lib

Thanks -is-this-fft- for your blog https://codeforces.com/blog/entry/111371

References for implementation: 
https://cp-algorithms.com/algebra/fft.html
http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h
*/

#ifndef O_O
#include"../../utility/template.cpp"
#endif

using cdl = complex<dbll>;
using cd = complex<double>; // change this to long double if WA and pray

void fft(vector<cd>& v, bool inverse = 0){
    int n = v.size();
    int lg = log2(n);

    static vector<cdl> loots;
    static vector<cd> roots;

    if(loots.size() < n){
        loots.resize(n,1);
        roots.resize(n,1);
    }
    

    for(static int len = 2; len < n; len<<=1){
        cdl z = polar(1.0l, acos(-1.0l)/len);
        for(int i = len; i < 2*len; i++){
            roots[i] = loots[i] = loots[i/2] * ((i&1) ? z : 1);
        }
    }

    vector<int> rev(n);

    for(int i = 1; i < n; i++){
        rev[i] = (rev[i>>1]>>1)+((i&1)<<lg-1);
        if(rev[i] > i)
            swap(v[i],v[rev[i]]);
    }
    
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

vector<cd> convolution(vector<cd> a, vector<cd> b){
    int mx = max(a.size(),b.size());
    int rets = a.size()+b.size()-1;
    int n = 1;
 
    while(n+1 < a.size()+b.size())
        n<<=1;
    
    a.resize(n), b.resize(n);
 
    fft(a), fft(b);
  
    for(int i = 0; i < n; i++){
        a[i]*=b[i];
    }
    
    fft(a,1);
    a.resize(rets);
 
    return a;
}
 

template<ull M = MOD>
vector<ll> convolutionmod(vector<ll>& a, vector<ll>& b){
    
    const int len = sqrt(M);
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
        p1[i] = (ca[opos]+conj(ca[i]))*cb[opos]*cd(0.5/n);
        p2[i] = (ca[opos]-conj(ca[i]))*cb[opos]*cd(0,-0.5/n);
    }

    fft(p1), fft(p2);

    vector<ll> ret(a.size()+b.size()-1);

    for(int i = 0; i < ret.size(); i++){
        ll r1 = round(p1[i].real()), i1 = round(p1[i].imag());
        ll r2 = round(p2[i].real()), i2 = round(p2[i].imag());

        ll small = r1%MOD, mid = (i1+r2)%MOD, big = i2%MOD;
        (ret[i] = small + mid*len + big*len%MOD*len)%=MOD;
    }

    return ret;
}