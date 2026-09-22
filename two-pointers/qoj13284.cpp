/*
  Competitive Programming - FULL TEMPLATE
  Filename: Competitive_Template_Full_2000.cpp
  Contents: large single-file template with many utilities:
    - fast IO, macros, typedefs
    - math utils, modular arithmetic, factorials, nCr
    - sieve, prime checks, SPF
    - FFT (iterative) placeholder
    - DSU, BIT, Segment Tree (iterative + lazy), Fenwick
    - Persistent segtree (skeleton)
    - Graph: BFS, DFS, Dijkstra, Bellman-Ford, SPFA, Kruskal, Prim
    - LCA (binary lifting), Euler tour, HLD (skeleton)
    - Dinic maxflow
    - Matrix exponentiation
    - Geometry utilities (point, cross, dot, orientation)
    - Random helpers, debug, timing
    - Template problem 'process()' placeholder to integrate your solution
   Use under GNU++17 or later.
*/
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
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){ u += v; if(u >= mod) u -= mod; }
inline void sub(int &u, int v){ u -= v; if(u < 0) u += mod; }
struct Combinatorics{
    int n; vector<int> fact, infact;
    Combinatorics(int _n = 0){
        fact.assign(n + 1, 0);
        infact.assign(n + 1, 0);
        fact[0] = 1;
        FOR(i, 1, n)fact[i] = 1ll * i * fact[i - 1] % mod;
        infact[n] = fastPow(fact[n], mod - 2);
        FORD(i, n, 1)infact[i - 1] = infact[i] * i % mod;
    }
    int calc(int k, int n){
        return k > n ? 0 : 1ll * fact[n] * infact[n - k] % mod * infact[k] % mod;
    }
}Comb;
struct Dinic{
    struct Edge{
        int to, cap, flow, rev;
        Edge(int _to, int _cap, int _rev)
            : to(_to), cap(_cap), flow(0), rev(_rev) {}
    };
    int n, source, sink;
    vector<int> level, ptr;
    vector<vector<Edge>> adj;

    Dinic(int _n = 0, int _s = 0, int _t = 0){
        init(_n, _s, _t);
    }

    void init(int _n, int _s, int _t){
        n = _n, source = _s, sink = _t;
        adj.assign(n + 1, vector<Edge>());
        level.assign(n + 1, 0);
        ptr.assign(n + 1, 0);
    }

    void addEdge(int u, int v, int cap){
        adj[u].push_back(Edge(v, cap, adj[v].size()));
        adj[v].push_back(Edge(u, 0, adj[u].size() - 1));
    }

    bool bfs(){
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e : adj[u]){
                if(level[e.to] == -1 && e.flow < e.cap){
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int u, int pushed){
        if(u == sink || pushed == 0)
            return pushed;
        for(int &cid = ptr[u]; cid < (int)adj[u].size(); cid++){
            Edge &e = adj[u][cid];
            if(level[e.to] != level[u] + 1 || e.flow == e.cap)
                continue;
            int tr = dfs(e.to, min(pushed, e.cap - e.flow));
            if(tr == 0) continue;
            e.flow += tr;
            adj[e.to][e.rev].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long maxFlow(){
        long long f = 0;
        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(source, inf)){
                f += pushed;
            }
        }
        return f;
    }
};
struct DSU{
    int n; vector<int> root, sz;
    DSU(int _n = 0){
        n = _n;
        root.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        FOR(i, 1, n)root[i] = i;
    }
    void reset(){
        FOR(i, 1, n)root[i] = i, sz[i] = 1;
    }
    int find_root(int v){
        return root[v] = root[v] == v ? v : find_root(root[v]);
    }
    bool unite(int u, int v){
        u = find_root(u);
        v = find_root(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        root[v] = u;
        return true;
    }
};
template<class T>
    struct Fenwick{
        int n; vector<T> fw;
        Fenwick(int _n = 0){
            n = _n;
            fw.assign(n + 1, T());
        }
        void reset(){
            FOR(i, 1, n)fw[i] = T();
        }
        void update(int x, T v){
            for(; x <= n; x += x & -x) fw[x] = fw[x] + v;
        }
        T get(int x){
            T res = 0;
            for(; x >= 1; x &= x - 1) res = res + fw[x];
            return res;
        }
        T get(int l, int r){
            if(l > r) return 0;
            return get(r) - get(l - 1);
        }
    };
struct Hashing{
    int n, base, mod;
    long long M;
    vector<int> power, Hash;
    Hashing(int _n = 0, int _base = 0, int _mod = 0, string s = ""){
        n = _n;
        M = 1ll * mod * mod;
        Hash.assign(n + 2, 0);
        power.assign(n + 2, 0);
        power[0] = 1;
        FOR(i, 1, n){
            Hash[i] = (Hash[i - 1] * base + s[i]) % mod;
            power[i] = 1ll * power[i - 1] * i % mod;
        }
    }
    int getHash(int l, int r){
        return (Hash[r] - 1ll * Hash[l - 1] * power[r - l + 1] + M) % mod;
    }

};
struct Interval{

    vector<long long> it;
    vector<long long> lz;
    int n;
    Interval(int _n = 0){
        n = _n;
        it.assign((n + 1) * 4, 0);
        lz.assign((n + 1) * 4, 0);
    }

    void push(int id){
        if(lz[id] == 0) return;
        lz[id << 1] += lz[id];
        lz[id << 1 | 1] += lz[id];
        it[id << 1] += lz[id];
        it[id << 1 | 1] += lz[id];
        lz[id] = 0;
    }
    void update(int id, int l, int r, int u, int v, int w){
        if(l > v || r < u) return;
        if(l >= u && r <= v){
            it[id] += w;
            lz[id] += w;
            return;
        }
        push(id);
        int mid = l + r >> 1;
        update(id << 1, l, mid, u, v, w);
        update(id << 1 | 1, mid + 1, r, u, v, w);
        it[id] = max(it[id << 1], it[id << 1 | 1]);
    }
    void update(int u, int v, int w){
        update(1, 1, n, u, v, w);
    }
    long long get(int id, int l, int r, int u, int v){
        if(l >= u && r <= v) return it[id];
        int mid = l + r >> 1;
        push(id);
        if(v <= mid) return get(id << 1, l, mid, u, v);
        if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
        long long L = get(id << 1, l, mid, u, v);
        long long R = get(id << 1 | 1, mid + 1, r, u, v);
        return max(L, R);
    }
    int get(int l, int r){
        return get(1, 1, n, l, r);
    }
};

const int maxN = 3e5 + 5;

int n, m, T;
int a[maxN], b[maxN];
long long pref[maxN];
void fuck(){

    cin >> n >> m >> T;
    FOR(i, 1, n){
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    FOR(i, 1, m)cin >> b[i];
    int answer = 0;
    int j = 1;
    FOR(i, 1, n){
        while(j <= m && b[j] < i)++j;
        // j va j - 1
        if(j <= m && b[j] >= i) if(pref[b[j]] - pref[i - 1] <= T)maximize(answer, b[j] - i + 1 + (T - pref[b[j]] + pref[i - 1]) / a[i]);
        if(j > 1 && b[j - 1] <= i) if(pref[i] - pref[b[j - 1] - 1] <= T) maximize(answer, i - b[j - 1] + 1 + (T - pref[i] + pref[b[j - 1] - 1]) / a[i]);
    }
    cout << answer;
}
int main(){
    #define LOVE "b18"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}

