#ifdef ONLINE_JUDGE
#include "coreputer.h"
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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";

int n, totCores = 0;
#ifndef ONLINE_JUDGE
vector<int> ans;
int cnt;
int run_diagnostic(vector<int> t){
    int tagged = 0;
    ++cnt;

    for(int &u : t)tagged += ans[u];
    int untagged = totCores - tagged;
    if(tagged > untagged) return 1;
    if(tagged == untagged) return 0;
    return -1;
}
#endif // ONLINE_JUDGE
vector<int> malfunctioning_cores(int N){
    n = N;
    vector<int> res(n, 0);
    vector<int> cans;
    int l = 0, r = n - 2, ans = -1;
    int last = -1;
    while(l <= r){
        int mid = l + r >> 1;
        cans.clear();
        for(int i = 0; i <= mid; ++i)cans.emplace_back(i);
        int cur = run_diagnostic(cans);
        if(cur != 1){
            last = cur;
            ans = mid;
            l = mid + 1;
        }else r = mid - 1;
    }
    if(ans == -1){
        res[0] = 1;
        return res;
    }
    if(last == -1){
        cans.clear();
        if(ans + 1 < n) res[ans + 1] = 1;
        for(int i = 0; i <= ans; ++i)cans.emplace_back(i);
        for(int i = ans + 2; i < n; ++i){
            cans.emplace_back(i);
            if(run_diagnostic(cans) != last)res[i] = 1;
            cans.pop_back();
        }
        cans.clear();
        for(int i = ans + 2; i < n; ++i) cans.emplace_back(i);
        for(int i = ans; i >= 0; --i){
            cans.emplace_back(i);
            if(run_diagnostic(cans) != last)res[i] = 1;
            cans.pop_back();
        }
    }else{
        cans.clear();
        for(int i = 0; i <= ans; ++i)cans.emplace_back(i);
        for(int i = ans + 1; i < n; ++i){
            cans.emplace_back(i);
            if(run_diagnostic(cans) != last) res[i] = 1;
            cans.pop_back();
        }
        cans.clear();
        for(int i = ans + 1; i < n; ++i)cans.emplace_back(i);
        for(int i = ans; i >= 0; --i){
            cans.emplace_back(i);
            if(run_diagnostic(cans) != last)res[i] = 1;
            cans.pop_back();
        }
    }
    return res;
}
#ifndef ONLINE_JUDGE
void process(){
    int n; cin >> n;
    ans.assign(n, 0);
    for(int &u : ans)cin >> u;
    totCores = 0;
    for(int &u : ans) totCores += u;
    vector<int> res = malfunctioning_cores(n);
    assert(ans == res);
    for(int &u : ans)cout << u << ' ';cout << '\n';
    for(int &u : res)cout << u << ' ';cout << '\n';
    cout << cnt << '\n';
}
#define LOVE "coreputer"
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
#endif // ONLINE_JUDGE
