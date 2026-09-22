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
const int maxN = 3e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, L, R, a[maxN];
namespace subtask1{
    bool check(){
        return n <= 5000;
    }
    long long f[maxN];
    void solve(){
        f[0] = 0;
        FOR(i, 1, n){
            f[i] = -infll;
            int Max = -inf, Min = inf;
            FORD(j, i, max(i - R + 1, 1)){
                maximize(Max, a[j]);
                minimize(Min, a[j]);
                if(i - j + 1 >= L)maximizell(f[i], f[j - 1] + Max - Min);
            }
            cout << f[i] << ' ';
        }
        cout << (f[n] <= - 5 * 1000000000000000 ? -1 : f[n]);
    }
}
namespace subtask2{
    long long it[maxN << 2], lz[maxN << 2];
    void push(int id){
        if(lz[id] == 0) return;
        FOR(x, id << 1, id << 1 | 1){
            lz[x] += lz[id];
            it[x] += lz[id];
        }
        lz[id] = 0;
    }
    void update(int id, int l, int r, int u, int v, long long w){
        if(l > v || r < u) return;
        if(l >= u && r <= v){
            it[id] += w;
            lz[id] += w;
            return;
        }
        push(id);
        int mid = l + r >> 1;
        update(id << 1, l, mid, u, v, w);
        update(id << 1 | 1, mid + 1, r, u, v, w);
        it[id] = max(it[id << 1], it[id << 1 | 1]);
    }
    long long get(int id, int l, int r, int u, int v){
        if(l > v || r < u) return -infll;
        if(l >= u && r <= v) return it[id];
        push(id);
        int mid = l + r >> 1;
        return max(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
    }
    long long f[maxN];
    int leftMax[maxN], leftMin[maxN];
    void solve(){
        stack<int> Max, Min;
        long long answer;
        FOR(i, 1, n){
            while(!Max.empty() && a[Max.top()] < a[i]){
                int p = Max.top();
                update(1, 1, n, leftMax[p], p, - a[p]);
                Max.pop();
            }
            while(!Min.empty() && a[Min.top()] > a[i]){
                int p = Min.top();
                update(1, 1, n, leftMin[p], p, + a[p]);
                Min.pop();
            }
            leftMax[i] = Max.empty() ? 1 : Max.top() + 1;
            leftMin[i] = Min.empty() ? 1 : Min.top() + 1;
            update(1, 1, n, leftMax[i], i, a[i]);
            update(1, 1, n, leftMin[i], i, -a[i]);
//
//            FOR(j, 0, i - 1)cout << get(1, 0, n, j, j) << ' ';cout << '\n';
            Max.emplace(i);
            Min.emplace(i);
            update(1, 1, n, i, i, f[i - 1]);
            f[i] = get(1, 1, n, max(i - R + 1, 1), min(i - L + 1, i));
//            cout << f[i] << ' ';


        }
//        cout << get(1, 0, n, n, n) << '\n';
        cout << f[n];
    }
}
/*
-1000000000000000000 7 7 10 11 11 14 15 15
*/
void process(){
    cin >> n >> L >> R;
    FOR(i, 1, n)cin >> a[i];
//    return subtask1 :: solve();
    return subtask2 :: solve();
}
#define LOVE "disparity"
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




