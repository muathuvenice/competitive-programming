#ifdef ONLINE_JUDGE
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
#define assert(x) if(!(x)) cout << "error", exit(0)
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

inline long long modI(long long a, long long m) {
    return a <= 1 ? a : (1 - modI(m % a, a) * m) / a + m;
}

const int mxN = 500;

int n, a[mxN], b[mxN];
long long dp[mxN + 1][2 * mxN];
long long c[2 * mxN][mxN + 1];
vector<int> comp;

void fuck(){

    cin >> n;
    REP(i, n) {
        cin >> a[i] >> b[i];
        a[i]--;
        comp.emplace_back(a[i]);
        comp.emplace_back(b[i]);
    }
    sort(all(comp));
    uni(comp);
    FOR(i, 1, (int)comp.size() - 1) {
        c[i][1] = comp[i] - comp[i - 1];
        FOR(j, 2, n) {
            long long d = comp[i] - comp[i - 1];
            c[i][j] = c[i][j - 1] * (d + j - 1) % mod * fastPow(j, mod - 2) % mod;
        }
    }

    REP(i, comp.size()) dp[0][i] = 1;
    FOR(i, 1, n) {
        dp[i][0] = 1;
        FOR(j, 1, (int)comp.size() - 1) {
            dp[i][j] = dp[i][j - 1];
            int n2 = 0;
            FORD(k, i, 1) {

                if (comp[j] > a[k - 1] && comp[j] <= b[k - 1]) {
                    ++n2;
                    dp[i][j] = (dp[i][j] + dp[k - 1][j - 1] * c[j][n2]) % mod;
                }
            }
        }
    }

    cout << (dp[n][comp.size() - 1] - 1 + mod) % mod << "\n";
}
int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



