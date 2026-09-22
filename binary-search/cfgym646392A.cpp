#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("popcnt")
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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
long long a[maxN];
int b[maxN], n, k;
long long c[maxN];
long long f[maxN];

bool check(long long x){
//    int sum = 0;
    FOR(i, 1, k)f[i] = 0;
    int sum = k;
    FOR(i, 1, n){
        long long t = a[i];
        while(t < 1ll * k * b[i]){
            if(!sum) return false;
            ++f[t / b[i] + 1];
            --sum;
            t += x;
        }
        if(sum < 0) return false;
    }
    FOR(i, 1, k){
        f[i] += f[i - 1];
        if(f[i] > i) return false;
    }
    return true;
}
void process(){
    cin >> n >> k;
    --k;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 1, n)cin >> b[i];
    long long answer = -infll, l = 0, r = 2e12;
//    check(5);
    while(l <= r){
        long long mid = l + r >> 1;
        if(check(mid)){
            answer = mid;
            r = mid - 1;
        }else l = mid + 1;
    }
    cout << (answer == -infll ? -1 : answer) << '\n';
}
#define LOVE "code"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
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





