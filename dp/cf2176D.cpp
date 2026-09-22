#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
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
const int mod = 998244353;
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

const int maxN = 2e5 + 5;
vector<int> adj[maxN];
int n, m;
long long a[maxN];
map<long long, int> f[maxN];
pair<long long, int> c[maxN];

void fuck(){
    cin >> n >> m;
    FOR(i, 1, n) cin >> a[i], c[i] = mp(a[i], i);
    sort(c + 1, c + 1 + n);
    FOR(i, 1, m){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        f[v][a[u]]++;

    }

    FOR(i, 1, n){
        auto [val, u] = c[i];
        for(int v : adj[u]){
            if(f[u].find(a[v] - a[u]) != f[u].end()){
                add(f[v][a[u]], f[u][a[v] - a[u]]);
            }
        }
    }
    int answer = 0;
    FOR(i, 1, n){
        for(auto [w, cnt] : f[i]){
            add(answer, cnt);
        }
    }
    cout << answer << '\n';
    // res
    FOR(i, 1, n){
        adj[i].clear();
        f[i].clear();
    }
}
int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}




