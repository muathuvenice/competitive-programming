#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(all(v), v.end())
#define mp make_pair
#define Mask(i) (1 << (i))
#define Bit(x, i) (((x) >> (i)) & 1)
#define Cnt(x) __builtin_popcount(x)
#define Cntll(x) __builtin_popcountll(x)
#define Ctz(x) __builtin_ctz(x)
#define Ctzll(x) __builtin_ctzll(x)
#define Clz(x) __builtin_clz(x)
#define Clzll(x) __builtin_clzll(x)
bool minimize(int &u, int v){ return u > v ? u = v, true : false;}
bool maximize(int &u, int v){ return u < v ? u = v, true : false;}
bool minimizell(long long &u, long long v){ return u > v ? u = v, true : false;}
bool maximizell(long long &u, long long v){ return u < v ? u = v, true : false;}
const int mod = 1e9 + 7;
void add(int &u, int v){ u += v; if(u >= mod) u -= mod;}
void sub(int &u, int v){ u -= v; if(u < 0) u += mod;}
int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
const int maxN = 1e5 + 5;
const int logN = __lg(maxN);
const int maxM = 1e5 + 5;
const int maxK = 1e5 + 5;
const long long infll = 1e18;
int n, s, e, q;
int w[maxN];
pair<int, int> edge[maxN];
vector<int> adj[maxN];
bool spec[maxN];
int par[maxN][17];
long long d[maxN], f[maxN], dp[maxN], Min[maxN][17];
int in[maxN], out[maxN], timeDfs;
int h[maxN];
void dfs(int u = 1, int p = 0){
    in[u] = ++timeDfs;
    dp[u] = infll;
    if(spec[u]) dp[u] = d[u];
    for(int id : adj[u]){
        int v = edge[id].first ^ edge[id].second ^ u;
        if(v == p) continue;
        h[v] = h[u] + 1;
        d[v] = d[u] + w[id];
        par[v][0] = u;
        dfs(v, u);
        minimizell(dp[u], dp[v]);
    }
    out[u] = timeDfs;
    if(dp[u] == infll)f[u] = infll;
    else f[u] = dp[u] - 2 * d[u];
}
bool inside(int root, int u){
    return in[root] <= in[u] && out[root] >= out[u];
}
long long jump(int u, int target){
    int dist = h[u] - h[target];
    long long cur = d[u];
    long long res = cur + f[u];
    REP(i, 16, 0){
        if(Bit(dist, i)){
            minimizell(res, cur + Min[u][i]);
            u = par[u][i];
        }
    }
    assert(u == target);
    return res;
}
void process(){
    cin >> n >> s >> q >> e;
    FOR(i, 1, n - 1){
        cin >> edge[i].first >> edge[i].second >> w[i];
        adj[edge[i].first].emplace_back(i);
        adj[edge[i].second].emplace_back(i);
    }
    FOR(i, 1, s){
        int u;
        cin >> u;
        spec[u] = true;
    }
    dfs(e, 0);

    FOR(i, 1, n - 1){
        int u = edge[i].first, v = edge[i].second;
        if(in[u] > in[v]){
            swap(u, v);
            swap(edge[i].first, edge[i].second);
        }
        Min[v][0] = f[u];
    }
    d[0] = -1;
    FOR(j, 1, 16){
        FOR(i, 1, n){
            par[i][j] = par[par[i][j - 1]][j - 1];
            Min[i][j] = min(Min[i][j - 1], Min[par[i][j - 1]][j - 1]);
        }
    }
    const long long Max = 1e17;
    while(q--){
        int x, r;
        cin >> x >> r;
        int u = edge[x].first, v = edge[x].second;
        if(!inside(v, r)){
            cout << "escaped\n";
            continue;
        }
        long long answer = jump(r, v);
        if(answer >= Max)cout << "oo\n";
        else cout << answer << '\n';
    }
}
#define LOVE "valley"
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    process();
    return 0;
}

