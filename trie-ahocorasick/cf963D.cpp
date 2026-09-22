#ifdef ONLINE_JUDGE
#endif // ONLINE_JUDGE
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
const int maxN = 1e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
#define next __next
int child[maxN][26], next[maxN][26], fail[maxN], numNode;
vector<int> found[maxN];
int n;
string t;
void addString(const string &s, int id){
    int u = 0;
    for(char x : s){
        int c = x - 'a';
        if(!child[u][c]) child[u][c] = ++numNode;
        u = child[u][c];
    }
    found[u].emplace_back(id);
}
void AC_BFS(){
    queue<int> q;
    FOR(i, 0, 25)next[0][i] = child[0][i] ? child[0][i] : 0;
    q.emplace(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        FOR(c, 0, 25){
            int v = child[u][c];
            if(v == 0) continue;
            fail[v] = u == 0 ? 0 : next[fail[u]][c];
            for(int id : found[fail[v]])found[v].emplace_back(id);
            FOR(c, 0, 25){
                next[v][c] = child[v][c] ? child[v][c] : next[fail[v]][c];
            }
            q.emplace(v);
        }

    }
}
int ans[maxN];
int k[maxN];
vector<int> pos[maxN];
string s[maxN];
void process(){
    cin >> t;
    cin >> n;
    FOR(i, 1, n){
        cin >> k[i];
        cin >> s[i];
        addString(s[i], i);
    }
    AC_BFS();
    int u = 0;
    FOR(i, 0, t.size() - 1){
        int c = t[i] - 'a';
        u = next[u][c];
        for(int id : found[u])pos[id].emplace_back(i);
    }
    FOR(i, 1, n){
        int x = s[i].size();
        if(pos[i].size() < k[i]){
            cout << -1 << '\n';
            continue;
        }
        int answer = inf;
        for(int j = 0; j + k[i] - 1 < pos[i].size(); ++j){
            minimize(answer, pos[i][j + k[i] - 1] - (pos[i][j] - x + 1) + 1);
        }
        cout << answer << '\n';
    }
}
#define LOVE "code"
int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
////        freopen(LOVE".out", "w", stdout);
//    }
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





