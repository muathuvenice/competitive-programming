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
const int maxN = 4e5 + 5;
string f[27], p;
int test, n;
int kmp[maxN];
char s[maxN], t[maxN];
int prefix[111], suffix[111];
long long appear[111];
int lenS;
long long match(const string &a){
    int lenT = 0;
    for(char c : a)t[++lenT] = c;
    int k = 0, answer = 0;
    FOR(i, 1, lenT){
        while(k > 0 && t[i] != s[k + 1]) k = kmp[k];
        int match = t[i] == s[k + 1] ? ++k : 0;
        if(match == lenS)++answer;
    }
    return answer;
}
long long query(const string &l, const string &r){
    int lenT = 0;
    for(char c : l)t[++lenT] = c;
    for(char c : r)t[++lenT] = c;
    int k = 0;
    int res = 0;
    FOR(i, 1, lenT){
        while(k > 0 && t[i] != s[k + 1])k = kmp[k];
        int match = t[i] == s[k + 1] ? ++k : 0;
        if(match == lenS && i > l.size() && i < l.size() + lenS)++res;
    }
    return res;
}
void process(){
    ++test;
    lenS = 0;
    for(char c : p)s[++lenS] = c;
    int k = 0;
    FOR(i, 2, lenS){
        while(k > 0 && s[i] != s[k + 1])k = kmp[k];
        kmp[i] = s[i] == s[k + 1] ? ++k : 0;
    }

    if(n <= 26){
        cout << "Case " << test << ":" << ' ' << match(f[n]) << "\n";
        return;
    }
//    cout << test << '\n';
    appear[25] = match(f[25]);
    appear[26] = match(f[26]);
    FOR(i, 27, n){
//        cout << i << '\n';
//        cout << i << ' ' << prefix[i - 1] << ' ' << suffix[i - 2] << '\n';
        appear[i] = appear[i - 1] + appear[i - 2] + query(f[suffix[i - 1]], f[prefix[i - 2]]);
    }
    cout << "Case " << test << ":" << ' ' << appear[n] << "\n";
}
#define NAME "Fibonacci Words"
int32_t main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
        freopen(NAME".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    f[0] = "0";
    f[1] = "1";
    FOR(i, 2, 26){
        f[i] = f[i - 1] + f[i - 2];
    }
    prefix[25] = suffix[25] = 25;
    suffix[26] = prefix[26] = 26;
    FOR(i, 27, 100){
        prefix[i] = prefix[i - 1];
        suffix[i] = suffix[i - 2];
//        cout << i << ' ' << prefix[i] << ' ' << suffix[i] << "\n";
    }
    while(cin >> n >> p)
        process();
    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}


