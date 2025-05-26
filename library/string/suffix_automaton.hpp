/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

template<int ALPHA = 26, int INI = 'a'>
struct SuffixAutomaton {
    struct state{
        int len, firstpos, link = -1, is_clone = 0;
        array<int, ALPHA> ptr;

        state(int len = 0, int firstpos = -1)
            : len(len), firstpos(firstpos){
            fill(all(ptr),-1);
        }
    };

    vector<state> sa;
    int last = 0;
    int ct = 0;
    SuffixAutomaton(){
        sa = {{}};
    }

    void extend(int c){
        c-=INI;
        int nxt = sa.size();
        sa.push_back({sa[last].len+1, ct++});

        int pivot = last;

        while(pivot != -1 && sa[pivot].ptr[c] == -1)
            sa[pivot].ptr[c] = nxt, pivot = sa[pivot].link;

        if(pivot == -1){
            sa[nxt].link = 0;
        } else {
            int tmp = sa[nxt].link = sa[pivot].ptr[c];
            if(sa[tmp].len != sa[pivot].len+1){
                int nlink = sa[nxt].link = sa.size();
                sa.push_back(sa[tmp]);
                sa.back().len = sa[pivot].len+1;
                sa.back().is_clone = 1;
                int tmp = sa[pivot].ptr[c];
                sa[tmp].link = nlink;
                
                while(pivot != -1 && sa[pivot].ptr[c] == tmp){
                    sa[pivot].ptr[c] = nlink;
                    pivot = sa[pivot].link;
                }
            }
        }
        last = nxt;
    }

    SuffixAutomaton(string s){
        sa = {{}};
        sa.reserve(2*s.size());
        for(char i : s)
            extend(i);

    }

    bool accept(string s){
        int id = 0;

        for(char i : s){
            id = sa[id].ptr[i-INI];
            if(id == -1)
                return 0;
        }
        return 1;
    }

    vector<int> get_ct(){
        vector<int> ct(sa.size());
        vector<bstring<int>> rslink(sa.size());

        for(int i = 1; i < sa.size(); i++){
            rslink[sa[i].link].push_back(i);
        }

        auto dfs =[&](int id, auto && dfs) -> void {
            ct[id] = !sa[id].is_clone;

            for(int i : rslink[id])
                dfs(i,dfs), ct[id]+=ct[i];
        };

        dfs(0,dfs);

        return ct;
    }

    state& operator[](int id){
        return sa[id];
    }

    int size(){
        return sa.size();
    }
};