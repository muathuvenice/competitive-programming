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
int n;
long long s;
int x[maxN];
vector<int> adj[maxN];
struct Data{
    long long req, profit;
    bool operator < (const Data &rhs) const{
        return req != rhs.req ? req < rhs.req : profit < rhs.profit;
    }
};
priority_queue<Data> tree[maxN];
int root[maxN];
int find_root(int v){
    return root[v] = root[v] == v ? v : find_root(root[v]);
}
void Merge(int u, int v){
    u = find_root(u);
    v = find_root(v);
    if(tree[u].size() < tree[v].size()) swap(u, v);
    root[v] = u;
    while(!tree[v].empty()){
        auto val = tree[v].top();
        tree[v].pop();
        tree[u].push(val);
    }
//    priority_queue<Data> tmp = tree[u];
//    while(!tmp.empty()){
//        auto[req, profit] = tmp.top();
//        tmp.pop();
//        cout << req << ' ' << profit << '\n';
//
//    }
}
void link(priority_queue<Data> &x, Data prev){
//    cout << "prev " << prev.req << ' ' << prev.profit << '\n';
    while(!x.empty()){
        auto [req, profit] = x.top();
//        cout << req << ' ' << profit << '\n';
        if(prev.profit <= 0){
//            cout << "t1\n";
            minimizell(prev.req, req + prev.profit);
            prev.profit += profit;
            x.pop();
        }else{
            if(prev.req < req){
//                cout << "t2\n";
                prev.profit += profit;
                x.pop();
            }else{
//                cout << "t3\n";
                x.push(prev);
                break;
            }
        }
    }
//    cout << "end " << prev.req << ' ' << prev.profit << '\n';
    if(x.size() == 0) x.push(prev);
    if(x.size() == 1){
        if(x.top().profit <= 0) x.pop();
    }
}
void dfs(int u){
    for(int v : adj[u]){
        dfs(v);
        Merge(u, v);
    }
//    cout << u << '\n';
    link(tree[find_root(u)], {min(0, x[u]), x[u]});
}
void process(){
    cin >> n >> s;
    FOR(i, 0, n)root[i] = i;

    FOR(i, 1, n){
        int p;
        cin >> x[i] >> p;
        adj[p].emplace_back(i);
    }
    dfs(0);
    long long answer = 0;
    int u = find_root(0);
    while(!tree[u].empty()){
        auto[req, profit] = tree[u].top();
        tree[u].pop();
        if(s + answer + req >= 0){
            answer += profit;
        }
    }
    cout << answer;
}
#define LOVE "code"
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





