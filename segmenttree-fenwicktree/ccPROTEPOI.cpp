#include <bits/stdc++.h>
/*
I might never be your knight in shining armor
I might never be the one you take home to mother
And I might never be the one who brings you flowers
But I can be the one, be the one tonight

When I first saw you
From across the room
I could tell that you were curious
Oh, yeah

Girl, I hope you're sure
What you're looking for
'Cause I'm not good at making promises

But if you like causing trouble up in hotel rooms
And if you like having secret little rendezvous
If you like to do the things you know that we shouldn't do
Then, baby, I'm perfect
Baby, I'm perfect for you

And if you like midnight driving with the windows down
And if you like going places we can't even pronounce
If you like to do whatever you've been dreaming about
Then, baby, you're perfect
Baby, you're perfect
So let's start right now

I might never be the hands you put your heart in
Or the arms that hold you any time you want them
But that don't mean that we can't live here in the moment
'Cause I can be the one you love from time to time

When I first saw you
From across the room
I could tell that you were curious
Oh, yeah

Girl, I hope you're sure
What you're looking for
'Cause I'm not good at making promises

But if you like causing trouble up in hotel rooms
And if you like having secret little rendezvous
If you like to do the things you know that we shouldn't do
Then, baby, I'm perfect
Baby, I'm perfect for you

And if you like midnight driving with the windows down
And if you like going places we can't even pronounce
If you like to do whatever you've been dreaming about
Then, baby, you're perfect
Baby, you're perfect
So let's start right now

And if you like cameras flashing every time we go out
Oh, yeah
And if you're looking for someone to write your break-up songs about
Baby, I'm perfect
And, baby, we're perfect

If you like causing trouble up in hotel rooms
And if you like having secret little rendezvous
If you like to do the things you know that we shouldn't do
Then, baby, I'm perfect
Baby, I'm perfect for you

And if you like midnight driving with the windows down
And if you like going places we can't even pronounce
If you like to do whatever you've been dreaming about
Then, baby, you're perfect
Baby, you're perfect
So let's start right now
*/
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
#define Ctz(x) __builtin_ctz(x) // so luong so 0 tinh tu ben phai
#define Ctzll(x) __builtin_ctzll(x)
#define Clz(x) __builtin_clz(x) // so luong so 0 tinh tu ben trai
#define Clzll(x) __builtin_clzll(x)
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
const int inf = 1e9;
const long long infll = 1e18;
int n, k, m;
pair<int, int> s1[maxN], s2[maxN];
int vir = 0, hor = 0;
int L = n / 2 + 1;
int R = n / 2 + 1;
bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    return a.second != b.second ? a.second < b.second : a.first < b.first;
}
int it[maxN << 3];
vector<int> compress;
void build(int id, int l, int r){
    if(l == r){
        if(compress[l - 1] < L) it[id] = 0;
        else it[id] = inf;
        return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    it[id] = min(it[id << 1], it[id << 1 | 1]);
}
void update(int id, int l, int r, int p, int v){
    if(l == r){
        minimize(it[id], v);
        return;
    }
    int mid = l + r >> 1;
    if(p <= mid) update(id << 1, l, mid, p, v);
    else update(id << 1 | 1, mid + 1, r, p, v);
    it[id] = min(it[id << 1], it[id << 1 | 1]);
}
int get(int id, int l, int r, int u, int v){
    if(l >= u && r <= v) return it[id];
    int mid = l + r >> 1;
    if(v <= mid) return get(id << 1, l, mid, u, v);
    if(u > mid) return get(id << 1 | 1, mid + 1, r, u, v);
    return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}
int query(int n, pair<int, int> seg[]){
    compress.clear();
    FOR(i, 1, n){
        compress.emplace_back(seg[i].first);
        compress.emplace_back(seg[i].second);
    }
    compress.emplace_back(L);
    compress.emplace_back(R);
    sort(all(compress));
    uni(compress);
    sort(seg + 1, seg + 1 + n, cmp);
    int sz = compress.size();
    build(1, 1, sz);
    FOR(i, 1, n){
        if(seg[i].first == L){
            int p = lower_bound(all(compress), seg[i].second) - compress.begin() + 1;
            update(1, 1, sz, p, 1);
            continue;
        }
        int u = lower_bound(all(compress), seg[i].first - 1) - compress.begin() + 1;
        int v = lower_bound(all(compress), seg[i].second - 1) - compress.begin() + 1;
        int val = get(1, 1, sz, u, v);
        int p = lower_bound(all(compress), seg[i].second) - compress.begin() + 1;
        update(1, 1, sz, p, val + 1);
    }
    int x = lower_bound(all(compress), R) - compress.begin() + 1;
    return get(1, 1, sz, x, sz);
}
void process(){
    cin >> n >> k >> m;

    vir = 0;
    hor = 0;
    L = (n - k) / 2 + 1, R = (n - k) / 2 + k;
    FOR(i, 1, m){
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        if(x > u) swap(x, u);
        if(y > v) swap(y, v);
        s1[++hor] = mp(y, v);
        s2[++vir] = mp(x, u);
    }
    int ans1 = query(hor, s1);
    int ans2 = query(vir, s2);
//    cout << ans1 << ' ' << ans2 << '\n';
    if(ans1 > n || ans2 > n){
        cout << -1 << '\n';
        return;
    }
//    cout << ans1 << ' ' << ans2 << '\n';
    cout << ans1 + ans2 << '\n';
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




