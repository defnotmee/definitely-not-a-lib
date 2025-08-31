/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Implements arithmetic operations with arbitrary precision integers.
 * 
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

template<ll B = 10>
struct Big{
    static_assert(B >= 1);

    vector<ll> v;
    bool minus = 0;

    Big(ll x = 0) {
        if(x < 0)
            minus = 1, x*=-1;
        while(x){
            v.push_back(x%B);
            x/=B;
        }
        if(v.empty())
            v.push_back(0);
    }
    
    void trim(){
        while(v.size() > 1 && v.back() == 0)
            v.pop_back();
    }

    Big(string s){
        static_assert(B <= 10);
        reverse(all(s));
        if(s.back() == '-')
            minus = 1, s.pop_back();
        for(int i = 0; i < s.size(); i++)
            v.push_back(s[i]-'0');
        trim();
    }

    /**
     * Converts an Big Integer from base A to base B 
     * 
     * ASSUMES THAT A IS A POWER OF B OR VICE VERSA
     * 
     * Useful for speeding up operations (for example,
     * doing multiplication in base 10^9 is 81x faster than
     * base 10)
     * */
    template<ll A>
    Big(Big<A> x){
        minus = x.minus;
        if(A == B){
            v = x.v;
            return;
        }
        if(A < B){
            v.push_back(0);
            ll cur = 1;
            for(ll i = 0; i < x.v.size(); i++){
                v.back()+=cur*x.v[i];
                cur*=A;
                if(cur == B)
                    cur = 1, v.push_back(0);
            }
            trim();
        } else {
            for(int i = 0; i < x.v.size(); i++){
                ll cur = 1;
                while(cur != A){
                    v.push_back(x.v[i]%B);
                    x.v[i]/=B;
                    cur*=B;
                }
            }
            trim();
        }
    }

    void extend(int sz){
        if(v.size() < sz)
            v.resize(sz);
    }

    Big& operator+=(Big& o){
        if(minus == o.minus){
            extend(o.v.size());
            o.extend(v.size());
            v.push_back(0);
            for(int i = 0; i < o.v.size(); i++){
                v[i]+=o.v[i];
                v[i+1]+=v[i]/B;
                v[i]%=B;
            }
            trim();
        }
        return *this;
    };

    Big& operator-=(Big o){
        o.minus^=1;
        return *this += o;
    }

    Big operator+(Big o){
        Big x;
        return x+=o;
    }

    Big operator-(Big o){
        Big x;
        return x-=o;
    }

    Big operator*(Big o) const {
        Big ret;
        ret.extend(v.size()+o.v.size());
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < o.v.size(); j++){
                ret.v[i+j]+=v[i]*o.v[j];
                ret.v[i+j+1]+=ret.v[i+j]/B;
                ret.v[i+j]%=B;
            }
        }
        ret.trim();
        return ret;
    }

    friend istream& operator>>(istream& in, Big& x){
        string s;
        in >> s;
        x = Big(s);
        return in;
    }

    friend ostream& operator<< (ostream& out, Big& x){
        x.trim();
        if(x.minus)
            out << '-';
        for(int i = int(x.v.size())-1; i >= 0; i--){
            out << x.v[i];
        }
        return out;
    }
};