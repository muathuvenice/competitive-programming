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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, m;
pair<int, int> edge[maxN << 2];
vector<int> adj[maxN];
namespace subtask1{
    bool check(){
        return n <= 2000;
    }
    bool visited[maxN];
    vector<int> e;
    void make_graph(){
        FOR(i, 1, n)visited[i] = false;
        visited[1] = true;
        priority_queue<int, vector<int>, greater<int>> q;
        for(int id : adj[1])q.emplace(id);
        int sz = 1;
        int h = 0;
        while(sz < n){
            int id = q.top();
            q.pop();
            auto[u, v] = edge[id];
            if(visited[u] && visited[v]) continue;
            e.emplace_back(id);
            h = (10ll * h + id) % mod;
            ++sz;
            if(visited[u]) swap(u, v);
            assert(visited[u] == false);
            visited[u] = true;
            for(int id : adj[u]){
                int x = edge[id].first ^ edge[id].second ^ u;
                if(!visited[x])q.emplace(id);
            }
        }
        cout << h << '\n';
    }
    void query(int u){
        FOR(i, 1, n)visited[i] = false;
        visited[u] = true;
        priority_queue<int, vector<int>, greater<int>> q;
        for(int id : adj[u])q.emplace(id);
        int sz = 1;
        int h = 0;
        while(sz < n){
            int id = q.top();
            q.pop();
            auto[u, v] = edge[id];
            if(visited[u] && visited[v]) continue;
            h = (10ll * h + id) % mod;
            ++sz;
            if(visited[u]) swap(u, v);
            assert(visited[u] == false);
            visited[u] = true;
            for(int id : adj[u]){
                int x = edge[id].first ^ edge[id].second ^ u;
                if(!visited[x])q.emplace(id);
            }
        }
        cout << h << '\n';
    }
    void solve(){
        make_graph();
        FOR(i, 1, n)adj[i].clear();
        for(int id : e){
            auto[u, v] = edge[id];
            adj[u].emplace_back(id);
            adj[v].emplace_back(id);
        }
        FOR(u, 2, n)query(u);
    }
}
namespace ac{
    bool check(){
        FOR(i, 1, m){
            auto[u, v] = edge[i];
            if(u + 1 != v) return false;
        }
        return true;
    }
    int root[maxN];
    vector<int> node[maxN];
    int find_root(int v){ return root[v] = root[v] == v ? v : find_root(root[v]);}
    bool union_set(int u, int v){
        u = find_root(u);
        v = find_root(v);
        if(u == v) return false;
        if(node[u].size() < node[v].size()) swap(u, v);
        root[v] = u;
        for(int x : node[v]) node[u].emplace_back(x);
        return true;
    }
    int pos[maxN], power[maxN];
    int L[maxN], R[maxN], sz[maxN];
    bool match(int u, int v) { return find_root(u) == find_root(v);}
    struct Node{
        int a, b;
        Node(int _a = 0, int _b = 0){
            a = _a;
            b = _b;
        }

        Node operator + (const Node &y) const {
            return Node(a + y.a, (1ll * power[y.a] * b + y.b) % mod);
        }
    }it[maxN << 2];
    void out(Node x){
        cout << x.a << ' ' << x.b << '\n';
    }
    void push(int id){
        if(it[id].a == 0) return;
        it[id << 1] = it[id << 1] + it[id];
        it[id << 1 | 1] = it[id << 1 | 1] + it[id];
        it[id] = Node();
    }
    void modify(int id, int l, int r, int u, int v, Node w){
        if(l > v || r < u) return;
        if(l >= u && r <= v){
            it[id] = it[id] + w;
            return;
        }
        int mid = l + r >> 1;
        push(id);
        modify(id << 1, l, mid, u, v, w);
        modify(id << 1 | 1, mid + 1, r, u, v, w);
    }
    Node get(int id, int l, int r, int p){
        if(l == r) return it[id];
        int mid = l + r >> 1;
        push(id);
        if(p <= mid) return get(id << 1, l, mid, p);
        else return get(id << 1 | 1, mid + 1, r, p);
    }
    void solve(){
        FOR(i, 1, n)root[i] = i, node[i].emplace_back(i);
        FOR(i, 1, m){
            auto[u, v] = edge[i];
            union_set(u, v);
        }
        int x = find_root(1);
        for(int i = 0; i < node[x].size(); ++i){
            pos[node[x][i]] = i + 1;
//            cout << node[x][i] << ' ';
        }
//        cout << '\n';
        power[0] = 1;
        FOR(i, 1, n)power[i] = 10ll * power[i - 1] % mod;
        FOR(i, 1, n){
            root[i] = i;
            sz[i] = 1;
            L[i] = R[i] = pos[i];
        }
        FOR(x, 1, m){
            auto[u, v] = edge[x];
            if(match(u, v)) continue;
            if(pos[u] > pos[v]) swap(u, v);

            Node Left = Node(1, x) + get(1, 1, n, pos[u]);
            Node Right = Node(1, x) + get(1, 1, n, pos[v]);
            u = find_root(u);
            v = find_root(v);
            modify(1, 1, n, L[u], R[u], Right);
            modify(1, 1, n, L[v], R[v], Left);
            if(sz[u] < sz[v]) swap(u, v);
            root[v] = u;
            minimize(L[u], L[v]);
            maximize(R[u], R[v]);
            sz[u] += sz[v];

        }
        FOR(i, 1, n){
            Node ans = get(1, 1, n, pos[i]);
            cout << ans.b << '\n';
        }

    }
}
void process(){
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; ++i){
        cin >> u >> v;
        adj[u].emplace_back(i);
        adj[v].emplace_back(i);
        edge[i] = mp(u, v);
    }
//    if(subtask1 :: check()) return subtask1 :: solve();
    return ac :: solve();
}
#define LOVE "graph"
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





