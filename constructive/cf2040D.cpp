#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
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
const int mod = 1e9 + 7;
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
const int maxN = 2e5 + 5;
const int inf = 2e9;
const long long infll = 1e18;
int n;
vector<int> adj[maxN];
int a[maxN];
bool prime[maxN << 1];
int MAX = 4e5;
void sieve(){
    prime[0] = prime[1] = 1;
    for(int i = 2; i * i <= MAX; ++i){
        if(!prime[i]){
            for(int j = i * i; j <= MAX; j += i)prime[j] = 1;
        }
    }
}
int cnt = 1;
void dfs(int u = 1, int pre = 0){
    for(int v : adj[u]){
        if(v != pre){
            ++cnt;
            while(!prime[abs(cnt - a[u])]){
                ++cnt;
            }
            a[v] = cnt;
            dfs(v, u);
        }
    }
}
void process(){
    cin >> n;
    FOR(i, 1, n){
        adj[i].clear();
    }
    cnt = 1;
    FOR(i, 2, n){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    a[1] = 1;
    dfs();
    FOR(i, 1, n)cout << a[i] << ' ';
    cout << "\n";
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
    sieve();
    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
