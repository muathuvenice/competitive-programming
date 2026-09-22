#ifdef ONLINE_JUDGE
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
const int maxN = 500 + 5;
const int inf = 1e9;
const long long infll = 1e18;
bitset<502> f[2][502], start[502];
char c[maxN][maxN];
int numRow, numCol, m;
void process(){
    cin >> numRow >> numCol >> m;
    FOR(i, 1, numRow){
        FOR(j, 1, numCol){
            cin >> c[i][j];
            if(c[i][j] == '.'){
                f[0][i][j] = start[i][j] = 1;
            }
        }
    }
    int cur = 0, pre = 1;
    FOR(i, 1, m){
        cur ^= 1;
        pre ^= 1;
        char c;
        cin >> c;
        if(c == '?'){
            FOR(i, 1, numRow)f[cur][i] = (f[pre][i - 1] | f[pre][i + 1] | (f[pre][i] >> 1) | f[pre][i] << 1) & start[i];
        }else{
            if(c == 'N')FOR(i, 1, numRow)f[cur][i] = f[pre][i + 1] & start[i];
            else if(c == 'S')FOR(i, 1, numRow)f[cur][i] = f[pre][i - 1] & start[i];
            else if(c == 'E')FOR(i, 1, numRow)f[cur][i] = (f[pre][i] << 1) & start[i];
            else FOR(i, 1, numRow)f[cur][i] = (f[pre][i] >> 1) & start[i];
        }
    }
    int answer = 0;
    FOR(i, 1, numRow)answer += f[cur][i].count();
    cout << answer;

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





