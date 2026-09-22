#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
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
#define parity(x) __builtin_parity(x)
#define parityll(x) __builtin_parityll(x)
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
const int maxN = 1e3 + 4;
const int maxP = 5e5 + 4;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int k, p;
long long val[maxN][maxN][19];
long long sum[maxN][maxN];
struct Ask{
    int xa, ya, xb, yb, w;
};
vector<Ask> query[maxP];
vector<pair<int, int>> ask[maxP];
long long fw[maxN][maxN];
void update(int x, int y, int w){
    for(int a = x; a <= k; a += a & -a){
        for(int b = y; b <= k; b += b & -b){
            fw[a][b] += w;
        }
    }
}
long long get(int x, int y){
    long long res = 0;
    for(int a = x; a > 0; a &= a - 1){
        for(int b = y; b > 0; b &= b - 1){
            res += fw[a][b];
        }
    }
    return res;
}
int ans[maxN][maxN];
void process(){
    cin >> k >> p;
    FOR(i, 1, k)FOR(j, 1, k)ans[i][j] = -1;
    int LOG = __lg(p) + 1;
    FOR(i, 1, p){
        int xa, ya, xb, yb, t, w;
        cin >> xa >> ya >> xb >> yb >> t >> w;
        sum[xa][ya] += w;
        sum[xa][yb + 1] -= w;
        sum[xb + 1][ya] -= w;
        sum[xb + 1][yb + 1] += w;
        REP(b, LOG){
            if(Bit(t, b)){
                val[xa][ya][b] += w;
                val[xa][yb + 1][b] -= w;
                val[xb + 1][ya][b] -= w;
                val[xb + 1][yb + 1][b] += w;
            }
        }
        query[t].push_back({xa, ya, xb, yb, w});
    }
    FOR(i, 1, k){
        FOR(j, 1, k){
            sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
            int mask = 0;
            REP(b, LOG){
                val[i][j][b] += val[i][j - 1][b] + val[i - 1][j][b] - val[i - 1][j - 1][b];
                if(val[i][j][b] * 2 > sum[i][j]) mask |= Mask(b);
            }
            if(mask <= p)ask[mask].emplace_back(i, j);
        }
    }
    FOR(t, 1, p){
        for(auto[xa, ya, xb, yb, w] : query[t]){
            update(xa, ya, w);
            update(xa, yb + 1, -w);
            update(xb + 1, ya, -w);
            update(xb + 1, yb + 1, w);
        }
        for(auto[u, v] : ask[t]){
            if(get(u, v) * 2 > sum[u][v]) ans[u][v] = t;
        }
        for(auto[xa, ya, xb, yb, w] : query[t]){
            update(xa, ya, -w);
            update(xa, yb + 1, w);
            update(xb + 1, ya, w);
            update(xb + 1, yb + 1, -w);
        }
    }
    FOR(i, 1, k){
        FOR(j, 1, k){
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
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






