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
const int maxN = 2e5 + 5;
int n, a[maxN], q;
int lg[maxN], Gcd[18][maxN], b[maxN];

int getGcd(int l, int r){
    int k = lg[r - l + 1];
    return __gcd(Gcd[k][l], Gcd[k][r - (1 << k) + 1]);
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 2, n)lg[i] = lg[i >> 1] + 1;
    FOR(i, 1, n)Gcd[0][i] = a[i + 1] - a[i];
    FOR(j, 1, lg[n]){
        FOR(i, 1, n - (1 << j)){

            Gcd[j][i] = __gcd(Gcd[j - 1][i], Gcd[j - 1][i + (1 << (j - 1))]);
        }
    }

    while(q--){
        int l, r;
        cin >> l >> r;
        if(l == r)cout << 0 << ' ';
        else cout << abs(getGcd(l, r - 1)) << ' ';
    }
    cout << '\n';
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



