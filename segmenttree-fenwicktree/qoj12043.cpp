#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops")
//#pragma GCC target("popcnt")
using namespace std;
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
#define assert(x) if(!(x)) cout << "error", exit(0)
template <class X, class Y>
    bool minimize(X &x, Y y) {
        return x > y ? x = y, true : false;
    }
template <class X, class Y>
    bool maximize(X &x, Y y) {
        return x < y ? x = y, true : false;
    }
template <class T>
    void printVec(vector<T> &vec){
        for(T x : vec)cout << x << ' ';
        cout << '\n';
    }
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
const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 5e5 + 5;

int n, q;
int a[maxN];
struct Node{
    long long sum;
    int cnt;
    Node(long long _sum = 0, int _cnt = 0){
        sum = _sum;
        cnt = _cnt;
    }
    Node operator + (const Node &rhs) const{
        return Node(sum + rhs.sum, cnt + rhs.cnt);
    }
}it[maxN << 2];
void modify(int id, int l, int r, int p, int v){
    if(l == r){
        it[id].sum += v;
        it[id].cnt++;
        return;
    }
    int mid = l + r >> 1;
    if(p <= mid) modify(id << 1, l, mid, p, v);
    else modify(id << 1 | 1, mid + 1, r, p, v);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
long long walk(int id, int l, int r, int k){
    if(l == r){
        return it[id].sum / it[id].cnt * k;
    }
    int mid = l + r >> 1;
    if(it[id << 1].cnt >= k) return walk(id << 1, l, mid, k);
    return it[id << 1].sum + walk(id << 1 | 1, mid + 1, r, k - it[id << 1].cnt);
}
vector<tuple<int, int, int>> query[maxN];
struct compress{
    vector<int> c;
    compress(){
        c.clear();
    }
    void insert(int v){
        c.emplace_back(v);
    }
    int getVal(int v){
        return lower_bound(all(c), v) - c.begin() + 1;
    }
    int maxVal(){
        return c.size();
    }
    void build(){
        sort(all(c));
        uni(c);
    }

};
long long answer[maxN];
int type[maxN];
void fuck(){
    cin >> n;
    compress c;
    FOR(i, 1, n) cin >> a[i], c.insert(a[i]);
    c.build();
    int mx = c.maxVal();
    int cnt = 0;
    cin >> q;
    FOR(i, 1, q){
        cin >> type[i];
        if(type[i] == 1){
            ++cnt;
            continue;
        }
        int l, r;
        cin >> l >> r;
        if(l - 1 > 0){
            query[min(l - 1 + cnt, n)].emplace_back(i, l - 1, -1);
        }
        query[min(r + cnt, n)].emplace_back(i, r, 1);
    }

    FOR(i, 1, n){
        modify(1, 1, mx, c.getVal(a[i]), a[i]);
        for(auto [id, p, delta] : query[i]) {
            answer[id] += delta * walk(1, 1, mx, p);
        }
    }
    FOR(i, 1, q) if(type[i] == 2) cout << answer[i] << '\n';
}
int main(){
    #define LOVE "code"

    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
    }

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        fuck();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



