/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Basic RNG functionality. High quality.
 */
#ifndef O_O
#include"../utility/template.cpp"
#endif

const int SEED = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(SEED);

// Returns random integer from l to r.
int range(int l, int r){ 
    return uniform_int_distribution<int>(l,r)(rng);
}