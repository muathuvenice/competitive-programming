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
const int maxN = 300 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, m, k, a[maxN], b[maxN];
string notValid = "Impossible";

namespace ac{
    int f[maxN * maxN];
    void solve(){
        int sumA = 0, sumB = 0;
        FOR(i, 1, n)sumA += a[i];
        FOR(i, 1, m)sumB += b[i];
        FOR(i, 1, sumB)f[i] = -inf;
        FOR(i, 1, m){
            REP(sum, sumB, b[i]){
                maximize(f[sum], f[sum - b[i]] + min(b[i], n));
            }
        }
        FOR(s, sumA, sumB){
            if(f[s] >= n * k){
                cout << s - sumA;
                return;
            }
        }
        cout << notValid;
    }
}
void process(){
    cin >> n >> m >> k;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 1, m)cin >> b[i];
    if(m < k || *min_element(a + 1, a + 1 + n) < k){
        cout << notValid;
        return;
    }
    return ac :: solve();
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



