#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
inline bool maximize(int &u, int v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimize(int &u, int v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
inline bool maximizell(long long &u, long long v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimizell(long long &u, long long v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 2e5 + 5;
const int inf = 2e9;
const long long infll = 1e18;
vector<int> adj[maxN];
int n, a[maxN], f[maxN];
void dfs(int u){
    if(adj[u].empty()){
        f[u] = a[u];
        return;
    }
    int mn = inf;
    for(int v : adj[u]){
        dfs(v);
        minimize(mn, f[v]);
    }
    if(a[u] >= mn)f[u] = mn;
    else f[u] = a[u] + mn >> 1;
}
void process(){
    cin >> n;
    FOR(i, 1, n){
        cin >> a[i];
        adj[i].clear();
    }
    FOR(i, 2, n){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    int mn = inf;
    for(int v : adj[1]){
        dfs(v);
        minimize(mn, f[v]);
    }
    cout << a[1] + mn << '\n';
}
#define NAME ""
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



