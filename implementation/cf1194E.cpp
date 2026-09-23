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
const int maxN = 1e5 + 5;
const int MAX = 1e4 + 1;
const int COS = 5e3 + 1;
int n;
vector<pair<int, int>> ex[MAX + 1], ey[MAX + 1];
pair<int, int> event[maxN];
int fw[MAX + 1];
void update(int x, int v){
    for(; x <= MAX; x += x &- x)fw[x] += v;
}
int get(int x){
    int res = 0;
    for(; x >= 1; x &= x - 1)res += fw[x];
    return res;
}
vector<int> queryX, queryY;
void process(){
    cin >> n;
    FOR(i, 1, n){
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        x += COS, y += COS, u += COS, v += COS;
        if(y == v){
            ex[y].emplace_back(min(x, u), max(x, u));
            queryX.emplace_back(y);
        }else{
            ey[x].emplace_back(min(y, v), max(y, v));
            queryY.emplace_back(x);
        }
    }
    sort(all(queryX));
    sort(all(queryY));
    uni(queryX);
    uni(queryY);
    long long answer = 0;
    int szY = (int)queryY.size();
    int szX = (int)queryX.size();
    for(int i = 0; i < szY; ++i){
        int y = queryY[i];
        for(auto[Lx, Rx] : ey[y]){
            int cntEvent = 0;
            int p = lower_bound(all(queryX), Lx) - queryX.begin();
            while(p < szX && queryX[p] <= Rx){
                int x = queryX[p];
                for(auto[Ly, Ry] : ex[x]){
                    if(Ly <= y && Ry > y){
                        update(x, 1);
                        event[++cntEvent] = mp(Ry, x);
                    }
                }
                ++p;
            }
            sort(event + 1, event + 1 + cntEvent);
            p = 1;
            for(int j = i + 1; j < szY; ++j){
                int nxtY = queryY[j];
                while(p <= cntEvent && event[p].first < nxtY){
                    update(event[p].second, -1);
                    ++p;
                }
                for(auto[Lx, Rx] : ey[nxtY]){
                    int rem = get(Rx) - get(Lx - 1);
                    answer += rem * (rem - 1) >> 1;
                }
            }
            while(p <= cntEvent){
                update(event[p].second, -1);
                ++p;
            }
        }
    }

    cout << answer;
}
#define NAME "2814"
int main(){
    if(fopen(NAME".inp", "r")){
        freopen(NAME".inp", "r", stdin);
//        freopen(NAME".out", "w", stdout);
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

