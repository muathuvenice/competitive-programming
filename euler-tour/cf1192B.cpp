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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, q;
long long w;
struct Edge{
    int u, v;
    long long c;
}edge[maxN];
vector<pair<int, long long>> adj[maxN];
long long d[maxN];
int in[maxN], out[maxN], tour[maxN], cnt;
void dfs(int u = 1, int p = 0){
    tour[++cnt] = u;
    in[u] = cnt;
    for(auto [v, c] : adj[u]){
        if(v == p) continue;
        d[v] = d[u] + c;
        dfs(v, u);
        tour[++cnt] = u;
    }
    out[u] = cnt;
}
#define ll long long
struct Node{
    ll Max, Min, LMax, RMax, answer;
    // LMax : max(d[i] - 2 * d[j]) pos[i] <= pos[j]
    // RMax : max(d[i] - 2 * d[j]) pos[j] <= pos[i]
    Node(ll _Max = 0, ll _Min = 0, ll _LMax = 0, ll _RMax = 0, ll _answer = 0){
        Max = _Max;
        Min = _Min;
        LMax = _LMax;
        RMax = _RMax;
        answer = _answer;
    }
}it[maxN << 2];

void modify(Node &u, ll val){
    u.Max += val;
    u.Min += val;
    u.LMax -= val;
    u.RMax -= val;
}
Node operator + (const Node &lhs, const Node &rhs){
    Node res;
    res.Max = max(lhs.Max, rhs.Max);
    res.Min = min(lhs.Min, rhs.Min);
    res.LMax = max({lhs.LMax, rhs.LMax, lhs.Max - 2 * rhs.Min});
    res.RMax = max({lhs.RMax, rhs.RMax, rhs.Max - 2 * lhs.Min});
    res.answer = max({lhs.answer, rhs.answer, lhs.LMax + rhs.Max, rhs.RMax + lhs.Max});
    return res;
}
void build(int id, int l, int r){
    if(l == r){
        int u = tour[l];
        it[id] = Node(d[u], d[u], -d[u], -d[u], 0);
        return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
ll lz[maxN << 2];
void push(int id){
    if(lz[id] == 0) return;
    modify(it[id << 1], lz[id]);
    modify(it[id << 1 | 1], lz[id]);
    lz[id << 1] += lz[id];
    lz[id << 1 | 1] += lz[id];
    lz[id] = 0;
    return;
}
void update(int id, int l, int r, int u, int v, ll w){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        modify(it[id], w);
        lz[id] += w;
        return;
    }
    push(id);
    int mid = l + r >> 1;
    update(id << 1, l, mid, u, v, w);
    update(id << 1 | 1, mid + 1, r, u, v, w);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
void process(){
    cin >> n >> q >> w;
    FOR(i, 1, n - 1){
        int u, v;
        ll c;
        cin >> u >> v >> c;
        edge[i] = {u, v, c};
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }
    dfs();
    build(1, 1, cnt);
    long long last = 0;
    while(q--){
        int d;
        long long e;
        cin >> d >> e;
        d = (d + last) % (n - 1);
        e = (e + last) % w;
        auto[u, v, c] = edge[d + 1];
        if(in[u] > in[v]) swap(u, v);
        update(1, 1, cnt, in[v], out[v], - c + e);
        edge[d + 1].c = e;
        last = it[1].answer;
        cout << last << '\n';
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





