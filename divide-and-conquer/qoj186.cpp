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
const int maxN = 3e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
char s[maxN];
int type[maxN];
int n, q, pos[maxN], a[maxN], b[maxN];
bool state[maxN];
struct event{
    int type, pos, posAsk, val;
    bool operator < (const event &rhs) const{
        return pos != rhs.pos ? pos < rhs.pos : type < rhs.type;
    }
};
vector<event> query[maxN];
int fw[maxN];
void update(int x, int v){
    for(; x <= n; x += x & -x)fw[x] += v;
}
int get(int x){
    int res = 0;
    for(; x >= 1; x &= x - 1) res += fw[x];
    return res;
}
int ans[maxN];
void dnc(int l, int r){
    if(l == r) return;
    if(l > r) return;
    int mid = l + r >> 1;
//    cerr << l << ' ' << mid << ' ' << mid + 1 << ' ' << r << '\n';
    dnc(l, mid);
    dnc(mid + 1, r);
    vector<event> Merge;
    FOR(i, l, mid){
        if(type[i] == 1){
            Merge.insert(Merge.end(), all(query[i]));
        }
    }
    FOR(i, mid + 1, r){
        if(type[i] == 2){
            Merge.insert(Merge.end(), all(query[i]));
        }
    }
    sort(all(Merge));
    for(auto[type, pos, posAsk, val] : Merge){
//        cerr << type << ' ' << pos << ' ' << posAsk << ' ' << val << '\n';
        if(type == 1){
            update(posAsk, val);
        }else{
            assert(val > 0);
            assert(val <= q);
            ans[val] += get(posAsk);
        }
    }

}
void process(){
    cin >> n >> q;
    set<int> zero;
    zero.insert(0);
    FOR(i, 1, n){
        cin >> s[i];
        if(s[i] == '0')zero.insert(i);
    }
    zero.insert(n + 1);
    FOR(i, 1, q){
        string t;
        cin >> t;
        if(t[0] == 't'){
            type[i] = 1;
            cin >> pos[i];
            if(s[pos[i]] == '0'){
                s[pos[i]] = '1';
                zero.erase(pos[i]);
                auto it = zero.upper_bound(pos[i]);
                int zr = *it - 1;
                int zl = *prev(it) + 1;
                // [zl, pos[i]] x [pos[i], zr]
                query[i].push_back({1, zl, pos[i], -i});
                query[i].push_back({1, zl, zr + 1, i});
                query[i].push_back({1, pos[i] + 1, pos[i], i});
                query[i].push_back({1, pos[i] + 1, zr + 1, -i});
            }else{
                auto it = zero.upper_bound(pos[i]);
                int zr = *it - 1;
                int zl = *prev(it) + 1;
                s[pos[i]] = '0';
                zero.insert(pos[i]);
                query[i].push_back({1, zl, pos[i], i});
                query[i].push_back({1, zl, zr + 1, -i});
                query[i].push_back({1, pos[i] + 1, pos[i], -i});
                query[i].push_back({1, pos[i] + 1, zr + 1, i});
            }
        }else{
            type[i] = 2;
            cin >> a[i] >> b[i];
            --b[i];
            auto it = zero.lower_bound(a[i]);
            if(*it > b[i]) state[i] = true;
            query[i].push_back({2, a[i], b[i], i});
        }
    }
    dnc(1, q);
    FOR(i, 1, q){
        if(type[i] == 2){
            cout << ans[i] + state[i] * i << '\n';
        }
    }
}
#define LOVE "streetlamps"
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
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




