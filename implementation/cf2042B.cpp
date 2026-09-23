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
int n, cnt[maxN];
struct dt{
    int cnt, val;
    bool operator < (const dt &rhs) const {
        if((cnt & 1) && (rhs.cnt & 1)) return cnt > rhs.cnt;
        return !(cnt & 1);
    }
};
priority_queue<dt> q;
int full[maxN];
void process(){
    cin >> n;
    FOR(i, 1, n)cnt[i] = 0, full[i] = 0;
    FOR(i, 1, n){
        int c;
        cin >> c;
        cnt[c]++;
    }
    int answer = 0;
    FOR(i, 1, n)if(cnt[i] > 0)q.push({cnt[i], i});
    int turn = 0;
    while(!q.empty()){
        auto[c, val] = q.top();
        q.pop();
        turn ^= 1;
        if(turn){
            if(!full[val]){
                ++answer;
            }
            full[val]++;
            if(full[val] == cnt[val])++answer;
            --c;
            if(c > 0)q.push({c, val});
        }else{
            --c;
            if(c > 0)q.push({c, val});
        }
    }
    cout << answer << '\n';
}
#define NAME "A"
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



