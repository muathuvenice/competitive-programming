#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define mp make_pair
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
const int maxN = 5e4 + 5;
int a[maxN], b[maxN], n, k;
long long p, g;
double d[maxN];
pair<int, int> c[maxN];
double m;
bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    return a.first - a.second * m > b.first - b.second * m;
}
bool check(){
    long long P = 0, G = 0;
    sort(c + 1, c + 1 + n, cmp);
    double rem = 0;
    FOR(i, 1, k){
        rem += c[i].first - c[i].second * m;
        P += c[i].first;
        G += c[i].second;
    }
    if(rem >= 0){
//        p = P;
//        g = G;
        return true;
    }return false;
}
void process(){
    cin >> n >> k;
    FOR(i, 1, n)cin >> a[i] >> b[i];
    FOR(i, 1, n)c[i] = mp(a[i], b[i]);
    double l = 0, r = 5000000000;
    double res = l;
    FOR(test, 1, 100){
        m = (l + r) / 2;
//        cout << m << "\n";
        if(check()){
            l = m;
        }else r = m;
    }
    long long x = __gcd(p, g);
    cout << fixed << setprecision(15) << l;
}
#define NAME "diamond"
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}

/*
5 3
5 2
7 6
8 9
1 4
10 4

6 3
1 1
2 1
3 1
4 1
5 1
6 1
*/


