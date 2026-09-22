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
string notValid = "Impossible";
int q;
int type[maxN];
struct rec{
    int x1, y1, x2, y2;
    void read(){
        cin >> x1 >> y1 >> x2 >> y2;
    }
}c[maxN];
struct Point{
    int x, y;
    void read(){
        cin >> x >> y;
    }
}p[maxN];
 bool inside(const Point &a, const rec &b){
    return b.x1 <= a.x && a.x <= b.x2 && b.y1 <= a.y && a.y <= b.y2;
}
namespace subtask1{
    bool check(){
        return q <= 5000;
    }

    void solve(){
        long long answer = 0;

        FOR(i, 1, q){
            if(type[i] == 1){
                FOR(j, 1, i - 1)if(type[j] == 2)answer += inside(p[i], c[j]);
            }else{
                FOR(j, 1, i - 1)if(type[j] == 1)answer += inside(p[j], c[i]);
            }
            cout << answer << '\n';
        }

    }
}
struct Fenwick{
    int n;
    vector<int> fw;
    Fenwick(int _n = 0){
        n = _n;
        fw.assign(n + 1, 0);
    }
    void update(int x, int v){
        for(; x <= n; x += x & -x)fw[x] += v;
    }
    int get(int x){
        int res = 0;
        for(; x >= 1; x &= x - 1) res += fw[x];
        return res;
    }
    int get(int l, int r){
        if(l > r) return 0;
        return get(r) - get(l - 1);
    }
};
namespace subtask2{
    int curx = -inf;
    bool check(){

        FOR(i, 1, q){
            if(type[i] == 1){
                if(curx == -inf) curx = p[i].x;
                else if(p[i].x != curx) return false;
            }
        }
        return true;
    }
    long long answer = 0;
    vector<int> compress;

