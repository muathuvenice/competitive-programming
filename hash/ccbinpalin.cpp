#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
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
template<class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template<class X, class Y>
    bool maximize(X &x, Y y) {
        return x < y ? x = y, true : false;
    }
template <class T>
    void printVec(vector<T> &vec){
        for(T x : vec)cout << x << ' ';
        cout << '\n';
    }
const int mod = 1e9 + 7;
const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 1e6 + 5;

int n, type[maxN];
char c[maxN];
namespace subtask1{
    bool check(){
        return n <= 5000;
    }
    const int maxN = 5e3 + 5;
    int D_odd[maxN];
    int D_even[maxN];
    string S = " ";
    int N = 0;
    void Calc_D_odd() {
        int L = 1;
        int R = 0;
        for(int i = 1 ; i <= N ; i++) {
            if(i > R) D_odd[i] = 0;
            else D_odd[i] = min(R - i, D_odd[L + (R - i)]);
            while(i - D_odd[i] - 1 > 0 && i + D_odd[i] + 1 <= N && S[i - D_odd[i] - 1] == S[i + D_odd[i] + 1]) {
                D_odd[i]++;
            }

            if(i + D_odd[i] > R) {
                R = i + D_odd[i];
                L = i - D_odd[i];
            }
        }
    }

    void Calc_D_even() {
        int L = 1;
        int R = 0;
        for(int i = 1 ; i < N ; i++) {
            int j = i + 1;
            if(j > R) D_even[i] = 0;
            else D_even[i] = min(R - j + 1, D_even[L + (R - j)]);
            while(i - D_even[i] > 0 && j + D_even[i] <= N && S[i - D_even[i]] == S[j + D_even[i]]) {
                D_even[i]++;
            }
            if(i + D_even[i] > R) {
                R = i + D_even[i];
                L = j - D_even[i];
            }
        }
    }

    void solve(){
        FOR(i, 1, n){
            if(type[i] == 1){
                S += c[i];
                ++N;
            }else{
                S.pop_back();
                --N;
            }
            if(N == 0){
                cout << 0 << '\n';
                continue;
            }
            FOR(i, 1, N)D_odd[i] = D_even[i] = 0;
            Calc_D_odd();
            Calc_D_even();
            int answer = 0;
            for(int i = 1; i < N; ++i){
                maximize(answer, 2 * D_odd[i] + 1);
                maximize(answer, 2 * D_even[i]);
            }
            maximize(answer, 2 * D_odd[N] + 1);
            cout << answer << '\n';
        }
    }
}
namespace ac{
    int Hash[maxN];
    int power[maxN];
    int base = 50;
    int mod = 1e9 + 9;
    long long M = 1ll * mod * mod;
    int revHash[maxN];
    int invPower[maxN];
    int MAX = 1e6;
    int ans[maxN];
    int sz;
    inline int fastPow(int a, int n){
        if(n == 0) return 1;
        int t = fastPow(a, n >> 1);
        t = 1ll * t * t % mod;
        if(n & 1) t = 1ll * t * a % mod;
        return t;
    }
    int getHash(int l, int r){
        return 1ll * (Hash[r] - Hash[l - 1] + mod) * invPower[l] % mod;
    }
    int getRevHash(int l, int r){
        return 1ll * (revHash[r] - revHash[l - 1] + mod) * power[r] % mod;
    }
    bool isPalin(int l, int r){
        return getHash(l, r) == getRevHash(l, r);
    }
    void solve(){
        power[0] = 1;
        FOR(i, 1, MAX){
            power[i] = 1ll * power[i - 1] * base % mod;
        }
        invPower[MAX] = fastPow(power[MAX], mod - 2);
        FORD(i, MAX, 1){
            invPower[i - 1] = 1ll * invPower[i] * base % mod;
        }
        FOR(i, 1, n){
            if(type[i] == 1){
                int addC = c[i];
                sz++;
                Hash[sz] = (Hash[sz - 1] + 1ll * addC * power[sz]) % mod;
                revHash[sz] = (revHash[sz - 1] + 1ll * addC * invPower[sz]) % mod;
                int last = ans[sz - 1];
                // n - last + 1 -> n
                FOR(x, last + 1, last + 2){
                    if(x <= sz){
                        if(isPalin(sz - x + 1, sz)){
                            last = x;
                        }
                    }
                }
                ans[sz] = last;
            }else{
                revHash[sz] = 0;
                --sz;
            }
            cout << ans[sz] << '\n';
        }
    }
}
void fuck(){
    cin >> n;
    FOR(i, 1, n){
        cin >> type[i];
        if(type[i] == 1)cin >> c[i];
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
    return ac :: solve();
}
int main(){
    #define LOVE "bin"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



