/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

vector<int> z_function(auto s){
    int n = s.size();
    int l = 0, r = 0;
    vector<int> z(n);
    for(int i = 1; i < n; i++){
        if(i < r)
            z[i] = min(r-i, z[i-l]);
        while(i + z[i] < n && s[i+z[i]] == s[z[i]])
            z[i]++;
        if(i+z[i] > r)
            l = i, r = i+z[i];
    }
    return z;
}
