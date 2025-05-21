/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Let pi(s) := size of the biggest proper prefix of s that is
 * also a suffix of s.
 * 
 * kmp(s) calculates pi(s[0..i]) for all i from 0 to n-1 in O(n)
 * 
 * Useful for multiple applications, for example string matching.
 * 
 * Also has a function that finds the automaton corresponding
 * to how the prefix function will change. Formally:
 * 
 * kmp_automaton<ALPHA,INI>(s)[p][c-INI] := pi(s+"#"+t+"c") given that
 * pi(s+"#"+t) = p, the alphabet size is ALPHA and the smallest character 
 * is INI.
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif


template<typename T>
vector<int> kmp(const T s){
    vector<int> pi(s.size());
    for(int i = 1; i < s.size(); i++){
        pi[i] = pi[i-1];
        while(pi[i] != 0 && s[pi[i]] != s[i]){
            pi[i] = pi[pi[i]-1];
        }
        pi[i]+=s[i]==s[pi[i]];
    }
    return pi;
}

template<int ALPHA = 26, int INI = 'a'>
vector<array<int,ALPHA>> kmp_automaton(const string s){
    vector<int> pi = kmp(s);
    vector<array<int,ALPHA>> ret(s.size()+1);

    ret[0][s[0]-INI] = 1;
    for(int i = 1; i < s.size(); i++){
        ret[i] = ret[pi[i-1]];
        ret[i][s[i]-INI] = i+1;
    }
    ret.back() = ret[pi.back()];

    return ret;
}