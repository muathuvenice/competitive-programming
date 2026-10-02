// #define LOCAL
#include"MXORLIB.h"
#include <bits/stdc++.h>
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
        for(T x : vec)cout << x << ' ';
        cout << '\n';
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

const int maxN = 1e5 + 5;
int n;
vector<int> a;
#ifdef LOCAL
int get_n() {
    return n;
}
int max_xor(vector<int> &I, vector<int> &J) {
    int res = 0;
    for(int i : I) {
        for(int j : J) {
            res = max(res, a[i - 1] ^ a[j - 1]);
        }
    }
    return res;
}
void answer(int i, int j) {

    cout << i << ' ' << j << '\n';
}
#endif
int maxXor[17];
vector<int> ans;
void fuck(){
    #ifdef LOCAL
    cin >> n;
    a.assign(n, 0);
    for(int &v : a) cin >> v;
    #endif
    n = get_n();
    int max_Xor = -1;
    FOR(bit, 0, 31 - Clz(n)) {
        // cout << bit << '\n';
        vector<int> I, J;
        for(int i = 1; i <= n; ++i) {
            if(Bit(i, bit)) I.emplace_back(i);
            else J.emplace_back(i);
        }
        assert(!I.empty());
        assert(!J.empty());
        maxXor[bit] = max_xor(I, J);
        maximize(max_Xor, maxXor[bit]);

    }
    int xorAns = 0;
    FOR(bit, 0, 31 - Clz(n)) {
        if(maxXor[bit] == max_Xor) {
            xorAns |= Mask(bit);
        }
    }
    int fixedBit = 31 - Clz(xorAns);
    vector<int> I, J;
    for(int i = 1; i <= n; ++i)if(Bit(i, fixedBit)) I.emplace_back(i);
    else J.emplace_back(i);
    if(I.size() > J.size()) swap(I, J);
    while(I.size() > 1) {
        int mid = I.size() / 2;
        vector<int> Left(I.begin(), I.begin() + mid);
        vector<int> Right(I.begin() + mid, I.end());
        if(max_xor(Left, J) == max_Xor) I = Left;
        else I = Right;

    }
    int u = *I.begin();
    int v = u ^ xorAns;
    answer(u, v);
}

int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
       // freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
