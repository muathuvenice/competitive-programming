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
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
struct Fenwick{
    vector<int> fw;
    int n;
    Fenwick(int _n = 0){
        n = _n;
        fw.assign(n + 1, 0);
    }
    int get(int x){
        int res = 0;
        for(; x >= 1; x &= x - 1) res += fw[x];
        return res;
    }
    int get(int l, int r){
        if(l > r) return 0;
        return get(r) - get(l - 1);
    }
    void update(int x, int v){
        for(; x <= n; x += x & -x) fw[x] += v;
    }
}fw;
int n, m, q;
bool connected[maxN];
int par[maxN][17];
vector<int> adj[maxN];
pair<int, int> edge[maxN];
int in[maxN], out[maxN], timeDfs;
void dfs(int u = 1, int p = 0){
    in[u] = ++timeDfs;
    for(int v : adj[u]){
        if(v == p) continue;
        par[v][0] = u;
        dfs(v, u);
    }
    out[u] = timeDfs;
}
int res[maxN], same[maxN];
int find_root(int u){
    FORD(i, 16, 0) if(par[u][i]){
        if(fw.get(in[par[u][i]] + 1, in[u]) == Mask(i)){
            u = par[u][i];
        }
    }
    return u;
}
void process(){
    cin >> n >> m >> q;
    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        edge[i] = mp(u, v);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    FOR(j, 1, 16)FOR(i, 1, n)par[i][j] = par[par[i][j - 1]][j - 1];
    fw = Fenwick(n);
    FOR(i, 1, n)res[i] = 1;
    while(m--){
        int id;
        cin >> id;
        auto[u, v] = edge[id];
        if(in[u] > in[v]) swap(u, v);
        u = find_root(u);
        if(!connected[id]){
            res[u] = res[v] + res[u] - same[id];
            fw.update(in[v], 1);
            fw.update(out[v] + 1, -1);
        }else{
            same[id] = res[v] = res[u];
            fw.update(in[v], -1);
            fw.update(out[v] + 1, 1);
        }
        connected[id] ^= 1;
    }
    while(q--){
        int u;
        cin >> u;
        cout << res[find_root(u)] << '\n';
    }
}
#define LOVE "code"
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





