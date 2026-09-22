#ifdef ONLINE_JUDGE
#include "gcd.h"
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
const int mod = 998244353;
inline int fastPow(int a, int n, int mod){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1, mod);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){ u += v; if(u >= mod) u -= mod; }
inline void sub(int &u, int v){ u -= v; if(u < 0) u += mod; }
const int maxN = 5e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, k, v;
int a[maxN];
int pref[maxN], suff[maxN];
long long sum[maxN];
int cnt[30];
int calc(int val){
    int answer = 0;
    REP(i, 29, 0){
        int c = cnt[i];
        if(Bit(val, i)) c = v + 1 - c;

        add(answer, 1ll * c * Mask(i) % mod);
    }
    return answer;
}
int pos[60];
int calculate_sum(int N, int K, int V, vector<int> A){
    FOR(i, 0, 29){
        cnt[i] = (V + 1) / Mask(i + 1) * Mask(i) + max(0, (V + 1) % Mask(i + 1) - Mask(i));
    }
    n = N, k = K, v = V;
    FOR(i, 1, n)a[i] = A[i - 1];
    FOR(i, 1, n){
        pref[i] = __gcd(pref[i - 1], a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    suff[n + 1] = 0;
    REP(i, n, 1)suff[i] = __gcd(suff[i + 1], a[i]);
    pos[1] = 1;
    int c = 1;
    FOR(i, 2, n){
        if(suff[i - 1] != suff[i]){
            pos[++c] = i;
        }
    }
    pos[c + 1] = n + 1;
    int answer = 0;
    FOR(l, 1, n){
        REP(i, c, 1){
            int r = pos[i + 1] - 1;
            int res = max(pos[i], l + 1);
            if(r <= l) break;
            int g = __gcd(pref[l], suff[res]);
            int valXor = fastPow(g, k, 1 << 30);
            int remG = fastPow(g, k, mod);
            remG -= valXor;
            remG %= mod;
            if(remG < 0) remG += mod;
            remG = 1ll * remG * (v + 1) % mod;
            valXor = calc(valXor);

            add(answer, (1ll * (r - res + 1) * a[l] + sum[r] - sum[res - 1]) % mod * (remG + valXor) % mod);
        }
    }
    return answer;
}
/*

1 318
1 10
2 5
2 4
3 5


1 5
1 5
1 30
2 4
2 5
3 5

1 54
1 30
2 48
132
*/
#ifndef ONLINE_JUDGE
void process(){
    int N, K, V;
    cin >> N >> K >> V;

    vector<int> A(N);
    for(int &v : A)cin >> v;
    cout << calculate_sum(N, K, V, A);
}
#define LOVE "gcd"
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
#endif // ONLINE_JUDGE




