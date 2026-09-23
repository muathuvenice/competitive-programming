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
const int maxN = 1e3 + 5;
char c[maxN][maxN];
int n, m;
bool cycle[maxN][maxN];
int state[maxN][maxN];
bool goOut(int u, int v){
    if(u == 1 && c[u][v] == 'U') return true;
    if(u == n && c[u][v] == 'D') return true;
    if(v == 1 && c[u][v] == 'L') return true;
    if(v == m && c[u][v] == 'R') return true;
    return false;
}
bool dfs(int u, int v){
    state[u][v] = 1;
    if(goOut(u, v)){
        state[u][v] = 2;
        return cycle[u][v] = false;
    }
    int x = u, y = v;
    if(c[u][v] == 'U')--x;
    else if(c[u][v] == 'D')++x;
    else if(c[u][v] == 'L')--y;
    else ++y;
    assert(c[x][y] != '?');
    if(state[x][y] == 1){
        state[u][v] = 2;
        return cycle[u][v] = true;
    }else if(state[x][y] == 0){
        cycle[u][v] |= dfs(x, y);
    }else cycle[u][v] |= cycle[x][y];
    state[u][v] = 2;
    return cycle[u][v];
}
void process(){
    cin >> n >> m;
    FOR(i, 1, n){
        FOR(j, 1, m){
            state[i][j] = 0;
            cycle[i][j] = false;
            cin >> c[i][j];
        }
    }

    FOR(i, 1, n){
        FOR(j, 1, m){
            if(c[i][j] == 'R'){
                if(j + 1 <= m && c[i][j + 1] == '?'){
                    c[i][j + 1] = 'L';
                }
            }else if(c[i][j] == 'L'){
                if(j >= 2 && c[i][j - 1] == '?'){
                    c[i][j - 1] = 'R';
                }
            }else if(c[i][j] == 'U'){
                if(i >= 2 && c[i - 1][j] == '?'){
                    c[i - 1][j] = 'D';
                }
            }else if(c[i][j] == 'D'){
                if(i + 1 <= n && c[i + 1][j] == '?'){
                    c[i + 1][j] = 'U';
                }
            }
        }
    }
    FOR(i, 1, n){
        FOR(j, 1, m){
            if(c[i][j] == '?'){
                if(i >= 2){
                    if(c[i - 1][j] == '?'){
                        c[i][j] = 'U';
                        c[i - 1][j] = 'D';
                        continue;
                    }
                    if(c[i - 1][j] == 'D'){
                        c[i][j] = 'U';
                        continue;
                    }
                }
                if(i + 1 <= n){
                    if(c[i + 1][j] == '?'){
                        c[i][j] = 'D';
                        c[i + 1][j] = 'U';
                        continue;
                    }
                    if(c[i + 1][j] == 'U'){
                        c[i][j] = 'D';
                        continue;
                    }
                }
                if(j >= 2){
                    if(c[i][j - 1] == '?'){
                        c[i][j] = 'L';
                        c[i][j - 1] = 'R';
                        continue;
                    }
                    if(c[i][j - 1] == 'R'){
                        c[i][j] = 'L';
                        continue;
                    }
                }
                if(j + 1 <= m){
                    if(c[i][j + 1] == '?'){
                        c[i][j] = 'R';
                        c[i][j + 1] = 'L';
                        continue;
                    }
                    if(c[i][j + 1] == 'L'){
                        c[i][j] = 'R';
                        continue;
                    }
                }
            }
        }
    }
    FOR(i, 1, n){
        FOR(j, 1, m){
            if(state[i][j] == 0 && c[i][j] != '?') cycle[i][j] = dfs(i, j);
        }
    }
    int answer = 0;
    FOR(i, 1, n){
        FOR(j, 1, m){
            if(c[i][j] == '?'){
                bool ok = false;
                if(i >= 2 && cycle[i - 1][j])ok = true;
                if(i + 1 <= n && cycle[i + 1][j])ok = true;
                if(j >= 2 && cycle[i][j - 1])ok = true;
                if(j + 1 <= m && cycle[i][j + 1])ok = true;
                answer += ok;
            }else answer += cycle[i][j];
        }
    }
    cout << answer << '\n';
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


