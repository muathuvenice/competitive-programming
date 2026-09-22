#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
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
#define left __left
#define down __down
#define right __right
#define up __up
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
const int maxN = 5000 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n;
vector<pair<int, int>> adj[maxN];
int sz[maxN];
long long init = 0;
long long f[maxN];
void preDfs(int u, int p){
    sz[u] = 1;
    for(auto[v, w] : adj[u]){
        if(v == p) continue;
        preDfs(v, u);
        init += 1ll * sz[u] * f[v] + 1ll * sz[v] * f[u] + 1ll * w * sz[u] * sz[v];
        f[u] += f[v] + 1ll * w * sz[v];
        sz[u] += sz[v];
    }
}
long long in[maxN], out[maxN];
void dfs(int u, int p){
    in[u] = 0, out[u] = 0;
    sz[u] = 1;
    for(auto [v, w] : adj[u]){
        if(v == p) continue;
        dfs(v, u);
        in[u] += in[v] + 1ll * w * sz[v];
        sz[u] += sz[v];
    }
}
void dfsOut(int u, int p, long long &answer, int root){
    minimizell(answer, in[u] + out[u]);
    for(auto [v, w] : adj[u]){
        if(v == p) continue;
        out[v] = out[u] + 1ll * w * (sz[root] - sz[v]) + in[u] - (in[v] + 1ll * w * sz[v]);
        dfsOut(v, u, answer, root);
    }
}
long long calc(int u, int v){
    dfs(u, v);
    dfs(v, u);
    long long answer = init - (in[u] * sz[v] + in[v] * sz[u]);
    long long Left = infll, Right = infll;
    dfsOut(u, v, Left, u);
    dfsOut(v, u, Right, v);
    answer += Left * sz[v] + Right * sz[u];
    return answer;
}
pair<int, int> edge[maxN];
void process(){
    cin >> n;
    FOR(i, 1, n - 1){
        int u, v, w;
        cin >> u >> v >> w;
        edge[i] = mp(u, v);
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    preDfs(1, 0);
    long long answer = init;
//    calc(3, 4);
    long long Max = 0;
    FOR(i, 1, n - 1){
        auto[u, v] = edge[i];
        minimizell(answer, calc(u, v));
    }
    cout << answer;
}
#define LOVE "didoi"
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





