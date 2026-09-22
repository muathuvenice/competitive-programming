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

int n;
vector<int> adj[maxN];
bool visited[maxN];
int salary[maxN];
int par[maxN], cnt, node[maxN];
void bfs(int root){
    FOR(i, 1, n) visited[i] = false;
    queue<int> q;
    q.emplace(root);
    visited[root] = true;
    par[root] = 0;
    cnt = 0;
    while(!q.empty()){
        int u = q.front();
        node[++cnt] = u;
        q.pop();
        for(int v : adj[u]){
            if(!visited[v]) {
                visited[v] = true;
                q.emplace(v);
                par[v] = u;
            }
        }
    }
}

int calc(int root){
    bfs(root);
    FOR(i, 1, n) if(!visited[i]) return inf;


    FOR(i, 1, n) salary[i] = 1;
    int sum = 0;
    FORD(i, n, 1){
        int v = node[i];
        int u = par[v];
        if(u) salary[u] += salary[v];
        sum += salary[v];
    }
    return sum;
}
void fuck(){
    cin >> n;
    FOR(i, 1, n){
        int k;
        cin >> k;
        REP(j, k){
            int u;
            cin >> u;
            adj[u].emplace_back(i);
        }
    }
    int answer = inf;
    FOR(i, 1, n) minimize(answer, calc(i));
    cout << answer;
}
int main(){
    #define LOVE "boss"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}





