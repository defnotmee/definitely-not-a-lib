/*
from https://github.com/defnotmee/definitely-not-a-lib

Unordered map with strong hash.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif


struct Hasher{
    ull operator()(ull x){
        // http://xorshift.di.unimi.it/splitmix64.c
        x+=0x9e3779b97f4a7c15;
        x = (x^(x>>30)) * 0xbf58476d1ce4e5b9;
        x = (x^(x>>27)) * 0x94d049bb133111eb;
        return x^(x>>31)^RANDOM; // for random seed, delete if lazy
    }
};

using hashmap = unordered_map<ull,Hasher>;