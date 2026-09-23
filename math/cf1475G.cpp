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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
inline void degbug(){

}
int n, a[maxN];
vector<int> divs[maxN];
int f[maxN];
int MAX = 2e5;
int cnt[maxN];
void process(){
    cin >> n;
    FOR(i, 1, MAX)f[i] = cnt[i] = 0;
    FOR(i, 1, n){
        int v;
        cin >> v;
        cnt[v]++;
    }

    FOR(i, 1, MAX)f[i] = 0;
    REP(i, MAX, 1){
        if(cnt[i]){
            f[i] = cnt[i];
            for(int j = 2 * i; j <= MAX; j += i){
                maximize(f[i], f[j] + cnt[i]);
            }
        }
    }
    cout << n - *max_element(f + 1, f + 1 + MAX) << "\n";
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




