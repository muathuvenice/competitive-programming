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
const int mod = (int)1e9 + 7;
inline int fastPow(int a, int n, int mod){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a % mod;
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
const int inf = (int)2e9;
const long long infll = 1e18;
int m, p[maxN];
long long n;
namespace subtask1{
    bool check(){
        return n <= 200000;
    }
    void solve(){
        int answer = 1;
        FOR(x, 1, n){
            if(n % x == 0)answer = 1ll * x * answer % mod;
        }
        cout << answer << "\n";
    }
}
namespace subtask2{
    int power[maxN];
    pair<int, int> prime[maxN];
    int cnt[maxN];
    int c, answer = 1;
    int prefMul[maxN], suffMul[maxN];
    void solve(){
        power[0] = 1;
        FOR(i, 1, m)power[i] = 2ll * power[i - 1] % mod;
        FOR(i, 1, m)cnt[p[i]]++;
        for(int i = 2; i <= 200000; ++i)if(cnt[i])prime[++c] = mp(i, cnt[i]);
        prefMul[0] = 1;
        FOR(i, 1, c)prefMul[i] = 1ll * prefMul[i - 1] * (prime[i].second + 1) % (mod - 1);
        suffMul[c + 1] = 1;
        REP(i, c, 1)suffMul[i] = 1ll * suffMul[i + 1] * (prime[i].second + 1) % (mod - 1);
        FOR(i, 1, c){
            int k = prime[i].second;
            answer = 1ll * answer * fastPow(fastPow(prime[i].first, 1ll * k * (k + 1) / 2 % (mod - 1), mod), 1ll * prefMul[i - 1] * suffMul[i + 1] % (mod - 1), mod) % mod;

        }
        cout << answer;
    }
}
void process(){
    n = 1;
    cin >> m;
    FOR(i, 1, m){
        cin >> p[i];
        n = n * p[i];
        minimizell(n, mod);
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
    return subtask2 :: solve();
}
#define NAME "password"
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
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}

