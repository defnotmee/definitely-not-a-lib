/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

template<int ALPHA = 26, int INI = 'a'>
struct SuffixAutomaton {
    struct state{
        int len, link;
        array<int, ALPHA> ptr;

        state(int len = 0, int link = -1) : len(len), link(link){
            fill(all(ptr),-1);
        }
    };

    vector<node> sa;
    int last = 0;

    SuffixAutomaton(){
        sa = {{}};
    }

    void extend(int c){
        c-=INI;
        int nxt = sa.size();
        sa.push_back({sa[last].len+1});

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

};