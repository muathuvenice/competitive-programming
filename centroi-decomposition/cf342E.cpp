#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
const int mod = 1e9 + 7;
inline bool maximize(int &u, int v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimize(int &u, int v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
inline bool maximizell(long long &u, long long v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimizell(long long &u, long long v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
inline int fastPow(int a, int n){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 1e5 + 5;
const int inf = 2e9;
const long long infll = 1e18;
vector<int> adj[maxN];
int n, q;
namespace LCA{
    int depth[maxN], p[maxN], lg[maxN << 1], min_depth[18][maxN << 1], tour[maxN << 1], cnt;
    void dfs(int u = 1, int pre = 0){
        tour[++cnt] = u;
        p[u] = cnt;
        for(int v : adj[u]){
            if(v != pre){
                depth[v] = depth[u] + 1;
                dfs(v, u);
                tour[++cnt] = u;
            }
        }
    }
    int getMin(int u, int v){
        return depth[u] < depth[v] ? u : v;
    }
    int get(int u, int v){
        int l = p[u], r = p[v];
        if(l > r)swap(l, r);
        int k = lg[r - l + 1];
        return getMin(min_depth[k][l], min_depth[k][r - (1 << k) + 1]);
    }
    int dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[get(u, v)];
    }
    void build(){
        dfs();
        FOR(i, 2, cnt)lg[i] = lg[i >> 1] + 1;
        FOR(i, 1, cnt)min_depth[0][i] = tour[i];
        FOR(j, 1, lg[cnt])FOR(i, 1, cnt - (1 << j) + 1)min_depth[j][i] = getMin(min_depth[j - 1][i], min_depth[j - 1][i + (1 << (j - 1))]);
    }
}
namespace Centroid{
    int sz[maxN], par[maxN], numNode;
    void reSize(int u, int p){
        sz[u] = 1;
        for(int v : adj[u]){
            if(v != p && par[v] == 0){
                reSize(v, u);
                sz[u] += sz[v];
            }
        }
    }
    int getCentroid(int u, int p){
        for(int v : adj[u]){
            if(v != p && par[v] == 0){
                if((sz[v] << 1) > numNode) return getCentroid(v, u);
            }
        }
        return u;
    }
    void build(int u = 1, int p = 0){
        reSize(u, p);
        numNode = sz[u];
        int c = getCentroid(u, p);
        if(p == 0)par[c] = n + 1;
        else par[c] = p;
        for(int v : adj[c]){
            if(v != p && par[v] == 0){
                build(v, c);
            }
        }
    }
}
int f[maxN];
void update(int u){
    int cur = u;
    while(cur <= n){
        minimize(f[cur], LCA :: dist(cur, u));
        cur = Centroid :: par[cur];
    }
}
int get(int u){
    int cur = u;
    int res = inf;
    while(cur <= n){
        minimize(res, LCA :: dist(cur, u) + f[cur]);
        cur = Centroid :: par[cur];
    }
    return res;
}
void process(){
    cin >> n >> q;
    FOR(i, 2, n){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    FOR(i, 1, n)f[i] = inf;
    LCA :: build();
    Centroid :: build();
    update(1);
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int v;
            cin >> v;
            update(v);
        }else{
            int v;
            cin >> v;
            cout << get(v) << "\n";
        }
    }
}
#define NAME ""
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



