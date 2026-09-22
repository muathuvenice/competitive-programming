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
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, q, d[maxN], MinDepth[maxN << 1][18], tour[maxN << 1], cnt, p[maxN], lg[maxN << 1];
vector<int> adj[maxN];
void dfs(int u = 1){
    tour[++cnt] = u;
    p[u] = cnt;
    for(int v : adj[u]){
        if(p[v]) continue;
        d[v] = d[u] + 1;
        dfs(v);
        tour[++cnt] = u;
    }
}
int getMin(int u, int v){ return d[u] < d[v] ? u : v;}
int lca(int u, int v){
    int l = p[u], r = p[v];
    if(l > r) swap(l, r);
    int k = lg[r - l + 1];
    return getMin(MinDepth[l][k], MinDepth[r - Mask(k) + 1][k]);
}
bool cmp(const int &a, const int &b){ return p[a] < p[b];}
bool imp[maxN];
int dist(int u, int v){ return d[u] + d[v] - 2 * d[lca(u, v)];}
vector<int> e[maxN];
int answer = 0;
void dfsQuery(int u){
    int cnt = 0;
    for(int v : e[u]){
        dfsQuery(v);
        cnt += imp[v];
    }
    if(imp[u]){
        answer += cnt;
        return;
    }
    if(cnt == 0){
        return;
    }
    if(cnt == 1){
        imp[u] = true;
        return;
    }
    ++answer;
}
void process(){
    cin >> n;
    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs();
    FOR(i, 1, cnt)MinDepth[i][0] = tour[i];
    FOR(i, 2, cnt)lg[i] = lg[i >> 1] + 1;
    FOR(j, 1, lg[cnt])FOR(i, 1, cnt - Mask(j) + 1)MinDepth[i][j] = getMin(MinDepth[i][j - 1], MinDepth[i + Mask(j - 1)][j - 1]);
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vector<int> Node(k);
        for(int &u : Node)cin >> u;
        sort(all(Node), cmp);
        for(int u : Node)imp[u] = true;
        int sz = (int)Node.size();
        for(int i = 0; i < sz - 1; ++i){
            Node.emplace_back(lca(Node[i], Node[i + 1]));
        }
        sort(all(Node), cmp);
        uni(Node);
        bool valid = true;
        sz = (int)Node.size();
        for(int i = 0; i < sz - 1; ++i){
            int u = lca(Node[i], Node[i + 1]);
            int v = Node[i + 1];
            if(imp[u] && imp[v] && dist(u, v) == 1){
                valid = false;
                break;
            }
            e[u].emplace_back(v);
        }

        if(!valid){
            for(int u : Node)imp[u] = false, e[u].clear();
            cout << - 1 << '\n';
            continue;
        }
        answer = 0;
        dfsQuery(Node[0]);
        cout << answer << '\n';
        for(int u : Node)imp[u] = false, e[u].clear();
    }
}
#define LOVE ""
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





