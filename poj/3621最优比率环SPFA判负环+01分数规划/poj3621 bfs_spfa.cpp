#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std ;
const int maxn = 1010 ;
const int zhf = 1000000000 ;
struct node {
    int v, w ;
} ;
vector <node> g[maxn] ;
int n, m, s[maxn], cnt[maxn] ; //SPFA判环需要记录点出现次数
double d[maxn] ;
bool p[maxn] ;
bool spfa ( double ans ) {
    queue <int> q ;
    memset ( cnt, 0, sizeof(cnt) ) ;
    memset ( p, 0, sizeof(p) ) ;
    int i, j, k, u, v, w ;
    for ( i = 1 ; i <= n ; i ++ ) 
        d[i] = zhf * 1.0 ;
    p[1] = 1 ; d[1] = 0.0 ;
    q.push(1) ; 
    while ( !q.empty() ) {
        int u = q.front() ;
        p[u] = 0 ;
        q.pop() ;
        for ( i = 0 ; i < g[u].size() ; i ++ ) {
            v = g[u][i].v ;
            double wei = ans * g[u][i].w - s[v] * 1.0 ; //方程见上
            if ( d[v] > wei + d[u] ) {
                d[v] = wei + d[u] ;
                if ( !p[v] ) {
                    p[v] = 1 ;
                    if ( ++cnt[v] > n ) return true ;
                    q.push(v) ;
                }
            }
        }
    }
    return false ;
}
int main () {
    int i, j, k, u, v, w ;
    int sum = 0 ; 
    scanf ( "%d%d", &n, &m ) ;
    for ( i = 1 ; i <= n ; i ++ ) {
        scanf ( "%d", s + i ) ;
        sum += s[i] ;
    }
    for ( i = 1 ; i <= m ; i ++ ) {
        scanf ( "%d%d%d", &u, &v, &w ) ;
        g[u].push_back( (node) {v,w} ) ;
    }
    double mid, l = 0.0, r = sum * 1.0, ans ; 
    while ( (r-l) > 1e-3 ) { // 二分答案
        mid = ( r + l ) * 1.0 / 2 ;
        if ( spfa(mid) ) {
            l = mid ;
            ans = mid ;
        }
        else r = mid ;
    }
    printf ( "%.2f\n", ans ) ;
    return 0 ;
}
