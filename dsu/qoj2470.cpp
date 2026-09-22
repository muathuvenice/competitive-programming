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
#define parity(x) __builtin_parity(x)
#define parityll(x) __builtin_parityll(x)
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
const int maxN = 60 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, m, k;
vector<int> adj[maxN];
pair<int, int> query[maxN];
int par[maxN], d[maxN];
void dfs(int u = 1, int p = 0){
    for(int v : adj[u]){
        if(v == p) continue;
        par[v] = u;
        d[v] = d[u] + 1;
        dfs(v, u);
    }
}
namespace subtask1{
    bool check(){
        return m == 1;
    }
    void solve(){
        int u = query[1].first, v = query[1].second;
        int numEdge = 0;
        while(u != v){
            if(d[u] > d[v]){
                ++numEdge;
                u = par[u];
            }else{
                ++numEdge;
                v = par[v];
            }
        }
        int answer = fastPow(k, n - 1);
        sub(answer, 1ll * k * fastPow(k, n - 1 - numEdge) % mod);
        cout << answer;
    }
}
namespace ac{
    int root[maxN];
    int find_root(int v) {
        return root[v] = root[v] == v ? v : find_root(root[v]);
    }
    bool unite(int u, int v){
        u = find_root(u);
        v = find_root(v);
        if( u == v) return false;
        root[v] = u;
        return true;
    }
    int cnt;
    void calc(int u, int v){

        if(d[u] < d[v]) swap(u, v);
        int x = u;
        while(d[u] > d[v]){
            cnt -= unite(x, u);
            u = par[u];
        }
        while(u != v){
            cnt -= unite(x, u);
            cnt -= unite(x, v);
            u = par[u];
            v = par[v];
        }
    }
    int power[maxN];
    void solve(){
        power[0] = 1;
        FOR(i, 1, n - 1)power[i] = 1ll * power[i - 1] * k % mod;
        int answer = 0;
        FOR(mask, 0, Mask(m) - 1){
            FOR(i, 1, n)root[i] = i;
            cnt = n - 1;
            FOR(i, 1, m){
                if(!Bit(mask, i - 1)) continue;
                calc(query[i].first, query[i].second);
            }
            if(parity(mask))sub(answer, power[cnt]);
            else add(answer, power[cnt]);
        }

        cout << answer;
    }
}
void process(){
    cin >> n >> m >> k;
    FOR(i, 1, n - 1){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    FOR(i, 1, m){
        cin >> query[i].first >> query[i].second;
    }
    dfs();
//    if(subtask1 :: check()) return subtask1 :: solve();
    return ac :: solve();
}
#define LOVE "colorful"
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





