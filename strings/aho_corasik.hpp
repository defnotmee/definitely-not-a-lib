/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"trie.hpp"
#include"template.cpp"
#endif

template<int ALPHA = 26, int INI = 'a'>
struct SuperTrie : Trie<ALPHA, INI>{
    vector<int> in_suffix, slink, pai, paic, match;
    using Trie<ALPHA,INI>::trie;
    vector<bstring<int>> rslink;

    SuperTrie(int expected = MAXN) : Trie<ALPHA, INI>(MAXN){
        trie[0].term = 0;
    }

    int next(int id, int c){
        while(id && trie[id].ptr[c] == -1)
            id = slink[id];
        if(trie[id].ptr[c] != -1)
            id = trie[id].ptr[c];
        return id;
    }

    void calc_link(){
        in_suffix = slink = pai = paic = match = vector<int>(trie.size());
        rslink = vector<bstring<int>>(trie.size());
        queue<int> q;

        q.push(0);

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(int c = 0; c < ALPHA; c++){
                int viz = trie[cur].ptr[c];
                if(viz == -1)
                    continue;
                pai[viz] = cur;
                paic[viz] = c;
                q.push(viz);
            }
            if(!cur)
                continue;

            slink[cur] = next(slink[pai[cur]], paic[cur]);
            slink[cur] = (slink[cur] != cur)*slink[cur];
            rslink[slink[cur]].push_back(cur);

            in_suffix[cur] = in_suffix[slink[cur]]+trie[cur].term;
        }
    }

    void add_str(string& s, int ct = 1){
        int id = 0;
        int sid = 0;

        while(sid < s.size()){
            int c = s[sid] - INI;
            id = next(id,c);
            match[id] += ct;
            sid++;
        }
    }

    void calc_match(int id = 0){
        for(int i : rslink[id]){
            calc_match(i);
            match[id]+=match[i];
        }
    }



};