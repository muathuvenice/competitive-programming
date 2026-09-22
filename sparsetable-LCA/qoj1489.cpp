#include "jumps.h"
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
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
#define left __left
#define down __down
#define right __right
#define up __up
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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int h[maxN], n;
int lg[maxN], L[maxN][18], R[maxN][18], Max[maxN][18], best[maxN][18];
int query(int u, int v){
    if(h[u] == inf) return v;
    if(h[v] == inf) return u;
    return h[u] > h[v] ? u : v;
}
int getMax(int l, int r){
    assert(l <= r);
    int k = lg[r - l + 1];
    return query(Max[l][k], Max[r - Mask(k) + 1][k]);
}
int jumpLeft(int start, int limit, int maxHeight){
    REP(i, lg[n], 0){
        if(L[start][i] >= limit && h[L[start][i]] < maxHeight)start = L[start][i];
    }
    return start;
}
int minimum_jumps(int A, int B, int C, int D){
    ++A, ++B, ++C, ++D;
    if(R[B][0] >= C){
        return R[B][0] <= D ? 1 : -1;
    }
    assert(B != C - 1);
    int middle = getMax(B + 1, C - 1);
    if(h[middle] > h[getMax(C, D)]) return -1;
//    cout << "middle " << middle << '\n';
    int pos = jumpLeft(B, A, h[middle]);
    if(L[pos][0] >= A){
        if(R[L[pos][0]][0] <= D) return 1;
    }
//    cout << "pos " << ' ' << pos << '\n';
//    cout << best[pos][0] << '\n';
    int answer = 0;
    REP(i, lg[n], 0){
        if(h[best[pos][i]] < h[middle]){
            answer += Mask(i);
            pos = best[pos][i];
        }
    }
    if(R[pos][0] == middle) return answer + 2;
    if(L[pos][0] >= 1 && R[L[pos][0]][0] <= D) return answer + 2;
    REP(i, lg[n], 0){
        if(h[R[pos][i]] <= h[middle]){
            answer += Mask(i);
            pos = R[pos][i];
        }
    }
//    cout << answer << '\n';
//    cout << "end " << pos << '\n';
    return answer + 1;
}

void init(int N, std::vector<int> H) {
    n = N;
    FOR(i, 1, n)h[i] = H[i - 1];
    h[0] = inf;
    h[n + 1] = inf;
    stack<int> st;
    FOR(i, 1, n){
        while(!st.empty() && h[st.top()] < h[i]) st.pop();
        if(!st.empty())L[i][0] = st.top();

        st.push(i);
    }
    while(!st.empty())st.pop();
    REP(i, n, 1){
        while(!st.empty() && h[st.top()] < h[i])st.pop();
        if(!st.empty())R[i][0] = st.top();

        st.push(i);
    }

    FOR(i, 2, n)lg[i] = lg[i >> 1] + 1;
    FOR(i, 1, n)best[i][0] = query(L[i][0], R[i][0]);
    FOR(j, 1, lg[n]){
        FOR(i, 1, n){
            L[i][j] = L[L[i][j - 1]][j - 1];
            R[i][j] = R[R[i][j - 1]][j - 1];
            best[i][j] = best[best[i][j - 1]][j - 1];
        }
    }
    FOR(i, 1, n)FOR(j, 0, lg[n])if(R[i][j] == 0)R[i][j] = n + 1;
    FOR(i, 1, n)Max[i][0] = i;
    FOR(j, 1, lg[n]){
        FOR(i, 1, n - Mask(j) + 1){
            Max[i][j] = query(Max[i][j - 1], Max[i + Mask(j - 1)][j - 1]);
        }
    }
//    FOR(i, 1, n){
//        FOR(j, 0, lg[n]){
//            cerr << i << ' ' << j << ' ' << best[i][j] << '\n';
//        }
//    }
}



//void process(){
//    int n, q;
//
//    cin >> n >> q;
//    vector<int> h(n);
//    FOR(i, 0, n - 1)cin >> h[i];
//    init(n, h);
//    while(q--){
//        int a, b, c, d;
//        cin >> a >> b >> c >> d;
//        cout << minimum_jumps(a, b, c, d) << '\n';
//    }
//}
//#define LOVE "RainforestJumps"
//int main(){
//    if(fopen(LOVE".inp", "r")){
//        freopen(LOVE".inp", "r", stdin);
//        freopen(LOVE".out", "w", stdout);
//    }
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
//
//    int t = 1;
////    cin >> t;
//    while(t--)
//        process();
////    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
//    return 0;
//}





