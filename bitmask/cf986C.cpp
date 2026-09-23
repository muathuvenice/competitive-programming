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
const int maxN = 2e5 + 5;
const int inf = 1e9;
const long long infll = 1e18;
int n, m, a[1 << 22], maxMask;
bool visited[1 << 22], exist[1 << 22];
void dfs(int u){
    visited[u] = true;
    if(exist[u] && !visited[maxMask ^ u]) dfs(maxMask ^ u);
    for(int sub = u ; sub > 0; sub ^= sub & -sub){
        if(!visited[u ^ (sub & -sub)]){
            dfs(u ^ (sub & -sub));
        }
    }
}
void process(){
    cin >> m >> n;
    maxMask = Mask(m) - 1;
    FOR(i, 0, n - 1){
        cin >> a[i];
        exist[a[i]] = true;
    }
    int answer = 0;
    FOR(i, 0, n - 1){
        if(!visited[a[i]]){
            dfs(maxMask ^ a[i]);
            ++answer;
        }
    }
    cout << answer;
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
//    cin >> t;
    while(t--)
        process();
//    cerr << '\n' << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC) << " s\n" ;
    return 0;
}




