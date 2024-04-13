/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#endif

template<typename T>
vector<int> kmp(T s){
    vector<int> pi(s.size());
    pi[0] = -1;
    for(int i = 1; i < s.size(); i++){
        pi[i] = pi[i-1];
        while(pi[i] != -1 && s[pi[i]] != s[i]){
            pi[i] = pi[pi[i]];
        }
        pi[i]++;
    }
    pi[0] = 0;
    return pi;
}