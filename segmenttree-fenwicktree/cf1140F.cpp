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
const int maxN = 3e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n;
map<pair<int, int>, int> visited;
int root[maxN << 1], sz[maxN << 1], cntX[maxN << 1], cntY[maxN << 1];
int find_root(int v){
    while(v != root[v]) v = root[v];
    return v;
}
const int Max = 3e5;
vector<int> operation;
void init(){
    FOR(i, 1, Max){
        root[i] = i;
        root[i + Max] = i + Max;
        cntX[i] = 1;
        cntY[i + Max] = 1;
        sz[i] = sz[i + Max] = 1;
    }
}
long long rem = 0;
bool unite(int u, int v){
    u = find_root(u);
    v = find_root(v);
    if(u == v) return false;
    rem -= 1ll * cntX[u] * cntY[u] + 1ll * cntX[v] * cntY[v];
    if(sz[u] < sz[v]) swap(u, v);
    operation.emplace_back(v);
    root[v] = u;
    sz[u] += sz[v];
    cntX[u] += cntX[v];
    cntY[u] += cntY[v];
    rem += 1ll * cntX[u] * cntY[u];
    return true;
}
void rollback(){
    int v = operation.back();
    operation.pop_back();
    int u = find_root(v);
    rem -= 1ll * cntX[u] * cntY[u];
    cntX[u] -= cntX[v];
    cntY[u] -= cntY[v];
    sz[u] -= sz[v];
    rem += 1ll * cntX[u] * cntY[u] + 1ll * cntX[v] * cntY[v];
    root[v] = v;
}
long long answer[maxN];
vector<pair<int, int>> it[maxN << 2];
void modify(int id, int l, int r, int u, int v, pair<int, int> edge){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        it[id].emplace_back(edge);
        return;
    }
    int mid = l + r >> 1;
    modify(id << 1, l, mid, u, v, edge);
    modify(id << 1 | 1, mid + 1, r, u, v, edge);
}
void dfs(int id, int l, int r){
    int saveSize = operation.size();
    for(auto[u, v] : it[id]) unite(u, v);
    int mid = l + r >> 1;
    if(l == r) answer[l] = rem;
    else {
        dfs(id << 1, l, mid);
        dfs(id << 1 | 1, mid + 1, r);
    }
    while(operation.size() > saveSize) rollback();
}
void process(){
    cin >> n;
    init();
    FOR(i, 1, n){
        int x, y;
        cin >> x >> y;
        if(!visited[mp(x, y)]){
            visited[mp(x, y)] = i;
        }else{
            modify(1, 1, n, visited[mp(x, y)], i - 1, mp(x, y + Max));
            visited.erase(mp(x, y));
        }
    }
    for(auto it : visited){
        auto [u, v] = it.first;
        int x = it.second;
        modify(1, 1, n, x, n, mp(u, v + Max));
    }
    dfs(1, 1, n);
    FOR(i, 1, n)cout << answer[i] << ' ';
}
#define LOVE "code"
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





