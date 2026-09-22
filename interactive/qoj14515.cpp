#ifdef ONLINE_JUDGE
#include "cards.h"
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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int a[3];
namespace subtask1{
    long long solve(long long X, long long Y, long long Z){
        long long answer = 1;
        a[0] = X;
        a[1] = Y;
        a[2] = Z;
        int cur = a[0] < a[1] ? 0 : 1;
        if(a[2] < a[cur]) cur = 2;
        --a[0];
        --a[1];
        --a[2];
        while(true){
            int x = cur == 0 ? 1 : 0;
            int y = 3 ^ cur ^ x;
            if(a[x] >= 1 && a[y] >= 1){
                cur = a[x] < a[y] ? x : y;
                --a[x];
                --a[y];
                cout << "round " << answer + 1<< ' ';
                FOR(i, 0, 2)cout << a[i] << ' ';
                cout << '\n';
                ++answer;
                continue;
            }
            break;
        }
        return answer;
    }
}
namespace subtask5{
    long long solve(long long X, long long Y, long long Z){
        return 1 + (3 * X - 3) / 2;
    }
}
namespace ac{
    long long solve(long long X, long long Y, long long Z){
        long long l = 1, r = 2 * min({X, Y, Z});
        long long res = 0;
        while(l <= r){
            long long mid = l + r >> 1;
            if(max(mid - X, 0ll) + max(mid - Y, 0ll) + max(mid - Z, 0ll) < mid) {
                res = mid;
                l = mid + 1;
            }else r = mid - 1;
        }
        return res;
    }

}
long long maximum_score(int X, int Y, int Z) {
//    if(max({X, Y, Z}) <= 50) return subtask1 :: solve(X, Y, Z);
//    if(X == Y && Y == Z) return subtask5 :: solve(X, Y, Z);
    return ac :: solve(X, Y, Z);
}
#ifndef ONLINE_JUDGE
void process(){

    int x, y, z;
    cin >> x >> y >> z;
    cout << maximum_score(x, y, z);

}
#define LOVE "code"
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
    while(t--) process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
#endif


