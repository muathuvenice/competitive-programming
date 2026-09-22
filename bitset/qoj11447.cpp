#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
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
const int maxN = 300 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, m, k, a[maxN], b[maxN];
string notValid = "Impossible";
namespace subtask1{
    bool check(){
        return m <= 15;
    }
    void solve(){
        int sumA = 0;
        FOR(i, 1, n)sumA += a[i];
        int answer = inf;
        FOR(mask, 1, Mask(m) - 1){
            if(Cnt(mask) < k) continue;
            int sum = 0;
            vector<int> available;
            FOR(i, 1, m){
                if(Bit(mask, i - 1)){
                    available.emplace_back(b[i]);
                    sum += b[i];
                }
            }
            sort(all(available), greater<int>());
            int rem = 0;
            FOR(i, 1, n){
                if(available.size() < k){
                    rem = inf;
                    break;
                }
                rem += a[i] - k;
                FOR(i, 0, k - 1)available[i]--;
                sort(all(available), greater<int> ());
                while(!available.empty() && available.back() == 0)available.pop_back();
            }
            if(rem + k * n <= sum)
            minimize(answer, sum);
        }
        if(answer == inf) cout << notValid;
        else cout << answer - sumA;
    }
}
namespace subtask3{
    bool check(){
        return k == 1;
    }
    bitset<90001> sum;
    void solve(){
        sum[0] = 1;
        FOR(i, 1, m){
            sum |= (sum << b[i]);
        }
        int sumA = 0;
        FOR(i, 1, n)sumA += a[i];
        FOR(i, sumA, 90000){
            if(sum[i]){
                cout << i - sumA;
                return;
            }
        }
        cout << notValid;
    }
}
/*
4 2 1
12 43 61 11
98 130

6 2 1
61 23 23 75 12 53
135 221
*/
namespace subtask4{
    bool check(){
        return max({n, m, k, *max_element(a + 1, a + 1 + n), *max_element(b + 1, b + 1 + m)}) <= 40;
    }
    const int maxN = 41;
    bitset<maxN * maxN> f[maxN * maxN];
    void solve(){
        int sumB = 0, sumA = 0;
        FOR(i, 1, n)sumA += a[i];
        FOR(i, 1, m)sumB += b[i];
        f[0][0] = 1;
        FOR(i, 1, m){
            REP(cover, i * n, min(b[i], n)){
                f[cover] |= f[cover - min(b[i], n)] << b[i];
            }

        }
        int answer = inf;
        FOR(cover, k * n, m * n){
            FOR(s, sumA, sumB){
                if(f[cover][s]){
                    minimize(answer, s);
                    break;
                }
            }
        }
        if(answer != inf)cout << answer - sumA;
        else cout << notValid;
    }
}
namespace ac{
    int f[maxN * maxN];
    void solve(){
        int sumA = 0, sumB = 0;
        FOR(i, 1, n)sumA += a[i];
        FOR(i, 1, m)sumB += b[i];
        FOR(i, 1, sumB)f[i] = -inf;
        FOR(i, 1, m){
            REP(sum, sumB, b[i]){
                maximize(f[sum], f[sum - b[i]] + min(b[i], n));
            }
        }
        FOR(s, sumA, sumB){
            if(f[s] >= n * k){
                cout << s - sumA;
                return;
            }
        }
        cout << notValid;
    }
}
void process(){
    cin >> n >> m >> k;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 1, m)cin >> b[i];
    if(m < k || *min_element(a + 1, a + 1 + n) < k){
        cout << notValid;
        return;
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
//    if(subtask3 :: check()) return subtask3 :: solve();
//    if(subtask4 :: check()) return subtask4 :: solve();
    return ac :: solve();
}
#define LOVE "code"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
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




