#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for(int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for(int i = (a), _b = (b); i >= _b; --i)
#define REP(i, n) for(int i = 0, _n = (n); i < _n; ++i)
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
#define parity(x) __builtin_parity(x)
#define parityll(x) __builtin_parityll(x)
#define assert(x) if(!(x)) cout << "error", exit(0)

template <class X, class Y>
bool minimize(X &x, Y y) { return x > y ? x = y, true : false; }

template <class X, class Y>
bool maximize(X &x, Y y) { return x < y ? x = y, true : false; }

template <class T>
void printVec(vector<T> &vec){ for(T x: vec) cout << x << ' '; cout << '\n'; }

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

const int inf = 1e9;
const long long infll = 1e18;

const int maxN = 1e6 + 17;

struct Vector {
    long long x, y;
    Vector operator - (const Vector& other) const { return {x - other.x, y - other.y}; }
    long long operator * (const Vector& other) const { return x * other.y - y * other.x; }
};

int n, H;
Vector P[maxN];
long double L[maxN], R[maxN];

inline long long CCW(const Vector& A, const Vector& B, const Vector& C){ return (B - A) * (C - A); }
inline long double getintersect(const Vector& A, const Vector& B){ return A.x - 1.0L * (A.x - B.x) / (A.y - B.y) * (A.y - H); }

void process(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> H;
    FOR(i,1,n) cin >> P[i].x >> P[i].y;

    vector<Vector> CH;
    for(int i = 2; i <= n; ++i){
        while(CH.size() >= 2 && CCW(*prev(prev(CH.end())), CH.back(), P[i]) >= 0) CH.pop_back();
        CH.push_back(P[i]);
        if(i % 2 == 1 && CH.size() >= 2) L[i] = getintersect(CH.back(), *prev(prev(CH.end())));
    }

    CH.clear();
    for(int i = n - 1; i >= 1; --i){
        while(CH.size() >= 2 && CCW(*prev(prev(CH.end())), CH.back(), P[i]) <= 0) CH.pop_back();
        CH.push_back(P[i]);
        if(i % 2 == 1 && CH.size() >= 2) R[i] = getintersect(CH.back(), *prev(prev(CH.end())));
    }

    vector<pair<long double,long double>> ranges;
    for(int i = 3; i <= n-2; i += 2) ranges.emplace_back(L[i], R[i]);

    sort(all(ranges));
    int ans = 0;
    for(int i = 0; i < (int)ranges.size();){
        int j = i;
        long double to = 1e18L;
        while(j < (int)ranges.size() && ranges[j].first <= to){ minimize(to, ranges[j].second); ++j; }
        ++ans;
        i = j;
    }
    cout << ans << '\n';
}

int main(){
    #define LOVE "code"
    if(fopen(LOVE".inp", "r")) freopen(LOVE".inp", "r", stdin);

    ios::sync_with_stdio(false); cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while(T--) process();
    return 0;
}