    void solve(){
        FOR(i, 1, q){
            if(type[i] == 1){
                compress.emplace_back(p[i].y);
            }else{
                compress.emplace_back(c[i].y1);
                compress.emplace_back(c[i].y2);
                compress.emplace_back(c[i].y2 + 1);
            }
        }
        compress.emplace_back(-inf);
        sort(all(compress));
        uni(compress);
        Fenwick point = Fenwick(compress.size() - 1);
        Fenwick rectangle = Fenwick(compress.size() - 1);
        FOR(i, 1, q){
            if(type[i] == 1){
                p[i].y = lower_bound(all(compress), p[i].y) - compress.begin();
                answer += rectangle.get(p[i].y);
                point.update(p[i].y, 1);
            }else{
                if(c[i].x1 <= curx && curx <= c[i].x2){
                    int ly = lower_bound(all(compress), c[i].y1) - compress.begin();
                    int ry = upper_bound(all(compress), c[i].y2) - compress.begin() - 1;
                    answer += point.get(ly, ry);
                    c[i].y1 = ly;
                    c[i].y2 = lower_bound(all(compress), c[i].y2) - compress.begin();
                    rectangle.update(c[i].y1, 1);
                    rectangle.update(c[i].y2 + 1, -1);
                }
            }
            cout << answer << '\n';
        }
    }
}
namespace subtask3{
    bool visited = false;
    bool check(){
        FOR(i, 1, q){
            if(type[i] == 1 && visited == true)return false;
            if(type[i] == 2) visited = true;
        }
        return true;
    }
    long long answer = 0;
    const int logN = __lg(maxN) + 2;
    struct Node{
        int lc, rc, sum;
        Node(){
            lc = rc = sum = 0;
        }
    }it[maxN * logN];
    vector<int> cx, cy;
    vector<int> query[maxN];
    int rootVersion[maxN];
    int numNode;
    void modify(int pre, int cur, int l, int r, int p){
//        assert(numNode < maxN * logN);
        if(l == r){
            it[cur].sum = it[pre].sum + 1;
            return;
        }
        int mid = l + r >> 1;
        if(p <= mid){
            it[cur].rc = it[pre].rc;
            it[cur].lc = ++numNode;
            modify(it[pre].lc, it[cur].lc, l, mid, p);
        }else{
            it[cur].rc = ++numNode;
            it[cur].lc = it[pre].lc;
            modify(it[pre].rc, it[cur].rc, mid + 1, r, p);
        }
        it[cur].sum = it[it[cur].lc].sum + it[it[cur].rc].sum;
    }
    long long get(int curl, int curr, int l, int r, int u, int v){
        if(l >= u && r <= v) return it[curr].sum - it[curl].sum;
        int mid = l + r >> 1;
        if(v <= mid) return get(it[curl].lc, it[curr].lc, l, mid, u, v);
        if(u > mid) return get(it[curl].rc, it[curr].rc, mid + 1, r, u, v);
        return get(it[curl].lc, it[curr].lc, l, mid, u, v) + get(it[curl].rc, it[curr].rc, mid + 1, r, u, v);
    }
    int sz;
    int get(int l, int r, int u, int v){
        if(l > r || u > v) return 0;
        return get(rootVersion[l - 1], rootVersion[r], 1, sz, u, v);
    }
    void solve(){
        FOR(i, 1, q){
            if(type[i] == 1){
                cx.emplace_back(p[i].x);
                cy.emplace_back(p[i].y);
            }else break;
        }
        cx.emplace_back(-inf);
        cy.emplace_back(-inf);
        sort(all(cx));
        sort(all(cy));
        uni(cx);
        uni(cy);
        FOR(i, 1, q){
            if(type[i] == 2) break;
            p[i].x = lower_bound(all(cx), p[i].x) - cx.begin();
            p[i].y = lower_bound(all(cy), p[i].y) - cy.begin();
            query[p[i].x].emplace_back(p[i].y);
        }
        sz = cy.size() - 1;
        int preVersion = 0;
        FOR(x, 1, cx.size() - 1){
            for(int y : query[x]){
                rootVersion[x] = ++numNode;
                modify(preVersion, rootVersion[x], 1, sz, y);
                preVersion = rootVersion[x];
            }
        }
//        cout << it[cx.size() - 1].sum << '\n';
        FOR(i, 1, q){
            if(type[i] == 1)cout << 0 << '\n';
            else{
                int lx = lower_bound(all(cx), c[i].x1) - cx.begin();
                int rx = upper_bound(all(cx), c[i].x2) - cx.begin() - 1;
                int ly = lower_bound(all(cy), c[i].y1) - cy.begin();
                int ry = upper_bound(all(cy), c[i].y2) - cy.begin() - 1;
                answer += get(lx, rx, ly, ry);
                cout << answer << '\n';
            }

        }
    }
}
namespace ac{
    const int inf = 2e9;
    long long ans[maxN];
    vector<int> cx, cy;
    struct Event1{
        int type, id, pos, delta;
        bool operator < (const Event1 & rhs) const{
            if(pos != rhs.pos) return pos < rhs.pos;
            return type < rhs.type;
        }
    };
    struct Event2{
        int type, id, pos, delta;
        bool operator < (const Event2 &rhs) const{
            if(pos != rhs.pos) return pos < rhs.pos;
            return type > rhs.type;
        }
    };
    Fenwick fw;
    void dnc(int l, int r){
        if(l > r || l == r) return ;
        int mid = l + r >> 1;
        vector<Event1> PointToRec;
        vector<Event2> RecToPoint;
        dnc(l, mid);
        dnc(mid + 1, r);
        FOR(i, l, mid){
            if(type[i] == 1)PointToRec.push_back({1, i, p[i].x, p[i].y});
            else{
                RecToPoint.push_back({2, i, c[i].x1, 1});
                RecToPoint.push_back({2, i, c[i].x2 + 1, -1});
            }
        }

        FOR(i, mid + 1, r){
            if(type[i] == 1)RecToPoint.push_back({1, i, p[i].x, p[i].y});
            else{
                PointToRec.push_back({2, i, c[i].x1 - 1, -1});
                PointToRec.push_back({2, i, c[i].x2, 1});
            }
        }
        sort(all(PointToRec));
        sort(all(RecToPoint));
        for(auto[type, id, pos, delta] : PointToRec){

            if(type == 1){
                fw.update(delta, 1);
            }else{
                int l = c[id].y1;
                int r = c[id].y2;
                ans[id] += delta * fw.get(l, r);
            }
        }
        for(auto[type, id, pos, delta] : PointToRec)if(type == 1) fw.update(delta, -1);
        for(auto[type, id, pos, delta] : RecToPoint){
            if(type == 2){
                int l = c[id].y1;
                int r = c[id].y2;
                fw.update(l, delta);
                fw.update(r + 1, - delta);
            }else{
                ans[id] += fw.get(delta);
            }
        }

    }
    void solve(){
        FOR(i, 1, q){
            if(type[i] == 1){
                cx.emplace_back(p[i].x);
                cy.emplace_back(p[i].y);
            }else{
                cx.emplace_back(c[i].x1);
                cx.emplace_back(c[i].x2);
                cy.emplace_back(c[i].y1);
                cy.emplace_back(c[i].y2);
            }
        }
        cx.emplace_back(-inf);
        cy.emplace_back(-inf);
        sort(all(cx));
        sort(all(cy));
        uni(cx);
        uni(cy);
        fw = Fenwick(cy.size() - 1);
        FOR(i, 1, q){
            if(type[i] == 1){
                p[i].x = lower_bound(all(cx), p[i].x) - cx.begin();
                p[i].y = lower_bound(all(cy), p[i].y) - cy.begin();
            }else{
                c[i].x1 = lower_bound(all(cx), c[i].x1) - cx.begin();
                c[i].x2 = lower_bound(all(cx), c[i].x2) - cx.begin();
                c[i].y1 = lower_bound(all(cy), c[i].y1) - cy.begin();
                c[i].y2 = lower_bound(all(cy), c[i].y2) - cy.begin();
            }
        }
        dnc(1, q);
        FOR(i, 1, q){
            ans[i] += ans[i - 1];
            cout << ans[i] << '\n';
        }
    }

}
void process(){
    cin >> q;
    FOR(i, 1, q){
        cin >> type[i];
        if(type[i] == 1){
            p[i].read();
        }else{
            c[i].read();
        }
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
//    if(subtask2 :: check()) return subtask2 :: solve();
//    if(subtask3 :: check()) return subtask3 :: solve();
    return ac :: solve();
}
#define LOVE "2dplane"
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





