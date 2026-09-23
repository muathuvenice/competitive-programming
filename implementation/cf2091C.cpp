#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
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
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
    return res;
}
inline void add(int &u, int v){
    u += v;
    if(u >= mod) u -= mod;
}
inline void sub(int &u, int v){
    u -= v;
    if(u < 0) u += mod;
}
const int maxN = 2e5 + 5;
const int inf = 2e9;
const long long infll = 1e18;
int p[maxN], n;
int loc[maxN];
void process(){
    cin >> n;
    p[1] = 1;
    for(int i = 2; i <= (n >> 1) + (n & 1); ++i){
        p[i] = p[i - 1] + 2;
    }
    p[(n >> 1) + (n & 1) + 1] = 2;
    for(int i = (n >> 1) + (n & 1) + 2; i <= n; ++i){
        p[i] = p[i - 1] + 2;
    }
    FOR(i, 1, n)loc[p[i]] = i;
    int preDist = 0;
    FOR(i, 2, n){
        int dist = p[i] >= loc[p[i]] ? p[i] - loc[p[i]] : (n - loc[p[i]] + p[i]);
        if(dist != preDist + 1){
            cout << -1 << '\n';
            return;
        }
        preDist = dist;
    }
    FOR(i, 1, n)cout << p[i] << ' ';
    cout << "\n";
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



