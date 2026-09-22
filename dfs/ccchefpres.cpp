#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
#define Bit(x, i) ((x >> (i)) & 1)
#define Mask(i) (1 << (i))
#define Cnt(x) __builtin_popcount(x)
#define Cntll(x) __builtin_popcountll(x)
#define Ctz(x) __builtin_ctz(x)
#define Ctzll(x) __builtin_ctzll(x)
#define Clz(x) __builtin_clz(x)
#define Clzll(x) __builtin_clzll(x)
inline bool maximize(int &u, int v){ return v > u ? u = v, true : false; }
inline bool minimize(int &u, int v){ return v < u ? u = v, true : false; }
inline bool maximizell(long long &u, long long v){ return v > u ? u = v, true : false; }
inline bool minimizell(long long &u, long long v){ return v < u ? u = v, true : false; }
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){ u += v; if(u >= mod) u -= mod; }
inline void sub(int &u, int v){ u -= v; if(u < 0) u += mod; }
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, B, k, q;
vector<int> adj[maxN];
int f[maxN], d[maxN][101];
void dfs(int u = B, int p = 0){
    d[u][f[u]] = u;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v, u);
        FOR(x, 1, k)if(d[u][x] == -1 || (d[u][x] > d[v][x] && d[v][x] != -1)) d[u][x] = d[v][x];
    }
}
void dfs2(int u = B, int p = 0){
    for(int v : adj[u]){
        if(v == p) continue;
        FOR(x, 1, k){
            if(d[v][x] == -1)d[v][x] = d[u][x];
        }
        dfs2(v, u);
    }
}

void process(){
    cin >> n >> k >> B;
    FOR(i, 2, n){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    FOR(i, 1, n)cin >> f[i];
    FOR(i, 1, n)FOR(x, 1, k)d[i][x] = -1;
    dfs();
    dfs2();
    cin >> q;
    while(q--){
        int a, x;
        cin >> a >> x;
        cout << d[a][x] << '\n';
    }
}
/*
8 5 8
3 2
2 1
1 8
8 6
8 7
7 4
4 5
3 5 3 4 1 1 4 5
5
2 1
2 3
4 4
7 4
5 2
*/
#define LOVE "kingdom"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}




