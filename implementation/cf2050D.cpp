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
string s;
int nxt[maxN], pre[maxN];
void process(){
    cin >> s;
    int n = s.size();
    s = ' ' + s;
    nxt[0] = 1;
    pre[1] = 0;
    FOR(i, 1, n)nxt[i] = i + 1, pre[i + 1] = i;
//    FOR(i, 1, n)cout << nxt[i] << ' ';cout << endl;
//    FOR(i, 1, n)cout << pre[i] << ' ';cout << endl;
    for(int i = 1; i <= n; i = nxt[i]){
//        cout << i << "\n";
        int tmp = s[i] - '0', pos = i;
        int t = 0;
        for(int j = nxt[i]; j <= n && t <= 8; j = nxt[j]){
            ++t;
            if(maximize(tmp, s[j] - '0' - t))pos = j;
        }
//        cout << i << ' ' << pos << ' ' << tmp << endl;
//        cout << s[i] << ' ' << s[pos] << endl;
        if(pos != i){
//            cout << s[i] << ' ' << s[pos] << endl;
            int prep = pre[pos], nxtp = nxt[pos];
            nxt[prep] = nxtp;
            pre[nxtp] = prep;
//            cout << i << ' ';
            cout << char(tmp + '0');
            i = pre[i];
            continue;
        }
//        cout << i << ' ';
        cout << s[i];
    }
    cout << '\n';
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



