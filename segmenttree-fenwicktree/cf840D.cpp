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
#define Ctz(x) __builtin_ctz(x) // so luong so 0 tinh tu ben phai
#define Ctzll(x) __builtin_ctzll(x)
#define Clz(x) __builtin_clz(x) // so luong so 0 tinh tu ben trai
#define Clzll(x) __builtin_clzll(x)
inline bool maximize(int &u, int v){
    return v > u ? u = v, true : false;
}
inline bool minimize(int &u, int v){
    return v < u ? u = v, true : false;
}
inline bool maximizell(long long &u, long long v){
    return v > u ? u = v, true : false;
}
inline bool minimizell(long long &u, long long v){
    return v < u ? u = v, true : false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 3e5 + 5;
const int logN = __lg(maxN);
const int maxNlogN = maxN * (logN + 2);
const int inf = 1e9;
const long long infll = 1e18;
int n, a[maxN], q;
int numNode, rootVersion[maxN];
int len, k;
struct Node{
    int lc, rc, sum;
}it[maxNlogN];
void update(int cur, int pre, int l, int r, int p){
    if(l == r){
        it[cur].sum = it[pre].sum + 1;
        return;
    }
    int mid = l + r >> 1;
    if(p <= mid){
        it[cur].rc = it[pre].rc;
        it[cur].lc = ++numNode;
        update(it[cur].lc, it[pre].lc, l, mid, p);
    }else{
        it[cur].lc = it[pre].lc;
        it[cur].rc = ++numNode;
        update(it[cur].rc, it[pre].rc, mid + 1, r, p);
    }
    it[cur].sum = it[it[cur].lc].sum + it[it[cur].rc].sum;
}
int get(int lid, int rid, int k, int len, int l, int r){
    if((it[rid].sum - it[lid].sum) * k <= len) return -1;
    if(l == r) return l;
    int mid = l + r >> 1;
    int v = get(it[lid].lc, it[rid].lc, k, len, l, mid);
    if(v != -1) return v;
    return get(it[lid].rc, it[rid].rc, k, len, mid + 1, r);
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n){
        cin >> a[i];
        ++numNode;
        rootVersion[i] = numNode;
        update(rootVersion[i], rootVersion[i - 1], 1, n, a[i]);
    }
    while(q--){
        int l, r;
        cin >> l >> r >> k;
        len = r - l + 1;
        cout << get(rootVersion[l - 1], rootVersion[r], k, len, 1, n) << '\n';
    }
}
#define LOVE ""
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





