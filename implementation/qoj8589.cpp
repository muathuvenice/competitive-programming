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
const int maxN = 1e3 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, c;
pair<int, int> a[2 * maxN];
bool used[2 * maxN];
void process(){
    cin >> n >> c;
    FOR(i, 1, n)cin >> a[i].first, a[i].second = 1;
    FOR(i, n + 1, 2 * n)cin >> a[i].first, a[i].second = -1;
    sort(a + 1, a + 1 + 2 * n);
    long long answer = 0;
    vector<int> operation;
    while(true){
        int cnt = 0, cur = 0;
        int numOperations = 0;
        bool needReturn = false;
        vector<int> curOp;
        FOR(i, 1, 2 * n){
            if(used[i]) continue;
            int curCnt = cnt + a[i].second;
            if(curCnt < 0) needReturn = true;
            if(min(abs(cnt), abs(curCnt)) < c){
                curOp.emplace_back(a[i].first);
                used[i] = true;
                if(cnt != 0) answer += abs(cur - a[i].first);
                cur = a[i].first;
                if(curCnt == 0) break;
            }
            cnt = curCnt;
        }
        if(curOp.empty()) break;
        if(needReturn)reverse(all(curOp));
        operation.insert(operation.end(), all(curOp));
    }
    cout << answer << '\n';
    for(int p : operation)cout << p << ' ';
}
/*
3 2
12 14 4
9 5 8
*/
#define LOVE "explosives"
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





