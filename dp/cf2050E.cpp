#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
const int mod = 1e9 + 7;
inline bool maximize(int &u, int v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimize(int &u, int v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
inline bool maximizell(long long &u, long long v){
    if(v > u){
        u = v;
        return true;
    }
    return false;
}
inline bool minimizell(long long &u, long long v){
    if(v < u){
        u = v;
        return true;
    }
    return false;
}
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
string a, b, c;
int f[1001][1001];
void process(){
    cin >> a >> b >> c;
    int n = a.size(), m = b.size(), z = c.size();
    a = ' ' + a;
    b = ' ' + b;
    c = ' ' + c;
    FOR(i, 0, n){
        FOR(j, 0, m){
            if(i == 0 && j == 0)continue;
            f[i][j] = 0;
            if(i)maximize(f[i][j], f[i - 1][j] + (a[i] == c[i + j]));
            if(j)maximize(f[i][j], f[i][j - 1] + (b[j] == c[i + j]));
        }
    }
//    FOR(i, 0, n){
//        FOR(j, 0, m){
//            cout << i << ' ' << j << ' ' << f[i][j] << '\n';
//        }
//    }
    cout << z - f[n][m] << '\n';
}
#define NAME ""
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while(t--)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



