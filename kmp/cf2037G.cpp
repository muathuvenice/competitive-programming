#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define FOS(i, a, b) for(int i = a; i < b; ++i)
#define mp make_pair
const int mod = 998244353;
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
int n, a[maxN];
const int MAX = 1e6;
int MinPrime[MAX + 1];
int f[maxN], sum[MAX + 1];
void seive(){
    FOR(x, 2, MAX)MinPrime[x] = x;
    FOR(x, 2, MAX){
        if(MinPrime[x] == x){
            for(int y = 2; y * x <= MAX; ++y){
                minimize(MinPrime[y * x], x);
            }
        }
    }
}
void process(){
    seive();
    cin >> n;
    FOR(i, 1, n)cin >> a[i];
    vector<int> p;
    int cur = a[1];
    f[1] = 1;
    while(cur > 1){
        int v = MinPrime[cur];
        while(cur % v == 0)cur /= v;
        p.push_back(v);
    }
//    for(int v : p)cout << v << ' ';cout << '\n';
    FOS(mask, 1, 1 << p.size()){
        int val = 1;
        FOS(i, 0, p.size()){
            if((mask >> i) & 1)val *= p[i];
        }
        sum[val] = 1;
    }
    vector<int> divs;

    FOR(i, 2, n){
        p.clear();
        divs.clear();
        cur = a[i];
        while(cur > 1){
            int v = MinPrime[cur];
            while(cur % v == 0)cur /= v;
            p.push_back(v);
        }
//        int tmp = (int)p.size() & 1;
        FOS(mask, 1, 1 << p.size()){
            int cnt = 0, val = 1;
            FOS(i, 0, p.size()){
                if((mask >> (i)) & 1){
                    ++cnt;
                    val *= p[i];
                }
            }
            divs.push_back(val);
            if(cnt & 1)add(f[i], sum[val]);
            else sub(f[i], sum[val]);
        }
        for(int v: divs)add(sum[v], f[i]);
    }
//    FOR(i, 1, n)cout << f[i] << ' ';cout << '\n';
    cout << f[n];
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
//    cin >> t;
    while(t--)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}


