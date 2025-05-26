/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

vector<int> manacher(string in){
    string s = "#";

    for(char i : in)
        s+=i + string("#");

    int n = s.size();

    vector<int> ret(n);

    int mid = 0, r = 0;

    for(int i = 1; i < n-1; i++){
        if(i < r)
            ret[i] = min(r-i, ret[mid*2-i]);
        
        while(ret[i] <= i && i+ret[i] < n && s[i-ret[i]] == s[i+ret[i]])
            ret[i]++;

        if(i+ret[i] > r)
            mid = i, r = i+ret[i];
    }

    return vector<int>(1+all(ret)-1);
}