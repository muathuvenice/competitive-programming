#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
inline bool maximize(int &u, int v){
    return v > u ? u = v, true : false;
}
inline bool minimize(int &u, int v){
    return v < u ? u = v, true : false;
}
inline bool maximizell(long long &u, long long v){
    return v > u ? u = v, true : false;
}
inline bool minimizell(long long &u, long long v){
    return v < u ? u = v, true : false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
inline void degbug(){

}
int n, m, q;
pair<int, pair<int, int>> edge[maxN];
int root[maxN], sz[maxN];
int find_root(int v){
    return root[v] = root[v] == v ? v : find_root(root[v]);
}
bool union_set(int u, int v){
    u = find_root(u);
    v = find_root(v);
    if(u == v) return false;
    if(sz[u] < sz[v])swap(u, v);
    sz[u] += sz[v];
    root[v] = u;
    return true;
}
vector<pair<int, int>> adj[maxN];
int par[maxN][17], d[maxN], Max[maxN][17];
void dfs(int u = 1){
    for(pair<int, int> x : adj[u]){
        int v = x.first;
        int w = x.second;
        if(v == par[u][0])continue;
        par[v][0] = u;
        Max[v][0] = w;
        d[v] = d[u] + 1;
        dfs(v);
    }
}
int getMax(int u, int v){
    if(d[u] < d[v])swap(u, v);
    int res = 0;
    REP(i, 16, 0){
        if(d[par[u][i]] >= d[v]){
            maximize(res, Max[u][i]);
            u = par[u][i];
        }
    }
    if(u == v) return res;
    REP(i, 16, 0){
        if(par[u][i] != par[v][i]){
            maximize(res, Max[u][i]);
            maximize(res, Max[v][i]);
            u = par[u][i];
            v = par[v][i];
        }
    }
    maximize(res, Max[u][0]);
    maximize(res, Max[v][0]);
    return res;
}
namespace sparseTable{
    int Max[maxN][17], lg[maxN];
    int get(int l, int r){
        int k = lg[r - l + 1];
        return max(Max[l][k], Max[r - (1 << k) + 1][k]);
    }
    void solve(){
        FOR(i, 2, n)lg[i] = lg[i >> 1] + 1;
        FOR(i, 1, n - 1){
            Max[i][0] = getMax(i, i + 1);
        }
        FOR(j, 1, lg[n - 1]){
            FOR(i, 1, n - 1 - (1 << i) + 1){
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
            }
        }
        FOR(i, 1, q){
            int l, r;
            cin >> l >> r;
            if(l == r)cout << 0 << ' ';
            else{
                cout << get(l, r - 1) << " ";
            }
        }
    }
}
void process(){
    cin >> n >> m >> q;
    FOR(i, 1, n)adj[i].clear();
    FOR(i, 1, m){
        int u, v;
        cin >> u >> v;
        edge[i] = mp(i, mp(u, v));
    }
    sort(edge + 1, edge + 1 + m);
    FOR(i, 1, n)root[i] = i, sz[i] = 1;
    FOR(i, 1, m){
        int u = edge[i].second.first;
        int v = edge[i].second.second;
        if(union_set(u, v)){
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }
    }
    dfs();
    d[0] = -1;
    FOR(j, 1, 16){
        FOR(i, 1, n){
            par[i][j] = par[par[i][j - 1]][j - 1];
            Max[i][j] = max(Max[i][j - 1], Max[par[i][j - 1]][j - 1]);
        }
    }
    sparseTable :: solve();
    cout << "\n";
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
    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



