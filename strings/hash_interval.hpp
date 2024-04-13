/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#endif

template<ull M = MOD>
struct Hasher{
    vector<ull> psum, power;

    Hasher(string& s, ull c = 123){
        psum = vector<ull>(s.size()+1);
        power = vector<ull>(s.size()+1,1);
        for(int i = 1; i < power.size(); i++)
            power[i] = power[i-1]*c%M;
        for(int i = 1; i < psum.size(); i++)
            (psum[i] = psum[i-1]*c+s[i-1])%=M;
    }

    ull sub_hash(int l, int r){
        return (psum[r+1]-psum[l]*power[r-l+1]%M+M)%M;
    }
    ull hash(){
        return psum.back();
    }
};