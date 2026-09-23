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
const int mod = 998244353;
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
const int maxN = 5e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, k, m;
int l[maxN], r[maxN], v[maxN];
int f[maxN], pref[maxN];
int MaxL[maxN];
int s[maxN];
void process(){
    cin >> n >> k >> m;
    FOR(i, 1, m){
        cin >> l[i] >> r[i] >> v[i];
    }
    int answer = 1;
    FOR(j, 0, k - 1){
        FOR(i, 1, n + 1)s[i] = 0, MaxL[i] = 0;
        FOR(i, 1, m){
            if(Bit(v[i], j)){
                s[l[i]]++;
                s[r[i] + 1]--;
            }else{
                maximize(MaxL[r[i] + 1], l[i]);
            }
        }
        FOR(i, 1, n + 1)maximize(MaxL[i], MaxL[i - 1]);
        FOR(i, 1, n + 1)s[i] += s[i - 1];
        f[0] = 1;
        pref[0] = 1;
        FOR(i, 1, n + 1){
            if(s[i] > 0) {
                f[i] = 0;
                pref[i] = pref[i - 1];
                continue;
            }
            f[i] = pref[i - 1];
            if(MaxL[i] > 0) sub(f[i], pref[MaxL[i] - 1]);
            pref[i] = pref[i - 1];
            add(pref[i], f[i]);
        }
        int sum = f[n + 1];
        answer = 1ll * answer * sum % mod;
    }
    cout << answer;
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






