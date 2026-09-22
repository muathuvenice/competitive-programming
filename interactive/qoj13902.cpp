#include "souvenirs.h"
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
const int maxN = 1e2 + 5;
const int inf = 1e9;
const long long infll = 1e18;
//int N;
//long long P[maxN];
//pair<vector<int>, long long> transaction(long long M){
//    vector<int> res;
////    if(M < P[N - 1]){
////        cerr << M << "\n";
////        exit(0);
////    }
//    assert(M >= P[N - 1]);
//    assert(M < P[0]);
//    FOR(i, 0, N - 1){
//        if(M >= P[i]){
//            res.emplace_back(i);
//            M -= P[i];
//        }
//    }
//    return mp(res, M);
//}
int n;
int Q[maxN];
using T = pair<vector<int>, long long>;
long long p[maxN];
void dfs(long long cost){
    T val = transaction(cost);
    cost -= val.second;
    int cnt = val.first.size();
    for(int u : val.first)Q[u]++;
    for(int i = val.first.size() - 1; i > 0; --i){
        int u = val.first[i];
        if(p[u] == 0){
            dfs(cost / cnt);
        }
        cost -= p[u];
        --cnt;
    }
    p[val.first[0]] = cost;
    for(int i = val.first[0] + 1; i <= n - 1; ++i){
        if(p[i] == 0) dfs(p[i - 1] - 1);
    }
}
void buy_souvenirs(int N, long long P0) {
    n = N;
    p[0] = P0;
    dfs(P0 - 1);
    FOR(i, 1, n - 1){
        while(Q[i] < i){
            T val = transaction(p[i]);
            ++Q[i];
        }
    }
    return;
}
//void process(){
//    cin >> N;
//    FOR(i, 0, N - 1) cin >> P[i];
//    buy_souvenirs(N, P[0]);
//    FOR(i, 0, N - 1)assert(p[i] == P[i]);
//    FOR(i, 0, N - 1) cerr << p[i] << ' ' << P[i] << '\n';
//    FOR(i, 0, N - 1)cerr << Q[i] << ' ';
//    FOR(i, 0, N - 1) assert(Q[i] == i);
//}
//#define LOVE "souvenirs"
//int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
//    }
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
//
//    int t = 1;
////    cin >> t;
//    while(t--)
//        process();
////    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
//    return 0;
//}
//
//



