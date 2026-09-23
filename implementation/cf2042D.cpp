#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
const int mod = 1e9 + 7;
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
int n;
int comp[maxN << 1];
const int inf = 1e9 + 2222;
struct MAX{
    int it[maxN << 3];
    void init(int id, int l, int r){
        if(l == r){
            it[id] = 0;
            return;
        }
        int mid = l + r >> 1;
        init(id << 1, l, mid);
        init(id << 1 | 1, mid + 1, r);
        it[id] = 0;
    }
    void modify(int id, int l, int r, int p){
        if(l == r){
            it[id] = p;
            return;
        }
        int mid = l + r >> 1;
        if(p <= mid)modify(id << 1, l, mid, p);
        else modify(id << 1 | 1, mid + 1, r, p);
        it[id] = max(it[id << 1], it[id << 1 | 1]);
    }
    int get(int id, int l, int r, int u, int v){
        if(l >= u && r <= v) return it[id];
        int mid = l + r >> 1;
        if(v <= mid)return get(id << 1, l, mid, u, v);
        if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
        return max(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
    }
}Max;
struct MIN{
    int it[maxN << 3];
    void init(int id, int l, int r){
        if(l == r){
            it[id] = inf;
            return;
        }
        int mid = l + r >> 1;
        init(id << 1, l, mid);
        init(id << 1 | 1, mid + 1, r);
        it[id] = inf;
    }
    void modify(int id, int l, int r, int p){
        if(l == r){
            it[id] = p;
            return;
        }
        int mid = l + r >> 1;
        if(p <= mid)modify(id << 1, l, mid, p);
        else modify(id << 1 | 1, mid + 1, r, p);
        it[id] = min(it[id << 1], it[id << 1 | 1]);
    }
    int get(int id, int l, int r, int u, int v){
        if(l >= u && r <= v) return it[id];
        int mid = l + r >> 1;
        if(v <= mid)return get(id << 1, l, mid, u, v);
        if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
        return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
    }
}Min;
struct segment{
    int l, r, id;
    bool operator < (const segment &rhs) const{
        return l != rhs.l ? l < rhs.l : r > rhs.r;
    }
    bool operator > (const segment &rhs) const {
        return r != rhs.r ? r > rhs.r : l < rhs.l;
    }
}s[maxN];
int MinR[maxN], MaxL[maxN];
int L[maxN], R[maxN];
map<pair<int, int>, int> cnt;
void process(){
    cin >> n;
    int m = n << 1;
    cnt.clear();
    FOR(i, 1, n){
        int l, r;
        cin >> l >> r;
        s[i] = {l, r, i};
        comp[i] = l;
        comp[i + n] = r;
    }
    sort(comp + 1, comp + 1 + m);
    FOR(i, 1, n){
        s[i].l = lower_bound(comp + 1, comp + 1 + m, s[i].l) - comp;
        s[i].r = lower_bound(comp + 1, comp + 1 + m, s[i].r) - comp;
        MinR[i] = s[i].r;
        MaxL[i] = s[i].l;
        L[i] = s[i].l;
        R[i] = s[i].r;
        cnt[mp(L[i], R[i])]++;
    }
    Min.init(1, 1, m);
    Max.init(1, 1, m);
    sort(s + 1, s + 1 + n);
    FOR(i, 1, n){
        auto[l, r, id] = s[i];
        int tmp = Min.get(1, 1, m, r, m);
        if(tmp != inf)MinR[id] = tmp;
        Min.modify(1, 1, m, r);
    }
    sort(s + 1, s + 1 + n, greater<segment>());
    FOR(i, 1, n){
        auto[l, r, id] = s[i];
        int tmp = Max.get(1, 1, m, 1, l);
        if(tmp)MaxL[id] = tmp;
        Max.modify(1, 1, m, l);
    }
    FOR(i, 1, n){
        if(cnt[mp(L[i], R[i])] > 1)cout << 0 << '\n';
        else cout << comp[L[i]] - comp[MaxL[i]] + comp[MinR[i]] - comp[R[i]] << "\n";
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
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}


