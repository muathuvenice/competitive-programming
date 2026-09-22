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
const int maxN = 4e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, q;
vector<int> adj[maxN];
int in[maxN], out[maxN], tour[maxN], cnt, c[maxN];
void dfs(int u = 1, int p = 0){
    in[u] = ++cnt;
    tour[cnt] = u;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v, u);
    }
    out[u] = cnt;
}
#define ll long long
ll it[maxN << 2];
void build(int id, int l, int r){
    if(l == r){
        it[id] = 1ll << (c[tour[l]] - 1);
        return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = it[id << 1] | it[id << 1 | 1];
}
ll lz[maxN << 2];
void push(int id){
    if(lz[id] == 0) return;
    it[id << 1] = it[id << 1 | 1] = lz[id << 1] = lz[id << 1 | 1] = lz[id];
    lz[id] = 0;
    return;
}
void update(int id, int l, int r, int u, int v, int x){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        it[id] = 1ll << x - 1;
        lz[id] = 1ll << x - 1;
        return;
    }
    push(id);
    int mid = l + r >> 1;
    update(id << 1, l, mid, u, v, x);
    update(id << 1 | 1, mid + 1, r, u, v, x);
    it[id] = it[id << 1] | it[id << 1 | 1];
}
long long get(int id, int l, int r, int u, int v){
    if(l >= u && r <= v) return it[id];
    int mid = l + r >> 1;
    push(id);
    if(v <= mid) return get(id << 1, l, mid, u, v);
    if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
    return get(id << 1, l, mid, u, v) | get(id << 1 | 1, mid + 1, r, u, v);
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n)cin >> c[i];
    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    build(1, 1, n);
    while(q--){
        int t, u;
        cin >> t >> u;
        if(t == 1){
            int c;
            cin >> c;
            update(1, 1, n, in[u], out[u], c);
        }else{
            long long answer = get(1, 1, n, in[u], out[u]);
            cout << Cntll(answer) << '\n';
        }
    }
}
#define LOVE "code"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
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






