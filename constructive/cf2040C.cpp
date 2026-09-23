#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
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
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
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
int n;
#define left lep
#define right rai
long long k;
void process(){
    cin >> n >> k;
    int cnt = n;
    vector<int> v;
    if(n <= 42 && (1ll << (n - 1)) < k){
        cout  << -1 << "\n";
        return;
    }
    int val = 1;
    while(n - val >= 42){
        cout << val++ << ' ';
    }
    vector<int> right;
    FOR(i, val, n - 1){
        if((1ll << (n - i - 1)) >= k){
            cout << i << ' ';
        }else{
            k -= (1ll << (n - i - 1));
            right.emplace_back(i);
        }
    }
    assert(k == 1);
    cout << n << ' ';
    reverse(all(right));
    for(int v : right)cout << v << ' ';
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
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
