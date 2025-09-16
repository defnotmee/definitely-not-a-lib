/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Given a string/vector s, finds all the indices of all
 * lexicographically minimum rotations of s in O(nlogn).
 * 
 * That way, rotate(s.begin(),s.begin()+min_rot(s)[0], s.end())
 * will transform s into a lexicographically minimum rotation.
 * 
 * Note that the largest perfect period of a string of size n will be
 * n/min_rot(s).size()
 */

#ifndef O_O
#include"../utility/template.cpp"
#endif

vector<int> min_rot(auto s){
    int n = s.size();
    vector<int> cand;
    auto mn = *min_element(all(s));
    vector<int> is_cand(n);
    for(int i = 0; i < n; i++)
        if(s[i] == mn)
            cand.push_back(i), is_cand[i] = 1;
    int k = 1;
    while(true){
        auto mn = s[(cand[0]+k)%n];
        for(int i : cand)
            mn = min(mn, s[(i+k)%n]);

        for(int i : cand){
            is_cand[(i+k)%n] = 0;
            if(s[(i+k)%n] != mn)
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
