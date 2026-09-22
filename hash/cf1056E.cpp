#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define First dsldsjofdsojisadjosdafiddd
#define Second dodfoidfjodsfodsodsfiosdf
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
const int maxN = 1e6 + 5;
const int inf = 1e9;
const long long infll = 1e18;
string a, b;
int cnt[2];
int Hash[maxN];
long long M = 1ll * mod * mod;
int power[maxN];
const int base = 256;
int getHash(int l, int r){
    return (Hash[r] - 1ll * Hash[l - 1] * power[r - l + 1] + M) % mod;
}
void process(){
    cin >> a >> b;
    if(a.size() > b.size()){
        cout << 0 << '\n';
        return;
    }
    memset(cnt, 0, sizeof cnt);
    for(char c : a)cnt[c - '0']++;
    b = ' ' + b;
    int m = b.size() - 1;
    power[0] = 1;
    FOR(i, 1, m){
        power[i] = 1ll * base * power[i - 1] % mod;
    }
    FOR(i, 1, m){
        Hash[i] = (1ll * Hash[i - 1] * base + b[i]) % mod;
    }
    int answer = 0;
    int c = a[0] - '0';
    FOR(i, 1, m){
        if(1ll * cnt[c] * i <= m){
            if((m - 1ll * cnt[c] * i) % cnt[c ^ 1] == 0){
                int j = (m - 1ll * cnt[c] * i) / cnt[c ^ 1];
                if(j == 0) continue;
                int First = mod, Second = mod;
                int lastCur = 0;
                bool ok = true;
                for(char x : a){
                    if(x == c + '0') lastCur += i;
                    else lastCur += j;
                    if(x == c + '0'){
                        if(First == mod) First = getHash(lastCur - i + 1, lastCur);
                        else if(getHash(lastCur - i + 1, lastCur) != First){
                            ok = false;
                            break;
                        }
                    }else{
                        if(Second == mod) Second = getHash(lastCur - j + 1, lastCur);
                        else if(getHash(lastCur - j + 1, lastCur) != Second){
                            ok = false;
                            break;
                        }
                    }
                }
                if(First == Second) ok = false;
//                cout << i << ' ' << j << ' ' << ok << '\n';
                answer += ok;
            }
        }
    }
    cout << answer << '\n';
}
#define LOVE "kytu"
int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
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





