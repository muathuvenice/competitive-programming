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
const int maxN = 5e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
vector<int> adj[maxN];
int p[maxN], n, a[maxN], q;
long long f[maxN];
long long sum[maxN];
int par[maxN][19], d[maxN];
void dfs(int u){
    sum[u] = a[u];
    for(int v : adj[u]){
        d[v] = d[u] + 1;
        par[v][0] = p[v];
        dfs(v);
        f[u] += f[v] + sum[v];
        sum[u] += sum[v];
    }
}
int jump(int u, int target){
    REP(i, 18, 0){
        if(d[par[u][i]] > d[target]) u = par[u][i];
    }
    return u;
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 2, n){
        cin >> p[i];
        adj[p[i]].emplace_back(i);
    }
    dfs(1);
    FOR(j, 1, 18)FOR(i, 1, n)par[i][j] = par[par[i][j - 1]][j - 1];
    while(q--){
        int x, y;
        cin >> x >> y;
        if(y == p[x]){
            cout << f[y] << '\n';
            continue;
        }
        long long answer = f[y];
        int v = jump(x, y);
        answer -= a[x] * (d[x] - d[v]);

        answer += (sum[v] - sum[x]);
//        cout << "check " << answer << '\n';

        cout << answer << '\n';
    }
}
#define LOVE "truyvancay"
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




