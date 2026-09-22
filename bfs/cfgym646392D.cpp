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
const int maxN = 1e3 + 1;
const int inf = 1e9;
const long long infll = 1e18;
string notValid = "Impossible";
int n, m, k, a[maxN][maxN], q;
int dist[41][maxN][maxN];
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
vector<pair<int, int>> List[41];
bool visited[41];
void bfs(int col){
    queue<pair<int, int>> q;
    FOR(i, 1, n){
        FOR(j, 1, m){
            if(a[i][j] == col){
                dist[col][i][j] = 0;
                q.emplace(i, j);
                continue;
            }
            dist[col][i][j] = inf;
        }
    }
    memset(visited, 0, sizeof visited);
    visited[col] = true;
    while(!q.empty()){
        auto[u, v] = q.front();
        q.pop();
        if(!visited[a[u][v]]){
            visited[a[u][v]] = true;
            for(auto[x, y] : List[a[u][v]]){
                if(minimize(dist[col][x][y], dist[col][u][v] + 1)){
                    q.emplace(x, y);
                }
            }
        }
        REP(k, 4){
            int x = u + dx[k];
            int y = v + dy[k];
            if(x >= 1 && x <= n && y >= 1 && y <= m){
                if(minimize(dist[col][x][y], dist[col][u][v] + 1)){
                    q.emplace(x, y);
                }
            }
        }
    }
}
void process(){
    cin >> n >> m >> k;
    FOR(i, 1, n){
        FOR(j, 1, m){
            cin >> a[i][j];
            List[a[i][j]].emplace_back(i, j);
        }
    }
    FOR(i, 1, k)bfs(i);
    cin >> q;
    while(q--){
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        if(u == x && v == y){
            cout << 0 << '\n';
            continue;
        }
        if(a[u][v] == a[x][y]){
            cout << 1 << '\n';
            continue;
        }
        int answer = abs(u - x) + abs(v - y);
        FOR(col, 1, k){
            minimize(answer, dist[col][u][v] + dist[col][x][y] + 1);
        }
        cout << answer << '\n';
    }
}
#define LOVE "code"
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





