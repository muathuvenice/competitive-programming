
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
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
struct TestCase{
    int n;
    vector<int> c, s;
}a[maxN];
int t;
int n, c[maxN], s[maxN];
int Max, sum = 0;
namespace ac{
    pair<long long, int> f[maxN];
    pair<long long, int> Max[maxN];
    int sz[maxN], id[maxN];
    vector<int> candidates[maxN];
    long long pref[maxN];
    bool cmp(const int &a, const int &b){
        return s[a] > s[b];
    }
    bool cmp2(const int &a, const int &b){
        return sz[a] > sz[b];
    }
    void query(){
        vector<int> colours;
        FOR(i, 1, n)f[i] = mp(-infll, 0);
        FOR(i, 1, n)colours.emplace_back(c[i]);
        sort(all(colours));
        uni(colours);
        int maxColours = colours.size();
        FOR(i, 1, n){
            c[i] = lower_bound(all(colours), c[i]) - colours.begin() + 1;
            sz[c[i]]++;
            candidates[c[i]].emplace_back(i);
        }
        FOR(i, 1, maxColours){
            sort(all(candidates[i]), cmp);
        }
        FOR(i, 1, maxColours)id[i] = i;
        sort(id + 1, id + 1 + maxColours, cmp2);
        int col1 = -1, col2 = -1;
        long long answer = 0;
        FOR(i, 1, maxColours){
            int col = id[i];
            long long sum = 0;
            FOR(j, 0, sz[col] - 1){
                sum += s[candidates[col][j]];
            }
            pair<long long, int> tmp = f[sz[col] + 1];
            if(maximizell(answer, tmp.first + sum)){
                col1 = tmp.second;
                col2 = col;
            }
            tmp = f[sz[col]];
            if(maximizell(answer, tmp.first + sum)){
                col1 = tmp.second;
                col2 = col;
            }
            sum = 0;
            FOR(j, 0, sz[col] - 1){
                sum += s[candidates[col][j]];
                f[j + 1] = max(f[j + 1], mp(sum, col));
            }
        }
        vector<int> cans;
        int s1 = sz[col1], s2 = sz[col2];
        FOR(i, 0, min(s1, s2) - 1){
            cans.emplace_back(candidates[col1][i]);
            cans.emplace_back(candidates[col2][i]);
        }
        if(s1 > s2)cans.emplace_back(candidates[col1][s2]);
        else if(s1 < s2){
            reverse(all(cans));
            cans.emplace_back(candidates[col2][s1]);
        }
        // checker
//        assert(cans.size() <= n);
//        assert(cans.size() >= 2);
//        long long sum = 0;
//        for(int id : cans)sum += s[id];
//        assert(sum == answer);
//        assert(col1 != -1);
//        assert(col2 != -1);
//        assert(col1 != col2);
//        int cur = c[cans[0]];
//        for(int id : cans)assert(c[id] == col1 || c[id] == col2);
//        for(int i = 1; i < cans.size(); ++i){
//            assert(c[cans[i]] != c[cans[i - 1]]);
//        }
        cout << answer << '\n';
        cout << cans.size() << '\n';
        for(int id : cans)cout << id << ' ';cout << '\n';
//        cerr << answer << '\n';
//        cerr << cans.size() << '\n';
//        for(int id : cans)cerr << id << ' ';cerr << '\n';
        // reset
        FOR(i, 1, maxColours){
            candidates[i].clear();
            sz[i] = 0;
        }
    }
    void solve(){
        FOR(i, 1, t){
            n = a[i].n;
            FOR(j, 1, n)c[j] = a[i].c[j], s[j] = a[i].s[j];
            query();
        }
    }
}
void process(){
//    cin >> t;
    t = 1;
    FOR(i, 1, t){
//        string s;
//        cin >> s;
        cin >> a[i].n;
        a[i].c.resize(a[i].n + 1);
        a[i].s.resize(a[i].n + 1);
        FOR(j, 1, a[i].n)cin >> a[i].c[j] >> a[i].s[j];
    }
    FOR(i, 1, t)maximize(Max, a[i].n), sum += a[i].n;
//    if(subtask1 :: check()) return subtask1 :: solve();
    return ac :: solve();
}
#define LOVE "tower"
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




