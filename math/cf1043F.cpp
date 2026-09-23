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
#define Clz(x) __builtin_clz(x) // first bit
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
int mod;
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
const int inf = 1e9;
const long long infll = 1e18;
int n, a[maxN];
vector<int> divisor[maxN];
int cnt[maxN];
int numMul[maxN];
int fact[maxN], infact[maxN];
int C(int k, int n){
    if(k > n) return 0;
    return 1ll * fact[n] * infact[n - k] % mod * infact[k] % mod;
}
int numWays[maxN];
void process(){
    int N = 3e5;
    cin >> n;

    FOR(i, 1, n)cin >> a[i], cnt[a[i]]++;
    FOR(i, 1, N){
        for(int j = i; j <= N; j += i){
            numMul[i] += cnt[j];
        }
    }
    mod = 1e9 + 7;
    fact[0] = 1;
    FOR(i, 1, n)fact[i] = 1ll * fact[i - 1] * i % mod;
    infact[n] = fastPow(fact[n], mod - 2);
    REP(i, n, 1){
        infact[i - 1] = 1ll * infact[i] * i % mod;
    }
    FOR(i, 1, 7){
        memset(numWays, 0, sizeof numWays);
        REP(val, N, 1){
            numWays[val] = C(i, numMul[val]);
            for(int k = 2; k * val <= N; ++k){
                sub(numWays[val], numWays[k * val]);
            }
        }
        if(numWays[1] > 0){
            cout << i;
            return;
        }
    }
    cout << -1;
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






