/*
from https://github.com/defnotmee/definitely-not-a-lib

Given an array of ancestors (next), is able to get information
about starting on a certain node and going to the ancestor of the
current node k steps in a row in O(log(k)) per query. Is able to work with
any functional graph, but the lca function just works for trees.

Usage: 

- BinLift(next): constructs the structure. next is assumed to be 0-indexed
- lift: an auxiliary class that stores information about the path (for example
what is the maximum edge on the path). By default only stores the vertex you will end
up in after going up a certain number of times.
- k_up(id,k): returns a lift structure of starting on id and going to the ancestor
k times in a row. 
- lca(a,b,h): assuming the functional graph given is a tree, if h is a vector representing
the height of the nodes in a tree, returns the lift structure of the path between a and b.
The .to member of the return value will be the lca between a and b. If you are storing more
information about the path, it needs to be commutative (for example, you can store max).
*/

#ifndef O_O
#include"../../utility/template.cpp"
#endif

struct BinLift{
    
    int n, lg;

    struct lift{
        int to = 0;
    };

    // what happens when you go through a, and then go through b?
    static lift merge(lift a, lift b){
        return {b.to};
    }

    matrix<lift> jmp;

    BinLift(vector<int> next) : n(next.size()), lg(1){

        for(int tmp = 1; tmp < n; tmp*=2, lg++);

        jmp = matrix<lift>(lg,vector<lift>(next.size()));
        
        // initialize jmp[0][i]
        for(int i = 0; i < next.size(); i++)
            jmp[0][i] = {next[i]};


        for(int i = 1; i < lg; i++){
            for(int j = 0; j < next.size(); j++){
                jmp[i][j] = merge(jmp[i-1][j], jmp[i-1][jmp[i-1][j].to]);
            }
        }
    }

    lift k_up(int id, int k){
        lift ret{id}; // needs to be an identity element through merge
        while(k){
            ret = merge(ret, jmp[__builtin_ctz(k)][ret.to]);
            k-=k&-k;
        }
        return ret;
    }

    lift lca(int a, int b, vector<int>& h){
        if(h[a] < h[b])
            swap(a,b);
        
        int d = h[a]-h[b];
        lift la = k_up(a,d), lb = {b}; // needs to be an identity element through merge

        if(la.to == lb.to)
            return la;
        
        for(int i = lg-1; i >= 0; i--){
            if(jmp[i][la.to].to != jmp[i][lb.to].to)
                la = merge(la,jmp[i][la.to]), lb = merge(lb,jmp[i][lb.to]);
        }

        la = merge(la, jmp[0][la.to]);
        lb = merge(lb, jmp[0][lb.to]);


        return merge(la,lb);
    }

};