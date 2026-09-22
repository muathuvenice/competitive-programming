#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
using namespace std;
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
#define assert(x) if(!(x)) cout << "error", exit(0)
template <class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template <class X, class Y>
    bool maximize(X &x, Y y) {
        return x < y ? x = y, true : false;
    }
template <class T>
    void printVec(vector<T> &vec){
        for(T x : vec)cout << x << ' ';
        cout << '\n';
    }
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
const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 1e5 + 5;

long long f[1 << 5][maxN];
int n, m, k;
int imp[maxN];
vector<pair<int, int>> adj[maxN];
struct state {
    long long dist;
    int u;
    bool operator < (const state &rhs) const {
        return dist > rhs.dist;
    }
};
int root;
void solve(){
    cin >> n >> k >> m;
    cin >> root;--k;
    REP(i, k) cin >> imp[i];
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    FOR(mask, 1, Mask(k) - 1) FOR(i, 1, n) f[mask][i] = infll;
    priority_queue<state> q;
    FOR(mask, 0, Mask(k) - 1) {
        FOR(i, 1, n) {
            for(int sub = mask; sub >= 0; --sub) {
                sub &= mask;
                minimize(f[mask][i], f[sub][i] + f[mask ^ sub][i]);
            }
            if(f[mask][i] != infll) q.push({f[mask][i], i});
        }
        while(!q.empty()) {
            long long dist = q.top().dist;
            int u = q.top().u;
            q.pop();
            if(dist > f[mask][u]) continue;
            for(pair<int, int> x : adj[u]) {
                int v = x.first;
                int w = x.second;
                if(minimize(f[mask][v], dist + w)) {
                    q.push({f[mask][v], v});
                }
            }
        }
        REP(i, k) minimize(f[mask | Mask(i)][imp[i]], f[mask][imp[i]]);
    }
    cout << f[Mask(k) - 1][root];
}
int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        solve();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}






