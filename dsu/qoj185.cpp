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
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, m, q;
pair<int, int> edge[maxN];
int cen[maxN], reqW[maxN], type[maxN], ans[maxN];
int w[maxN];
int root[maxN], sz[maxN];
int find_root(int v){
    while(v != root[v]) v = root[v];
    return v;
}
vector<pair<int, int>> save;
bool unite(int u, int v){
    u = find_root(u);
    v = find_root(v);
    if(u == v) return false;
    if(sz[u] < sz[v]) swap(u, v);
    save.emplace_back(v, sz[v]);
    sz[u] += sz[v];
    root[v] = u;
    return true;
}
void rollback(){
    auto [v, sv] = save.back();
    save.pop_back();
    int u = root[v];
    sz[u] -= sv;
    root[v] = v;
}
void reset(){
    FOR(i, 1, n)root[i] = i, sz[i] = 1;
    while(!save.empty()) save.pop_back();
}
struct query{
    int w, id;
    query(int _w, int _id){
        w = _w;
        id = _id;
    }
    bool operator < (const query &rhs) const{
        return w != rhs.w ? w > rhs.w : id > rhs.id;
    }
};
bool change[maxN];
void process(){
    cin >> n >> m;
    FOR(i, 1, n) root[i] = i, sz[i] = 1;
    multiset<query> rem;
    FOR(i, 1, m){
        cin >> edge[i].first >> edge[i].second >> w[i];
        rem.insert(query(w[i], i));
    }
    cin >> q;
    FOR(i, 1, q){
        cin >> type[i] >> cen[i] >> reqW[i];
    }
    int BLOCK = 3 * sqrt(q + n);
    for(int l = 1; l <= q; l += BLOCK){
        int r = min(q, l + BLOCK - 1);
        reset();
        vector<tuple<int, int, vector<int>>> ask;
        vector<int> modify;
        FOR(i, l, r){
            if(type[i] == 1){
                if(!change[cen[i]]){
                    modify.emplace_back(cen[i]);
                    change[cen[i]] = true;
                    rem.erase(query(w[cen[i]], cen[i]));
                }
            }
        }
        FOR(i, l, r){
            if(type[i] == 1){
                w[cen[i]] = reqW[i];
            }else{
                vector<int> modifyCur;
                for(int id : modify)if(w[id] >= reqW[i])modifyCur.emplace_back(id);
                ask.emplace_back(reqW[i], i, modifyCur);
            }
        }
        sort(all(ask), greater<tuple<int, int, vector<int>>> ());
        auto it = rem.begin();
        for(auto[w, id, modify] : ask){
            while(it != rem.end() && it -> w >= w) unite(edge[it -> id].first, edge[it -> id].second), ++it;
            int saveSize = save.size();
            for(int id : modify) unite(edge[id].first, edge[id].second);
            ans[id] = sz[find_root(cen[id])];
            while(save.size() > saveSize)rollback();
        }
        for(int id : modify){
            change[id] = false;
            rem.insert(query(w[id], id));
        }
    }
    FOR(i, 1, q)if(type[i] == 2)cout << ans[i] << '\n';
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
