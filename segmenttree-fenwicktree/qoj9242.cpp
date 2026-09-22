#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
#include <bits/stdc++.h>
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
#define left __left
#define down __down
#define right __right
#define up __up
inline bool maximize(int &u, int v){ return v > u ? u = v, true : false; }
inline bool minimize(int &u, int v){ return v < u ? u = v, true : false; }
inline bool maximizell(long long &u, long long v){ return v > u ? u = v, true : false; }
inline bool minimizell(long long &u, long long v){ return v < u ? u = v, true : false; }
const int mod = 1e9 + 7;
const long long M = 1ll * mod * mod;
inline int fastPow(int a, int n){
    if(n == 0) return 1;
    int t = fastPow(a, n >> 1);
    t = 1ll * t * t % mod;
    if(n & 1) t = 1ll * t * a % mod;
    return t;
}
inline void add(int &u, int v){ u += v; if(u >= mod) u -= mod; }
inline void sub(int &u, int v){ u -= v; if(u < 0) u += mod; }
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int power[maxN];
int n, k, b, a[maxN], q;
const int base = 13331;
struct Node{
    int lr, rl;
    int len;
    Node(){
        lr = rl = len = 0;
    }
    Node operator + (const Node &rhs) const{
        Node res;
        res.lr = (1ll * lr * power[rhs.len] + rhs.lr) % mod;
        res.rl = (1ll * rhs.rl * power[len] + rl) % mod;
        res.len = len + rhs.len;
        return res;
    }
}it[maxN << 2];
int lz[maxN << 2];
int pref[maxN];
void build(int id, int l, int r){
    if(l == r){
        it[id].lr = a[l];
        it[id].rl = (1ll * a[l] + 2 * b) %mod;
        it[id].len = 1;
        return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
void modify(Node &cur, int val){
    add(cur.lr, 1ll * val * pref[cur.len - 1] % mod);
    add(cur.rl, 1ll * val * pref[cur.len - 1] % mod);
}

void push(int id){
    if(lz[id] == 0) return;
    add(lz[id << 1], lz[id]);
    add(lz[id << 1 | 1], lz[id]);
    modify(it[id << 1], lz[id]);
    modify(it[id << 1 | 1], lz[id]);
    lz[id] = 0;
}
void modifyRange(int id, int l, int r, int u, int v, int w){
    if(l > v || r < u) return;
    if(l >= u && r <= v){
        modify(it[id], w);
        add(lz[id], w);
        return;
    }
    int mid = l + r >> 1;
    push(id);
    modifyRange(id << 1, l, mid, u, v, w);
    modifyRange(id << 1 | 1, mid + 1, r, u, v, w);
    it[id] = it[id << 1] + it[id << 1 | 1];
}
Node get(int id, int l, int r, int u, int v){
    if(l >= u && r <= v) return it[id];
    int mid = l + r >> 1;
    push(id);
    if(v <= mid) return get(id << 1, l, mid, u, v);
    if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
    Node L = get(id << 1, l, mid, u, v);
    Node R = get(id << 1 | 1, mid + 1, r, u, v);
    return L + R;
}
void process(){
    cin >> n >> q >> k >> b;
    b %= mod;
    add(b, mod);
    power[0] = 1;
    pref[0] = 1;
    FOR(i, 1, n){
        power[i] = 1ll * power[i - 1] * base % mod;
        pref[i] = pref[i - 1];
        add(pref[i], power[i]);
        cin >> a[i];
        a[i] = (2 * a[i] - 1LL * i * k) % mod;
        add(a[i], mod);
    }
    build(1, 1, n);
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l, r, w;
            cin >> l >> r >> w;
            w *= 2;
            w %= mod;
            add(w, mod);
            modifyRange(1, 1, n, l, r, w);
        }else{
            int p;
            cin >> p;
            int res = 0;
            int l = 1, r = min(p - 1, n - p);
            while(l <= r){
                int mid = l + r >> 1;
                Node Left = get(1, 1, n, p - mid, p - 1);
                Node Right = get(1, 1, n, p + 1, p + mid);
                if(Left.rl == Right.lr){
                    res = mid;
                    l = mid + 1;
                }else r = mid - 1;
            }
            cout << res << '\n';
        }
    }
}

#define LOVE "code"
signed main(){
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





