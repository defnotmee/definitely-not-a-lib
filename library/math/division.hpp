/**
 * from https://github.com/defnotmee/definitely-not-a-lib
 * 
 * Integer division with ceil and floor that works for
 * potentially negative numbers
 */

#ifndef O_O
#include"../utility/template.cpp"
#endif

ll div_floor(ll a, ll b){
    return a/b-(a%b!=0 && (a^b)<0);
}
ll div_ceil(ll a, ll b){
    return a/b+(a%b!=0 && (a^b)>0);
}
