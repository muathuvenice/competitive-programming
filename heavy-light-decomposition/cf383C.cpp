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
const int inf = 1e9;
const long long infll = 1e18;
int n, q, type[maxN], pos[maxN], val[maxN], a[maxN];
vector<int> adj[maxN];

inline void degbug(){

}
namespace subtask1{
    bool check(){
        return max(n, q) <= 1000;
    }
    const int maxN = 1e3 + 5;
    int id[maxN], in[maxN], out[maxN], d[maxN], timeDfs;
    inline void dfs(int u = 1, int p = 0){
        in[u] = ++timeDfs;
        id[timeDfs] = u;
        for(int v : adj[u]){
            if(v == p)continue;
            d[v] = d[u] + 1;
            dfs(v, u);
        }
        out[u] = timeDfs;
    }
    void query(int p, int val){
        FOR(i, in[p], out[p]){
            int v = id[i];
            a[v] += (((d[v] - d[p]) & 1) ? -1 : 1) * val;
        }
    }
    void solve(){
        dfs();
        FOR(i, 1, q){
            if(type[i] == 1)query(pos[i], val[i]);
            else cout << a[pos[i]] << "\n";
        }
    }
}
namespace subtask2{
    bool check(){
        bool two = false;
        FOR(i, 1, q)if(type[i] == 2)two = true;
        else if(two)return false;
        return true;
    }
    long long sum[maxN];
    inline void dfs(int u = 1, int p = 0){
        for(int v : adj[u]){
            if(v == p)continue;
            sum[v] += -sum[u];
            dfs(v, u);
        }
    }
    void solve(){
        bool first = false;
        FOR(i, 1, q){
            if(type[i] == 1){
                sum[pos[i]] += val[i];
            }else{
                if(first == false){
                    first = true;
                    dfs();
                    cout << a[pos[i]] + sum[pos[i]]<< "\n";
                }else cout << a[pos[i]] + sum[pos[i]] << "\n";
            }
        }
    }
}
namespace subtask3{
    int heavy[maxN], sz[maxN], par[maxN];
    inline void dfs(int u = 1){
        sz[u] = 1;
        for(int v : adj[u]){
            if(v == par[u])continue;
            par[v] = u;
            dfs(v);
            sz[u] += sz[v];
            if(sz[v] > sz[heavy[u]])heavy[u] = v;
        }
    }
    int chain[maxN], curChain = 1, curLab = 1, lab[maxN], top[maxN];
    inline void hld(int u = 1){
        if(top[curChain] == 0)top[curChain] = u;
        chain[u] = curChain;
        lab[u] = curLab;
        ++curLab;
        if(heavy[u])
        hld(heavy[u]);
        for(int v : adj[u]){
            if(v != par[u] && v != heavy[u]){
                ++curChain;
                hld(v);
            }
        }
    }
    struct Node{
        long long odd, even;
        int len;
        Node operator + (const Node &rhs) const {
            if(len == 0) return rhs;
            if(rhs.len == 0) return *this;
            Node res = *this;
            res.len += rhs.len;
            if(len & 1){
                res.odd += rhs.even;
                res.even += rhs.odd;
            }else{
                res.odd += rhs.odd;
                res.even += rhs.even;
            }
            return res;
        }
    }it[maxN << 2];
    inline void build(int id, int l, int r){
        if(l == r){
            it[id].odd = it[id].even = 0;
            it[id].len = 1;
            return;
        }
        int mid = l + r >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        it[id].odd = it[id].even = 0;
        it[id].len = it[id << 1].len + it[id << 1 | 1].len;
    }
    inline void update(int id, int l, int r, int p, int v){
        if(l == r){
            it[id].odd += v;
            return;
        }
        int mid = l + r >> 1;
        if(p <= mid)update(id << 1, l, mid, p, v);
        else update(id << 1 | 1, mid + 1, r, p, v);
        it[id] = it[id << 1] + it[id << 1 | 1];
    }
    inline Node get(int id, int l, int r, int u, int v){
        if(l >= u && r <= v) return it[id];
        int mid = l + r >> 1;
        if(v <= mid) return get(id << 1, l, mid, u, v);
        if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
        return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
    }
    long long query(int u){
        int v = u;
        Node answer;
        answer.odd = answer.even = 0;
        answer.len = 0;
        while(chain[u] != 1){
            answer = get(1, 1, n, lab[top[chain[u]]], lab[u]) + answer;
            u = par[top[chain[u]]];
        }
        answer = get(1, 1, n, lab[1], lab[u]) + answer;
        if(answer.len % 2 == 0){
            swap(answer.odd, answer.even);
        }
        return a[v] + answer.odd - answer.even;
    }
    void solve(){
        dfs();
        hld();
        build(1, 1, n);
        FOR(i, 1, q){
            if(type[i] == 1){
                update(1, 1, n, lab[pos[i]], val[i]);
            }else{
                cout << query(pos[i]) << "\n";
            }
        }
    }
}
void process(){
    cin >> n >> q;
    FOR(i, 1, n)cin >> a[i];
    FOR(i, 2, n){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    FOR(i, 1, q){
        cin  >> type[i];
        if(type[i] == 1){
            cin >> pos[i] >> val[i];
        }else cin >> pos[i];
    }

//    if(subtask1 :: check()) return subtask1 :: solve();
//    if(subtask2 :: check()) return subtask2 :: solve();
    return subtask3 :: solve();
}
#define LOVE ""
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




