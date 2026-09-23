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
int n, q;
string s[maxN];
vector<int> pos[6];
int type[maxN];
bool fast(string &s, string &t){
    for(char c : s)for(char a : t)if(c == a) return true;
    return false;
}
int query(int u, int v){
    int answer = (int)1e9;
    FOR(i, 0, 5){
        if(i == type[u])continue;
        if(i == type[v])continue;
        int p = lower_bound(all(pos[i]), u) - pos[i].begin();
        if(p < pos[i].size()) minimize(answer, pos[i][p] - u + abs(pos[i][p] - v));
        if(p > 0) minimize(answer, u - pos[i][p - 1] + abs(pos[i][p - 1] - v));
        p = lower_bound(all(pos[i]), v) - pos[i].begin();
        if(p < pos[i].size()) minimize(answer, abs(pos[i][p] - u) + pos[i][p] - v);
        if(p > 0) minimize(answer, v - pos[i][p - 1] + abs(pos[i][p - 1] - u));
    }
    return (answer > 2 * n ? - 1 : answer) ;
}
void process(){
    cin >> n >> q;
    FOR(i, 0, 5)pos[i].clear();
    FOR(i, 1, n)cin >> s[i];
    FOR(i, 1, n){
        if(s[i] == "BG")type[i] = 0;
        else if(s[i] == "BR")type[i] = 1;
        else if(s[i] == "BY")type[i] = 2;
        else if(s[i] == "GR")type[i] = 3;
        else if(s[i] == "GY")type[i] = 4;
        else type[i] = 5;
        pos[type[i]].emplace_back(i);
    }
    while(q--){
        int u, v;
        cin >> u >> v;
        if(fast(s[u], s[v])){
            cout << abs(u - v) << '\n';
            continue;
        }
        cout << query(u, v) << "\n";

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



