#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
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
const int maxN = 18 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int m, n, r, c;
int a[maxN][maxN];
int sum[maxN][maxN];
int get(int u, int v, int x, int y){
    return sum[x][y] - sum[u - 1][y] - sum[x][v - 1] + sum[u - 1][v - 1];
}
namespace subtask1{
    bool check(){
        return max(m, n) <= 10;
    }
    int lastRow[maxN], lastCol[maxN];
    int answer = inf;
    int cnt = 0;
    void action(){
        ++cnt;
        int Max = -inf;
        FOR(i, 1, r){
            FOR(j, 1, c){
                maximize(Max, get(lastRow[i - 1] + 1, lastCol[j - 1] + 1, lastRow[i], lastCol[j]));
            }
        }
        minimize(answer, Max);
    }
    void BackTrackCol(int id){
        if(id == c){
            lastCol[id] = n;
            action();
            return;
        }
        FOR(j, lastCol[id - 1] + 1, n - c + id){
            lastCol[id] = j;
            BackTrackCol(id + 1);
        }
    }
    void BackTrackRow(int id){
        if(id == r){
            lastRow[r] = m;
            BackTrackCol(1);
            return;
        }
        FOR(j, lastRow[id - 1] + 1, m - r + id){

            lastRow[id] = j;
            BackTrackRow(id + 1);
        }
    }
    void solve(){
        BackTrackRow(1);
        cout << answer;
    }
}
namespace subtask2{
    int lastRow[maxN];
    int x;
    bool ok;
    bool ask(int u, int v){
        FOR(i, 1, r){
            if(get(lastRow[i - 1] + 1, u, lastRow[i], v) > x) return false;
        }
        return true;
    }
    void action(){
        int cntCol = 0;
        int i = 1;
        while(i <= n){
            int j = i;
            while(j <= n && ask(i, j))++j;
            if(j == i) return;
            // i -> j - 1
            ++cntCol;
            i = j;
        }
        if(cntCol <= c) ok = true;
    }
    void BackTrackRow(int id){
        if(id == r){
            lastRow[r] = m;
            action();
            return;
        }
        FOR(j, lastRow[id - 1] + 1, m - r + id){

            lastRow[id] = j;
            if(!ok) BackTrackRow(id + 1);
        }
    }

    void solve(){
        int l = 0, r = sum[m][n], res = inf;
        while(l <= r){
            x = l + r >> 1;
            ok = false;
            BackTrackRow(1);
            if(ok){
                res = x;
                r = x - 1;
            }else l = x + 1;
        }
        cout << res;
    }
}
void process(){
    cin >> m >> n >> r >> c;
    ++r;
    ++c;
    FOR(i, 1, m){
        FOR(j, 1, n){
            cin >> a[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
    return subtask2 :: solve();
}
#define LOVE "grid"
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




