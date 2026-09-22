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
int n, q;
vector<int> adj[maxN];
int lg[2 * maxN], tour[2 * maxN], p[maxN], depth[maxN], min_depth[maxN * 2][18], cnt;
inline void dfs(int u = 1){
    tour[++cnt] = u;
    p[u] = cnt;
    for(int v : adj[u])if(p[v] == 0){
        depth[v] = depth[u] + 1;
        dfs(v);
        tour[++cnt] = u;
    }
}
inline int getMin(int u, int v){
    return depth[u] < depth[v] ? u : v;
}
inline int lca(int u, int v){
    int pu = p[u], pv = p[v];
    if(pu > pv) swap(pu, pv);
    int k = lg[pv - pu + 1];
    return getMin(min_depth[pu][k], min_depth[pv - (1 << k) + 1][k]);
}
inline int dist(int u, int v){
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
bool cmp(const int &a, const int &b){
    return p[a] < p[b];
}
vector<int> e[maxN];
bool spec[maxN];
vector<int> Node[maxN];
int cntDepth[maxN];
long long answer = 0;
int D;
int sz[maxN], heavy[maxN], in[maxN], out[maxN], timeDfs, id[maxN];
void dfsV(int u){
    sz[u] = 1;
    heavy[u] = 0;
    in[u] = ++timeDfs;
    id[timeDfs] = u;
    for(int v : e[u]){
        dfsV(v);
        sz[u] += sz[v];
        if(sz[v] > sz[heavy[u]]) heavy[u] = v;
    }
    out[u] = timeDfs;
}
void del(int u){
    if(!spec[u]) return;
//    cout << "del " << u << '\n';
    cntDepth[depth[u]]--;
//    cout << depth[u] << ' ' << cntDepth[depth[u]] << '\n';
}
void add(int u){
    if(!spec[u]) return;
//    cout << "add " << u << '\n';
    cntDepth[depth[u]]++;
//    cout << depth[u] << ' ' << cntDepth[depth[u]] << '\n';
}
void sack(int u){
    for(int v : e[u]){
        if(v != heavy[u]){
            sack(v);
            FOR(i, in[v], out[v])del(id[i]);
        }
    }
    if(heavy[u]) sack(heavy[u]);

    if(spec[u]) {
        int cost = depth[u] + D;
        if(cost < n) answer += cntDepth[cost];
    }
    add(u);
    for(int v : e[u]){
        if(v != heavy[u]){
            FOR(i, in[v], out[v]){
                if(spec[id[i]]){
                    int cost = D + 2 * depth[u] - depth[id[i]];
                    if(cost >= 0 && cost < n)answer += cntDepth[cost];
                }
            }
            FOR(i, in[v], out[v]){
                add(id[i]);
            }
        }
    }
}
void buildVirtualTree(vector<int> &Node){
    sort(all(Node), cmp);
    int ssz = Node.size();
    for(int u : Node)spec[u] = true;
    for(int i = 0; i < ssz - 1; ++i){
        Node.emplace_back(lca(Node[i], Node[i + 1]));
    }
    sort(all(Node), cmp);
    uni(Node);
//    for(int u : Node){
//        assert(in[u] == 0);
//        assert(out[u] == 0);
//        assert(sz[u] == 0);
//        assert(e[u].empty());
//        assert(cntDepth[depth[u]] == 0);
//    }
    ssz = Node.size();
    for(int i = 0; i < ssz - 1; ++i){
        int p = lca(Node[i], Node[i + 1]);
        e[p].emplace_back(Node[i + 1]);
    }
//    for(int u : Node)cout << u << ' ';cout << '\n';
    dfsV(Node[0]);
    answer = 0;
    sack(Node[0]);
    cout << answer << '\n';
    timeDfs = 0;
    for(int u : Node){
        e[u].clear();
        cntDepth[depth[u]] = 0;
        in[u] = out[u] = 0;
        spec[u] = false;
    }
}
void process(){
    cin >> n >> q;

    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    for(int i = 2; i <= cnt; ++i)lg[i] = lg[i >> 1] + 1;
    for(int i = 1; i <= cnt; ++i)min_depth[i][0] = tour[i];
    for(int j = 1; j <= lg[cnt]; ++j){
        for(int i = 1; i + (1 << j) - 1 <= cnt; ++i){
            min_depth[i][j] = getMin(min_depth[i][j - 1], min_depth[i + (1 << (j - 1))][j - 1]);
        }
    }
    while(q--){
        int k;
        cin >> k >> D;
        vector<int> Node(k);
        for(int &u : Node)cin >> u;
        buildVirtualTree(Node);
    }
    FOR(i, 1, n)adj[i].clear(), p[i] = 0;
    cnt = 0;
}
#define LOVE "hdt_412"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
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




