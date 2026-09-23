#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for(int i = a; i <= b; ++i)
#define REP(i, a, b) for(int i = a; i >= b; --i)
#define mp make_pair
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
const int maxN = 1e6 + 5;
int n, kmp[maxN];
string s;
bool exist[maxN];
// k max thoa man khi ton tai j < i sao cho kmp[j] = k
void process(){
    cin >> s;
    n = s.size();
    s = ' ' + s;
    int k = 0;
    FOR(i, 2, n){
        while(k > 0 && s[i] != s[k + 1])k = kmp[k];
        kmp[i] = s[i] == s[k + 1] ? ++k : 0;
    }
    exist[0] = true;
    long long answer = 0;
    FOR(i, 1, n){
        int k = kmp[i];
        while(!exist[k]){
            k = kmp[k];
        }
        answer += k;
        exist[kmp[i]] = true;
    }
    cout << answer;
}
#define NAME "Repetitions"
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
//    cin >> t;
    while(t--)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}



