// my solution https://docs.google.com/document/d/1g3JZVD7vrX8Ff64moZq_hsAeSohorfmzf3g15rBQKcc/edit?tab=t.0
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
#define Clz(x) __builtin_clz(x) // first bit
#define Clzll(x) __builtin_clzll(x)

inline bool maximize(int &u, int v){
    return v > u ? u = v, true : false;
}
inline bool minimize(int &u, int v){
    return v < u ? u = v, true : false;
}
inline bool maximizell(long long &u, long long v){
    return v > u ? u = v, true : false;
}
inline bool minimizell(long long &u, long long v){
    return v < u ? u = v, true : false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, a[maxN], k[maxN];
namespace subtask12{
    bool check(){
        return n <= 5000;
    }
    int f[5001], trace[5001];
    void solve(){
        FOR(i, 1, n){
            f[i] = 1;
            for(int j = 1; j < i; ++j){
                if(Cnt(a[i] & a[j]) == k[i]){
                    if(maximize(f[i], f[j] + 1)){
                        trace[i] = j;
                    }
                }
            }
        }
        int mx = *max_element(f + 1, f + 1 + n);
        cout << mx << '\n';
        vector<int> ans;
        for(int i = n; i >= 1; --i){
            if(f[i] == mx){
                while(i > 0){
                    ans.emplace_back(i);
                    i = trace[i];
                }
            }
        }
        reverse(all(ans));
        for(int p : ans)cout << p << ' ';
    }
}
/*
4
1 2 3 4
10 0 1 0

5
5 3 5 3 5
10 1 20 1 20
*/
namespace subtask3{
    bool check(){
        return *max_element(a + 1, a + 1 + n) < Mask(8);
    }
    int trace[maxN], f[maxN], dp[Mask(8)];
    int last[Mask(8)];
    void solve(){
        int maxMask = Mask(8) - 1;
        for(int i = 1; i <= n; ++i){
            f[i] = 1;
            FOR(mask, 0, maxMask){
                if(Cnt(mask & a[i]) == k[i]){
                    if(maximize(f[i], dp[mask] + 1)){
                        trace[i] = last[mask];
                    }
                }
            }
            if(maximize(dp[a[i]], f[i]))last[a[i]] = i;
        }
        int mx = *max_element(f + 1, f + 1 + n);
        cout << mx << '\n';
        vector<int> ans;
        for(int i = n; i >= 1; --i){
            if(f[i] == mx){
                while(i > 0){
                    ans.emplace_back(i);
                    i = trace[i];
                }
                break;
            }
        }
        reverse(all(ans));
        for(int p : ans)cout << p << ' ';
    }
}
namespace subtask4{
    int f[1 << 10][1 << 10][11];
    // f[lx][ry][k] = (len, end)
    // xet den a[i]
    // rx & ry = k
    // luu pair bi cham => luu chi so thoi
    int trace[maxN];
    int lbs[maxN];
    int BLOCK = 1 << 10;
    int cnt[1 << 10][1 << 10];
    void solve(){
        FOR(i, 0, BLOCK - 1){
            FOR(j, 0, BLOCK - 1){
                cnt[i][j] = Cnt(i & j);
            }
        }
        FOR(i, 1, n){
            int l = a[i] >> 10;
            int r = a[i] % (BLOCK);
            lbs[i] = 1;
            for(int mask = 0; mask < BLOCK; ++mask){
                int needR = k[i] - cnt[l][mask];
                if(needR < 0 || needR > 10) continue;
                if(maximize(lbs[i], lbs[f[mask][r][needR]] + 1)){
                    trace[i] = f[mask][r][needR];
                }
            }
            for(int mask = 0; mask < BLOCK; ++mask){
                int needR = cnt[mask][r];
                if(lbs[f[l][mask][needR]] < lbs[i]){
                    f[l][mask][needR] = i;
                }
            }
        }
        int mx = *max_element(lbs + 1, lbs + 1 + n);
        cout << mx << '\n';
        vector<int> ans;
        for(int i = n; i >= 1; --i){
            if(lbs[i] == mx){
                while(i >= 1){
                    ans.emplace_back(i);
                    i = trace[i];
                }
            }
        }
        reverse(all(ans));
        for(int p : ans)cout << p << ' ';
    }
}
void process(){
    cin >> n;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 1, n)cin >> k[i];
//    if(subtask12 :: check()) return subtask12 :: solve();
//    if(subtask3 :: check()) return subtask3 :: solve();
    return subtask4 :: solve();
}
#define LOVE "lbs"
int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
//    }
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







