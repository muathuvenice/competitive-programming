#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
const int mod = 1e9 + 7;
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
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
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
int n;
vector<int> adj[maxN];
int f[maxN][2];
void dfs(int u = 1, int pre = 0){
    int numChild = 0;
    for(int v : adj[u]){
        if(v != pre){
            dfs(v, u);
            ++numChild;
        }
    }
    f[u][0] = numChild;
    f[u][1] = numChild + (pre > 0);
    for(int v : adj[u]){
        if(v != pre){
            maximize(f[u][1], f[u][0] + f[v][0] - 1 + (pre > 0));
            maximize(f[u][0], f[v][0] + numChild - 1);
        }
    }
}
void process(){
    cin >> n;
    FOR(i, 1, n)adj[i].clear();
    FOR(i, 2, n){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    int answer = 0;
    FOR(i, 1, n)maximize(answer, max(f[i][0], f[i][1]));
    cout << answer << '\n';
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
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}


