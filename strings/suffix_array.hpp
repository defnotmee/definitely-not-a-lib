/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"template.cpp"
#endif

struct SuffixArray{
    int n;
    vector<int> sa, rnk;


    SuffixArray(string& s) : n(s.size()), sa(n), rnk(n+1,-1){ 
        for(int i = 0; i < n; i++){
            rnk[i] = s[i];
        }
        iota(all(sa),0);

        for(int k = -1; (1<<k) < n; k++){
            int off = k == -1 ? 0 : 1<<k;

            vector<pii> lookup(n);
            vector<int> ct(max(256,n));
            vector<int> nsa(n);

            for(int i = 0; i < n; i++){
                ct[rnk[i]]++;
                lookup[i] = {rnk[i], rnk[min(n,i+off)]};
            }

            vector<int> ps = ct;
            for(int i = 1; i < ps.size(); i++)
                ps[i]+=ps[i-1];
            
            for(int i = n-off; i < n; i++)
                nsa[ps[rnk[i]]-(ct[rnk[i]]--)] = i;
            
            for(int i = 0; i < n; i++){
                if(sa[i] >= off){
                    int id = sa[i]-off;
                    nsa[ps[rnk[id]]-(ct[rnk[id]]--)] = id;
                }
            }

            swap(sa,nsa);
            rnk[sa[0]] = 0;

            for(int i = 1; i < n; i++)
                rnk[sa[i]] = rnk[sa[i-1]]+(lookup[sa[i]] != lookup[sa[i-1]]);
        }
        rnk.pop_back();
    }
};

struct LCP : SuffixArray{ // untested

    vector<int> lcp;

    matrix<int> sparse;

    LCP(string& s) : SuffixArray(s), lcp(s.size()){
        for(int i = 0; i < s.size(); i++){
            if(rnk[i]+1 == s.size()){
                lcp[i] = 0;
                continue;
            }
            int nxt = sa[rnk[i]+1];

            while(i+lcp[i] < s.size() && nxt+lcp[i] < s.size() && s[i+lcp[i]] == s[nxt+lcp[i]])
                lcp[i]++;
            
            if(i+1 < s.size())
                lcp[i+1] = max(0,lcp[i]);
        }
    }
};