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
//inline void add(int &u, int v){ u += v; if(u >= mod) u -= mod; }
//inline void sub(int &u, int v){ u -= v; if(u < 0) u += mod; }
const int maxN = 3e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int child[maxN * 20][2], Min[maxN * 20];
int numNode, n, a[maxN], q;
vector<int> query[maxN];
int l[maxN], r[maxN], x[maxN];
int res[maxN];
void add(int val, int pos){
    int u = 0;
    REP(i, 19, 0){
        int c = Bit(val, i);
        if(child[u][c] == 0) child[u][c] = ++numNode;
        u = child[u][c];
        if(Min[u] == 0 || Min[u] > pos) Min[u] = pos;
    }
}
int calc(int val, int pos){
    int answer = 0;
    int u = 0;
    REP(i, 19, 0){
        int c = Bit(val, i);
        if(child[u][c ^ 1] && Min[child[u][c ^ 1]] <= pos){
            u = child[u][c ^ 1];
            answer += Mask(i);
        }else{
            assert(child[u][c] > 0);
            u = child[u][c];
        }
    }
    return answer;
}
void process(){
    cin >> n;
    FOR(i, 1, n)cin >> a[i];
    cin >> q;
    FOR(i, 1, q){
        cin >> l[i] >> r[i] >> x[i];
        query[l[i]].emplace_back(i);
    }
    REP(i, n, 1){
        add(a[i], i);
        for(int id : query[i]){
            res[id] = calc(x[id], r[id]);
        }
    }
    FOR(i, 1, q){
        cout << res[i] << '\n';
    }
}
#define LOVE "mxq"
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




