/*
from https://github.com/defnotmee/definitely-not-a-lib

Example of a generator for stress.sh
*/

#include<bits/stdc++.h>
#define all(x) begin(x), end(x)
#define ff first
#define ss second
#define O_O
using namespace std;
template <typename T>
using bstring = basic_string<T>;
template <typename T>
using matrix = vector<vector<T>>;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef double dbl;
typedef long double dbll; 
const ll INFL = 4e18+25;
const int INF = 1e9+42;
const double EPS = 1e-7;
const int MOD = (1<<23)*17*7 + 1; // 998244353
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const int MAXN = 1e6+1;

mt19937 rng;

int range(int l, int r){
    return uniform_int_distribution<>(l,r)(rng);
}

int main(int argc, char ** argv){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    rng.seed(atoi(argv[1]));
    int n = range(1,5), m = range(1,5), k = range(0,n*m);

    cout << n << ' ' << m << ' ' << k << endl;
    
    return 0;

}