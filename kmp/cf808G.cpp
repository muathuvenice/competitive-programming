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
const int maxN = 2e5 + 5;
const int N = 1e5;
char s[N + 7];
char t[N + 7];
int n, m;

int inf = 1e9;
int dp[N + 7][2];

int pp[N + 7];
bool over[N + 7];

void kmp() {
  int tt = 0;
  pp[1] = 0;
  for (int i = 2; i <= m; ++i) {
    while (tt > 0 && t[i] != t[tt + 1]) tt = pp[tt];
    if (t[i] == t[tt + 1]) tt++;
    pp[i] = tt;
  }

  while (tt > 0) {
    over[tt] = true;
    tt = pp[tt];
  }
}
void process(){
    cin >> (s + 1);
  cin >> (t + 1);
  n = strlen(s + 1);
  m = strlen(t + 1);

  kmp();

  dp[0][1] = -inf;

  for (int i = 1; i <= n; ++i) {
    dp[i][1] = -inf;
    for (int j = m; j > 0; --j) {
      if (s[i - m + j] != '?' && t[j] != s[i - m + j]) break;
      if (over[j - 1]) dp[i][1] = max(dp[i][1], 1 + dp[i - m + j - 1][1]);
      if (j == 1) dp[i][1] = max(dp[i][1], dp[i - m][0] + 1);
    }
    dp[i][0] = max(dp[i][1], dp[i - 1][0]);
  }

  cout << dp[n][0] ;
}
#define NAME "Anthem of Berland"
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


