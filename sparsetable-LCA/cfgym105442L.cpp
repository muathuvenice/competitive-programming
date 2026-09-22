#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
using namespace std;
#define F first
#define S second
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define REP(i, n) for(int i = 0, _n = (n); i < _n; ++i)
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
#define parity(x) __builtin_parity(x)
#define parityll(x) __builtin_parityll(x)
template<class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template<class X, class Y>
    bool maximize(X &x, Y y) {
        return x < y ? x = y, true : false;
    }
template <class T>
    void printVec(vector<T> &vec){
        for(T x : vec)cout << x << ' ';
        cout << '\n';
    }
const int mod = 1e9 + 7;
const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 1e5 + 5;

int n, par[maxN][17], d[maxN];
vector<int> adj[maxN];
void dfs(int u = 0, int p = -1){
    for(int v : adj[u]){
        if(v == p) continue;
        d[v] = d[u] + 1;
        par[v][0] = u;
        dfs(v, u);
    }
}
int lca(int u, int v){
    if(d[u] < d[v]) swap(u, v);
    FORD(i, 16, 0)if(d[par[u][i]] >= d[v]) u = par[u][i];
    if(u == v) return u;
    FORD(i, 16, 0) if(par[u][i] != par[v][i]){
        u = par[u][i];
        v = par[v][i];
    }
    return par[u][0];
}
int cnt[maxN][2];
void jump(int u, int v, int dist){
    // (d + 1) / 2
    if(d[u] < d[v]) swap(u, v);
    FORD(i, 16, 0)if(Bit(dist / 2, i)) u = par[u][i];
    cnt[u][dist & 1]++;
}
int f[maxN][2];
void dfsSolve(int u = 0, int p = -1){
    if(cnt[u][0]){
        f[u][0] = inf;
        f[u][1] = 1;
    }else{
        f[u][1] = 1;
        f[u][0] = 0;
    }
    for(int v : adj[u]){
        if(v == p) continue;
        dfsSolve(v, u);
        if(cnt[v][0] && cnt[v][1] == 0){
            f[u][0] += f[v][1];
            f[u][1] += f[v][1];
        }else if(cnt[v][0] && cnt[v][1]){
            f[u][0] += f[v][1];
            f[u][1] += f[v][1];
        }else if(cnt[v][0] == 0 && cnt[v][1] == 0){
            f[u][0] += min(f[v][0], f[v][1]);
            f[u][1] += min(f[v][0], f[v][1]);
        }else{
            // cnt[v][0] = 0, cnt[v][1] > 0
            f[u][0] += f[v][1];
            f[u][1] += min(f[v][0], f[v][1]);
        }
        minimize(f[u][0], inf);
        minimize(f[u][1], inf);
    }
}
int q;
void fuck(){
    cin >> n >> q;
    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    FOR(j, 1, 16)REP(i, n) par[i][j] = par[par[i][j - 1]][j - 1];
    while(q--){
        int u, v;
        cin >> u >> v;
        int p = lca(u, v);

        jump(u, v, d[u] + d[v] - 2 * d[p]);
    }
    dfsSolve();
    cout << min(f[0][0], f[0][1]);
}
int main(){
    #define LOVE "cat"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}




