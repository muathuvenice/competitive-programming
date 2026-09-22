#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
inline bool maximize(int &u, int v){
    return v > u ? u = v, true : false;
}
inline bool minimize(int &u, int v){
    return v < u ? u = v, true : false;
}
inline bool maximizell(long long &u, long long v){
    return v > u ? u = v, true : false;
}
inline bool minimizell(long long &u, long long v){
    return v < u ? u = v, true : false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
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
const int inf = 2e9;
const long long infll = 1e18;
struct Node{
    int ans, subl, subr, addl, addr;
    Node operator + (const Node &rhs) const {
        Node res;
        res.ans = max(ans, rhs.ans);
        maximize(res.ans, addl + rhs.subr);
        maximize(res.ans, subl + rhs.addr);
        res.addl = max(addl, rhs.addl);
        res.addr = max(addr, rhs.addr);
        res.subl = max(subl, rhs.subl);
        res.subr = max(subr, rhs.subr);
        return res;
    }
}it[maxN << 2];
int n, q, a[maxN];
inline void init(int id, int l, int r){
    if(l == r){
        it[id] = {0, -a[l] + l, -a[r] - r, a[l] + l, a[r] - r};
        return;
    }
    int mid = l + r >> 1;
    init(id << 1, l, mid);
    init(id << 1 | 1, mid + 1, r);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
inline void modify(int id, int l, int r, int p, int v){
    if(l == r){
        it[id] = {0, -v + l, -v - r, v + l, v - r};
        return;
    }
    int mid = l + r >> 1;
    if(p <= mid)modify(id << 1, l, mid, p, v);
    else modify(id << 1 | 1, mid + 1, r, p, v);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n)cin >> a[i];
    init(1, 1, n);
    cout << it[1].ans << "\n";
    while(q--){
        int p, v;
        cin >> p >> v;
        modify(1, 1, n, p, v);
        cout << it[1].ans << "\n";
    }
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





