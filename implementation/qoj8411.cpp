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


const int maxN = 2e5 + 5;

int n, h[maxN], a[maxN], b[maxN];
int q;
vector<int> query[maxN];
vector<int> event[maxN];
int L[maxN], R[maxN];

struct Node{
    int Max, Min, qMax, qMin, ans;
    Node(){
        Max = qMax = -inf;
        Min = qMin = inf;
        ans = -1;
    }
}it[maxN << 2];

void pushUp(int id){
    it[id].Min = min(it[id << 1].Min, it[id << 1 | 1].Min);
    it[id].Max = max(it[id << 1].Max, it[id << 1 | 1].Max);
    it[id].ans = max(it[id << 1].ans, it[id << 1 | 1].ans);
}
void modify(int id, int k){
    maximize(it[id].ans, it[id].Max - k);
    maximize(it[id].ans, k - it[id].Min);
    maximize(it[id].qMax, k);
    minimize(it[id].qMin, k);
}
void pushDown(int id){
    if(it[id].qMax != -inf){
        modify(id << 1, it[id].qMax);
        modify(id << 1 | 1, it[id].qMax);
        it[id].qMax = -inf;
    }
    if(it[id].qMin != inf){
        modify(id << 1, it[id].qMin);
        modify(id << 1 | 1, it[id].qMin);
        it[id].qMin = inf;
    }
}
void updatePos(int id, int l, int r, int p, int val){
    if(l == r){
        if(val > 0){
            it[id].Min = it[id].Max = val;
        }else{
            it[id].Min = inf;
            it[id].Max = -inf;
        }
//        cout << "update pos " << p << ' ' << val << '\n';
        return;
    }
    pushDown(id);
    int mid = l + r >> 1;
    if(p <= mid) updatePos(id << 1, l, mid, p, val);
    else updatePos(id << 1 | 1, mid + 1, r, p, val);
    pushUp(id);
}
void updateRange(int id, int l, int r, int u, int v, int w){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
//        cout << "range " << l << ' ' << r << ' ' << w << '\n';
//        cout << it[id].Min << ' ' << it[id].Max << '\n';
        modify(id, w);
//        cout << it[id].ans << '\n';
        return;
    }
    int mid = l + r >> 1;
    pushDown(id);
    updateRange(id << 1, l, mid, u, v, w);
    updateRange(id << 1 | 1, mid + 1, r, u, v, w);
    pushUp(id);
}
int ans[maxN];
int get(int id, int l, int r, int u, int v){
    if(l >= u && r <= v){
//        cout << l << ' ' << r << '\n';
//        cout << it[id].ans << '\n';
        return it[id].ans;
    }
    int mid = l + r >> 1;
    pushDown(id);
    if(v <= mid) return get(id << 1, l, mid, u, v);
    if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
    return max(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}
void fuck(){
    cin >> n;
    FOR(i, 1, n){
        cin >> h[i] >> a[i] >> b[i];
        if(i + a[i] <= n) event[i + a[i]].emplace_back(i);
        if(i + b[i] + 1 <= n) event[i + b[i] + 1].emplace_back(-i);
    }
    cin >> q;
    FOR(i, 1, q){
        cin >> L[i] >> R[i];
        query[R[i]].emplace_back(i);
    }
    FOR(i, 1, n){
//        cout << i << '\n';
        for(int p : event[i])if(p > 0) updatePos(1, 1, n, p, h[p]);
        else updatePos(1, 1, n, -p, -1);
        updateRange(1, 1, n, max(1, i - b[i]), min(i - 1, i - a[i]), h[i]);
        for(int id : query[i]){
//            cout << "getAnswer " << id << '\n';
            ans[id] = get(1, 1, n, L[id], i);
        }
    }
    FOR(i, 1, q)cout << ans[i] << '\n';
}
int main(){
    #define LOVE "TwoAntennas"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



