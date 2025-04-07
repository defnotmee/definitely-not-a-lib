/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Given a string/vector s, finds all the lexicographically minimum
 * rotations of s in O(nlogn)
 */

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T> 
vector<int> min_rot(T v){
    int n = v.size();
    vector<int> cand;
    auto mn = *min_element(all(v));
    for(auto i : v)
        if(i == mn)
            cand.push_back(i);

    vector<int> is_cand(n);
    for(int i : cand)
        is_cand[i] = 1;

    int k = 1;
    while(true){
        auto mn = v[(cand[0]+k)%n];

        for(int i : cand){
            is_cand[(i+k)%n] = 0;
            if(v[(i+k)%n] != mn)
                is_cand[i] = 0;
        }
        vector<int> newcand;

        for(int i : cand)
            if(is_cand[i])
                newcand.push_back(i);
        
        if(newcand.empty())
            return cand;
        
        swap(cand,newcand);

        k++;
    }
}