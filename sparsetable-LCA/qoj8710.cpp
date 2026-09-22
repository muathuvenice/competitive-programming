#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
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
const int maxN = 4e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n;
long long m;
struct item{
    long long s, e;
    bool operator < (const item &rhs) const{
        return s < rhs.s;
    }
}a[maxN];
int Max[maxN][19], lg[maxN];
long long l[maxN], r[maxN];
int query(int u, int v){
    return r[u] > r[v] ? u : v;
}
int get(int l, int r){
    int k = lg[r - l + 1];
    return query(Max[l][k], Max[r - Mask(k) + 1][k]);
}
int nxt[maxN][19];
void process(){
    cin >> n >> m;
    FOR(i, 1, n){
        cin >> a[i].s >> a[i].e;
        if(a[i].s > a[i].e)a[i].e += m;
    }
    sort(a + 1, a + 1 + n);
    FOR(i, 1, n)a[i + n] = a[i];
    FOR(i, 1, n){
        l[i] = a[i].s;
        r[i] = a[i].e;
//        cerr << l[i] << ' ' << r[i] << '\n';
    }
    FOR(i, n + 1, 2 * n){
        a[i].s += m;
        a[i].e += m;
        l[i] = a[i].s;
        r[i] = a[i].e;
//        cerr << l[i] << ' ' << r[i] << '\n';
    }
    FOR(i, 1, 2 * n)Max[i][0] = i;
    FOR(i, 2, 2 * n)lg[i] = lg[i >> 1] + 1;
    FOR(j, 1, lg[2 * n])FOR(i, 1, 2 * n - Mask(j) + 1)Max[i][j] = query(Max[i][j - 1], Max[i + Mask(j - 1)][j - 1]);

    FOR(i, 1, 2 * n){
        int x = upper_bound(l + 1, l + 1 + 2 * n, l[i]) - l;
        int y = upper_bound(l + 1, l + 1 + 2 * n, r[i]) - l;
        --y;
//        cerr << x << ' ' << y << '\n';
        if(x <= y && y <= 2 * n){
            nxt[i][0] = get(x, y);
        }
    }
    FOR(j, 1, lg[2 * n]){
        FOR(i, 1, n * 2){
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
//    FOR(i, 1, n){
//        FOR(j, 0, lg[2 * n]){
//            cout << i << ' ' << j << ' ' << nxt[i][j]  << '\n';
//        }
//    }
    int answer = inf;
    FOR(i, 1, n){
        int sum = 0;
        int p = i;
        int s = i;
        REP(i, lg[2 * n], 0){
            if(nxt[p][i] <= 2 * n && nxt[p][i] >= 1 && r[nxt[p][i]] - l[s] < m){
                sum += Mask(i);
                p = nxt[p][i];
            }
        }
//        cout << "query\n";
//        cout << i << ' ' << p << '\n';
//        cout << r[nxt[p][0]] << '\n';
//        cout << sum << '\n';
        if(nxt[p][0] >= 1 && nxt[p][0] <= 2 * n && r[nxt[p][0]] - l[s] >= m)minimize(answer, sum + 2);
    }
    cout << (answer == inf ? -1 : answer);
}
#define LOVE "fire"
int32_t main(){
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




