#ifdef ONLINE_JUDGE
#include "icc.h"
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
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
template<class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template<class X, class Y>
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
struct DSU{
    int n; vector<int> root, sz;
    DSU(int _n = 0){
        n = _n;
        root.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        FOR(i, 1, n)root[i] = i, sz[i] = 1;
    }
    void reset(){
        FOR(i, 1, n)root[i] = i, sz[i] = 1;
    }
    int find_root(int v){
        return root[v] = root[v] == v ? v : find_root(root[v]);
    }
    bool unite(int u, int v){
        u = find_root(u);
        v = find_root(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        root[v] = u;
        return true;
    }
}dsu;
const int maxN = 1e2 + 5;
int n;
int a[maxN], b[maxN];
#ifndef ONLINE_JUDGE
int cnt;

vector<pair<int, int>> edge;
int query(int sizea, int sizeb, int a[], int b[]){
    sort(a, a + sizea);
    sort(b, b + sizeb);
    int i = 0, j = 0;
    while(i < sizea && j < sizeb){
        if(a[i] == b[j]){
            cout << 0;
            exit(0);
        }
        if(a[i] < b[j])++i;
        else ++j;
    }
//    cout << "query\n"; REP(i, sizea)cout << a[i] << ' ';cout << '\n';
//    REP(i, sizeb) cout << b[i] << ' ';cout << '\n';
    FOR(c, 0, cnt)REP(i, sizea)REP(j, sizeb) if(edge[c] == mp(a[i], b[j]) || edge[c] == mp(b[j], a[i])) return true;

//    cout << "notExist\n";
    return false;
}

void setRoad(int x, int y){
    if(mp(x, y) == edge[cnt] || mp(y, x) == edge[cnt]){
//        cout << "match " << x << ' ' << y << '\n';
        ++cnt;
        if(cnt == n - 1){
            cout << 1;
            exit(0);
        }
        return;
    }
    cout << 0;
    exit(0);
}
#endif // ONLINE_JUDGE
int makeQuery(vector<int> &A, vector<int> &B){
    REP(i, A.size())a[i] = A[i];
    REP(j, B.size())b[j] = B[j];
    return query(A.size(), B.size(), a, b);
}
void run(int N){
    n = N;
    dsu = DSU(n);
    while(true){
        vector<int> a, b;
        for(int bit = 0; Mask(bit) <= n; ++bit){
            a.clear();
            b.clear();
            FOR(v, 1, n)if(Bit(dsu.find_root(v), bit)) a.emplace_back(v);
            else b.emplace_back(v);
            if(makeQuery(a, b)) break;
        }
        int l = 0, r = a.size() - 1;
        while(l < r){
            int mid = l + r >> 1;
            vector<int> Left;
            FOR(i, l, mid)Left.emplace_back(a[i]);
            if(makeQuery(Left, b)){
                r = mid;
            }else l = mid + 1;
        }
        int firstNode = a[l];
        l = 0, r = b.size() - 1;
        while(l < r){
            int mid = l + r >> 1;
            vector<int> Right;
            FOR(i, l, mid) Right.emplace_back(b[i]);
            if(makeQuery(a, Right)){
                r = mid;
            }else l = mid + 1;
        }
        int secondNode = b[l];
//        cout << "guess " << firstNode << ' ' << secondNode << '\n';
        setRoad(firstNode, secondNode);
        dsu.unite(firstNode, secondNode);
    }

//    assert(0);
}
#ifndef ONLINE_JUDGE
void fuck(){
    int n; cin >> n;
    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;

        edge.emplace_back(u, v);
    }
    run(n);
    cout << 1;
}
int main(){
    #define LOVE "icc"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}

#endif // ONLINE_JUDGE


