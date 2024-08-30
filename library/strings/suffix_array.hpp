/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

struct SuffixArray{
    int n;
    string s;
    vector<int> sa, rnk;
 
    SuffixArray(string& s) : s(s), n(s.size()), sa(n), rnk(n+1,-1){
        for(int i = 0; i < n; i++)
            rnk[i] = s[i];
        
        iota(all(sa),0);
 
        for(int k = -1; k == -1 || (1<<k) <= n; k++){
            int off = k == -1 ? 0 : (1<<k);
 
            vector<pii> lookup(n);
            vector<int> ct(max(256, n));
            vector<int> nsa(n);
 
            for(int i  =0; i < n; i++){
                ct[rnk[i]]++;
                lookup[i] = {rnk[i], rnk[min(n,i+off)]};
            }
 
            vector<int> ps = ct;
 
            for(int i = 1; i < ps.size(); i++)
                ps[i]+=ps[i-1];

            auto aux =[&](int id){
                nsa[ps[rnk[id]] - (ct[rnk[id]]--)] = id;
            };

            for(int i = n-off; i < n; i++)
                aux(i);
            
            for(int i = 0; i < n; i++)
                if(sa[i] >= off)
                    aux(sa[i]-off);

 
            swap(sa,nsa);
 
            rnk[sa[0]] = 0;
 
            for(int i = 1; i < n; i++)
                rnk[sa[i]] = rnk[sa[i-1]]+(lookup[sa[i]] != lookup[sa[i-1]]);
            
        }
 
        rnk.pop_back();
        
    }
};
 
struct LCP : SuffixArray{
    vector<int> lcp;
 
    matrix<int> sparse;
 
    LCP(string& s) : SuffixArray(s), lcp(n), sparse(int(log2(n)+1), vector<int>(n)) {        
 
        for(int i = 0; i < n; i++){
            int& clcp = lcp[rnk[i]];
            if(rnk[i]+1 == n){
                clcp = 0;
                continue;
            }
            int nxt = sa[rnk[i]+1];
            
            while(i+clcp < n && nxt+clcp < n && s[i+clcp] == s[nxt+clcp]){
                clcp++;
            }
            
            if(i+1 < n)
                lcp[rnk[i+1]] = max(0,clcp-1);
        }
 
        sparse[0] = lcp;
 
        for(int i = 1; i < sparse.size(); i++){
            for(int j = 0; j + (1<<i) <= n; j++){
                sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j+(1<<i-1)]);
            }
        }
    }
    
    // returns the lcp between s[sa[l]..n] and s[sa[r]..n]
    int get_lcp_sa(int l, int r){
        if(l > r)
            swap(l,r);
        r--;
        int logg = log2(r-l+1);
        return min(sparse[logg][l], sparse[logg][r-(1<<logg)+1]);
    }

    // returns lcp between s[l..n] and s[r..n]
    int get_lcp(int l, int r){
        return get_lcp_sa(rnk[l], rnk[r]);
    }

    void debug(){
        for(int i = 0; i < s.size(); i++){
            cerr << i << ": " << "sa[i] = " <<sa[i] << ", suffix = " << s.substr(sa[i]) << ", lcp = " << lcp[i] << '\n';
        }
    }
};
