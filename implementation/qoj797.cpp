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
const int maxN = 1e4 + 5;
const int maxQ = 1e2 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, l, a[maxN], ans[maxN][maxQ], s[maxN], q;
int cur[maxN];
int posQuery[maxN];
struct query{
    int k, id;
    bool operator < (const query &rhs) const{
        return k > rhs.k;
    }
}ask[maxQ];
int res[maxN][maxQ];
void process(){
    cin >> n >> l;
    FOR(i, 1, n)cin >> a[i];
    cin >> q;
    FOR(i, 1, q){
        cin >> ask[i].k;
        ask[i].id = i;
    }
    sort(ask + 1, ask + 1 + q);
    FOR(i, 1, q){
        posQuery[ask[i].k] = i;
    }
    REP(i, n, 0)maximize(posQuery[i], posQuery[i + 1]);
    FOR(i, 2, n){
        FOR(j, 1, min(l, i - 1)){
            if(a[i] != a[j])s[i - j + 1]++;
        }
    }
    FOR(i, n - l + 2, n)s[i] = 0;
    FOR(j, 2, n - l + 1){
        ans[1][1]++;
        ans[1][posQuery[s[j]] + 1]--;
    }
    FOR(i, 2, n - l + 1){
        REP(j, n - l + 1, i + 1){
            s[j] = s[j - 1] - (a[j - 1] != a[i - 1]) + (a[j + l - 1] != a[i + l - 1]);
            ans[i][1]++;
            ans[i][posQuery[s[j]] + 1]--;
        }
    }

    memset(s, 0, sizeof s);
    REP(i, n - 1, 1){
        REP(j, n, max(n - l + 1, i + 1)){
            if(a[i] != a[j])s[n - l - j + i + 1]++;
        }
    }
    FOR(i, n - l + 2, n)s[i] = 0;
    FOR(i, 1, n - l){
        ans[n - l + 1][1]++;
        ans[n - l + 1][posQuery[s[i]] + 1]--;
    }
    REP(i, n - l, 1){
        FOR(j, 1, i - 1){
            s[j] = s[j + 1] - (a[j + l] != a[i + l]) + (a[j] != a[i]);
            ans[i][1]++;
            ans[i][posQuery[s[j]] + 1]--;
        }
    }
    FOR(i, 1, n - l + 1){
        FOR(j, 1, q){
            ans[i][j] += ans[i][j - 1];
        }
        FOR(j, 1, q)res[i][ask[j].id] = ans[i][j];
    }
    FOR(j, 1, q){
        FOR(i, 1, n - l + 1)cout << res[i][j] << ' ';
        cout << '\n';
    }
}
#define LOVE "lottery"
int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
////        freopen(LOVE".out", "w", stdout);
//    }
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




