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
int n;
char s[maxN];
bool f[maxN];
pair<int, int> seg[maxN];
int len[maxN];
void process(){
    cin >> n;
    int cnt = 0;
    FOR(i, 1, n)cin >> s[i];
    FOR(i, 1, n){
        if(s[i] == '0'){
            int j = i + 1;
            while(j <= n && s[j] == '0')++j;
            seg[++cnt] = mp(i, j - 1);
            len[cnt] = j - i;
            i = j;
        }
    }
    if(cnt == 0){
        cout << "YES\n";
        return;
    }
    f[0] = true;
    FOR(i, 1, cnt)f[i] = false;
    f[1] = seg[1].first == 1 || seg[1].second == n || len[1] >= 2;
    FOR(i, 2, cnt){
        if(len[i] >= 2)f[i] = f[i - 1];
        if(seg[i].second == n)f[i] = f[i - 1];
        if(f[i - 1]){
            if(seg[i].first - seg[i - 1].second == 2){
                if(len[i - 1] >= 2)f[i] = f[i - 1];
                else f[i] = max(f[i], f[i - 2]);
            }
        }else{
            if(seg[i].first - seg[i - 1].second == 2){
                f[i] = max(f[i - 2], f[i]);
            }else{
                f[i] = false;
            }
        }
    }
//    FOR(i, 1, cnt){
//        cout << f[i] << ' ';
//    }cout << '\n';
    cout << (f[cnt] ? "YES" : "NO") << '\n';
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
    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
/*
1
9
100100101
*/



