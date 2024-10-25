/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T>
struct Poly{
    int n;
    vector<T> p;

    Poly(int n) : n(n), p(n){}
    Poly(const vector<T>& v) : n(v.size()), p(v){}
    
    T& operator[](int id) {
        return p[id];
    }

    Poly operator+(Poly b) const {
        Poly ret(max(n, b.n));

        for(int i = 0; i < ret.n; i++)
            ret[i] = p[i]+b[i];
    }

    Poly operator-(Poly b) const {
        Poly ret(max(n, b.n));

        for(int i = 0; i < ret.n; i++)
            ret[i] = p[i]-b[i];
    }

    Poly operator*(Poly b) const {
        Poly ret(n+b.n-1);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < b.n; j++)
                ret[i+j] += p[i]*b[j];

        return ret;
    }

    Poly operator*(T b) const {
        Poly ret = *this;
        for(int i = 0; i < n; i++)
            ret[i]*=b;
        return ret;
    }

    Poly operator%(Poly b) const {
        Poly ret(*this);
        b*=T(1)/b.p.back();

        for(int i = n-b.n; i >= 0; i--){
            T scale = ret[i+b.n-1];
            for(int j = 0; j < b.n; j++)
                ret[i+j]-=b[j]*scale;
        }

        ret.p.resize(b.n-1);
        ret.n = b.n-1;

        return ret;
    }

    void operator%=(Poly b) {
        (*this) = (*this) % b;
    }

    void operator+=(Poly b){
        (*this) = (*this) + b;
    }

    void operator-=(Poly b){
        (*this) = (*this) - b;
    }

    void operator*=(Poly b){
        (*this) = (*this) * b;
    }
    
    void operator*=(T b){
        (*this) = (*this) * b;
    }
};
