#ifdef ONLINE_JUDGE
#include "art.h"
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
using namespace std;
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
#define parity(x) __builtin_parity(x)
#define parityll(x) __builtin_parityll(x)
template <class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template <class X, class Y>
    bool maximize(X &x, Y y) {
        return x < y ? x = y, true : false;
    }
template <class T>
    void printVec(vector<T> &vec){
        for(T x : vec)cerr << x << ' ';
        cerr << '\n';
    }
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
const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 4e3 + 1;
int n;

#ifndef ONLINE_JUDGE
vector<int> ranking;
int pos[maxN];
int publish(vector<int> R){
    int answer = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(pos[R[j]] > pos[R[i]]) ++answer;
        }
    }
//    printVec(R);
//    cerr << answer << '\n';
    return answer;
}
void answer(vector<int> R){
//    printVec(R);
//    printVec(ranking);
//    assert(R == ranking);
    if(R == ranking) cout << 1;
    else cout << 0;
}
#endif // ONLINE_JUDGE
void solve(int N){
    n = N;
    vector<int> cur(n);
    FOR(i, 1, n) cur[i - 1] = i;
    int curInv = publish(cur);
    vector<int> res(n, 0);
    for(int i = 1; i < n; ++i){
        int f = cur[0];
        for(int j = 1; j < n; ++j) cur[j - 1] = cur[j];
        cur[n - 1] = f;
//        printVec(cur);
        int preInv = curInv;
        curInv = publish(cur);
        int p = (preInv - curInv + n + 1) / 2;
        res[p - 1] = cur[n - 1];
    }
    for(int i = 0; i < n; ++i) if(res[i] == 0) res[i] = n;
//    printVec(res);
    answer(res);
}
#ifndef ONLINE_JUDGE

void fuck(){
    int n;
    cin >> n;
//    assert(n <= 40);
    FOR(i, 1, n){
        int u;
        cin >> u;
        ranking.emplace_back(u);
        pos[u] = i - 1;
    }
    solve(n);
}
int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}


#endif // ONLINE_JUDGE

