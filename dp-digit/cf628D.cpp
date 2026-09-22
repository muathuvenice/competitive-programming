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
int m, d;
string a, b;
int power[maxN];
int f[2001][2001][2][2], sz;
vector<int> l, r;
int calc(int id, int sum, bool smaller, bool larger){
    if(id == sz) return f[id][sum][smaller][larger] = sum == 0;
    if(f[id][sum][smaller][larger] != -1) return f[id][sum][smaller][larger];
    int res = 0;
    int limLow = larger ? 0 : l[id + 1];
    int limHigh = smaller ? 9 : r[id + 1];
    if(id & 1){
        if(d >= limLow && d <= limHigh)
        add(res, calc(id + 1, (sum + d * power[sz - (id + 1)]) % m, smaller || (d < r[id + 1]), larger || (d > l[id + 1])));
    }
    else{
        FOR(x, limLow, limHigh){
            if(x == d) continue;
            add(res, calc(id + 1, (sum + x * power[sz - (id + 1)]) % m, smaller || (x < r[id + 1]), larger || (x > l[id + 1])));

        }
    }

    return f[id][sum][smaller][larger] = res;
}
void process(){
    cin >> m >> d;
    cin >> a >> b;
    sz = b.size();
    a = '0' + a;
    b = '0' + b;
    for(char c : a)l.emplace_back(c - '0');
    for(char c : b)r.emplace_back(c - '0');
    power[0] = 1;
    FOR(i, 1, sz){
        power[i] = 10 * power[i - 1] % m;
    }
    memset(f, -1, sizeof f);
    cout << calc(0, 0, 0, 0);
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




