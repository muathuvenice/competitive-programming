#include <bits/stdc++.h>
using namespace std;
const string LOVE = "Phuong";
#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define REP(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define mp make_pair
#define all(v) v.begin(), v.end()
#define uni(v) v.erase(unique(all(v)), v.end())
inline bool maximize(int &u, int v){
    return v > u ? u = v, true : false;
}
inline bool minimize(int &u, int v){
    return v < u ? u = v, true : false;
}
inline bool maximizell(long long &u, long long v){
    return v > u ? u = v, true : false;
}
inline bool minimizell(long long &u, long long v){
    return v < u ? u = v, true : false;
}
const int mod = 1e9 + 7;
inline int fastPow(int a, int n){
    int res = 1;
    while(n){
        if(n & 1)res = 1ll * res * a * mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
    return res;
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
const int inf = 2e9;
const long long infll = 1e18;
int n;
string s;
int m;
bool same[maxN];
int pref[26][maxN];
bool palinFromMid[maxN];
bool check(int k){
    FOR(i, 1, n - k + 1){
        int l = i, r = i + k - 1;
        if(r < m){
            if(palinFromMid[r + 1] && same[l - 1]){
                bool ok = true;
                FOR(z, 0, 25)if(pref[z][r] - pref[z][l - 1] != pref[z][n - l + 1] - pref[z][n - r]){
                    ok = false;
                    break;
                }
                if(ok) return true;
            }else continue;
        }else if(r == m){
            if(!same[l - 1])continue;
            bool ok = true;
            FOR(z, 0, 25)if(pref[z][r] - pref[z][l - 1] != pref[z][n - l + 1] - pref[z][n - r]){
                ok = false;
                break;
            }
            if(ok) return true;
        }else{
            if(l > m + 1){
                if(palinFromMid[l - 1] && same[r + 1]){
                    bool ok = true;
                    FOR(z, 0, 25)if(pref[z][r] - pref[z][l - 1] != pref[z][n - l + 1] - pref[z][n - r]){
                        ok = false;
                        break;
                    }
                    if(ok) return true;
                }else continue;
            }else if(l == m + 1){
                if(!same[r + 1])continue;
                bool ok = true;
                FOR(z, 0, 25)if(pref[z][r] - pref[z][l - 1] != pref[z][n - l + 1] - pref[z][n - r]){
                    ok = false;
                    break;
                }
                if(ok) return true;
            }else{
                int L = min(l, n - r + 1);
                int R = n - L + 1;
                if(!same[L - 1])continue;
                if(!same[R + 1])continue;

                if(L == l && R == r){
                    bool ok = true;
                    FOR(z, 0, 25)if((pref[z][R] - pref[z][L - 1] % 2) == 1){
                        ok = false;
                        break;
                    }
                    if(ok) return true;
                    continue;
                }
                if(L == l){
                    assert(R > r);
                    bool ok = true;
                    FOR(z, 0, 25){
                        int cur = pref[z][r] - pref[z][l - 1];
                        cur -= pref[z][R] - pref[z][r];
                        if(cur < 0 || (cur & 1)){
                            ok = false;
                            break;
                        }
                    }
                    if(ok) return true;
                    continue;
                }
                assert(R == r && L < l);
                bool ok = true;
                FOR(z, 0, 25){
                    int cur = pref[z][r] - pref[z][l - 1];
                    cur -= pref[z][l - 1] - pref[z][L - 1];
                    if(cur < 0 || (cur & 1)){
                        ok = false;
                        break;
                    }
                }
                if(ok)return true;
            }
        }
    }
    return false;
}
void process(){
    cin >> s;
    n = s.size();
    s = ' ' + s;
    FOR(i, 1, n){
        FOR(j, 0, 25)pref[j][i] = pref[j][i - 1];
        pref[s[i] - 'a'][i]++;
    }
    m = n >> 1;
    same[0] = same[n + 1] = true;
    FOR(i, 1, m){
        same[i] = same[n - i + 1] = same[i - 1] & (s[i] == s[n - i + 1]);
    }
    palinFromMid[m] = palinFromMid[m + 1] = (s[m] == s[m + 1]);
    REP(i, m - 1, 1){
        palinFromMid[i] = palinFromMid[n - i + 1] = palinFromMid[i + 1] & (s[i] == s[n - i + 1]);
    }
    int answer = n;
    int l = 0, r = n;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)){
            answer = mid;
            r = mid - 1;
        }else l = mid + 1;
    }
    cout << answer << '\n';
}
#define LOVE ""
int main(){
    if(fopen(LOVE".inp", "r")){
        freopen(LOVE".inp", "r", stdin);
        freopen(LOVE".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}
/*
1
tfttefffeeefkkttfkkt
*/


