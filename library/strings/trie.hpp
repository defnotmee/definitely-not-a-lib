/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<int ALPHA = 26, int INI = 'a'>
struct Trie {
    public:
    struct node{
        array<int,ALPHA> ptr;
        int term; // number of strings that terminate on the node
        int sub;  // number of strings in the subtree of the node

        constexpr node() : term(0), sub(0){
            for(int i = 0; i < ALPHA; i++)
                ptr[i] = -1;
        }
    };
    vector<node> trie;

    Trie(int expected = MAXN) : trie(1) {
        trie.reserve(expected);
    }

    void insert(string& s, int ct = 1){
        int id = 0;
        int pos = 0;
        while(pos < s.size()){
            char cur = s[pos]-INI;
            if(trie[id].ptr[cur] == -1)
                trie[id].ptr[cur] = trie.size(), trie.push_back({});
            trie[id].sub+=ct;
            id = trie[id].ptr[cur];
            pos++;
        }
        trie[id].sub += ct;
        trie[id].term += ct;
    }

    int find(string& s){
        int id = 0, pos = 0;
        while(pos < s.size()){
            char cur = s[pos]-INI;
            if(trie[id].ptr[cur] == -1)
                return -1;
            id = trie[id].ptr[cur];
            pos++;
        }
        return id;
    }
};