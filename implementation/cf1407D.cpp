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
const int maxN = 3e5 + 5;
int n, h[maxN];
int f[maxN];
stack<int> st;
vector<int> adj[maxN];
int lMax[maxN], rMax[maxN], lMin[maxN], rMin[maxN];
void process(){
    cin >> n;
    FOR(i, 1, n)cin >> h[i];
    FOR(i, 1, n){
        while(!st.empty() && h[st.top()] <= h[i])st.pop();
        if(!st.empty())lMax[i] = st.top();
        else lMax[i] = i;
        st.push(i);
    }
    while(!st.empty())st.pop();
    REP(i, n, 1){
        while(!st.empty() && h[st.top()] <= h[i])st.pop();
        if(!st.empty())rMax[i] = st.top();
        else rMax[i] = i;
        st.push(i);
    }
    while(!st.empty())st.pop();
    FOR(i, 1, n){
        while(!st.empty() && h[st.top()] >= h[i])st.pop();
        if(!st.empty())lMin[i] = st.top();
        else lMin[i] = i;
        st.push(i);
    }
    while(!st.empty())st.pop();
    REP(i, n, 1){
        while(!st.empty() && h[st.top()] >= h[i])st.pop();
        if(!st.empty())rMin[i] = st.top();
        else rMin[i] = i;
        st.push(i);
    }
    FOR(i, 1, n - 1)adj[i].emplace_back(i + 1);
    FOR(i, 1, n){
        if(lMax[i] < rMax[i] && h[i] < min(h[lMax[i]], h[rMax[i]])){
            adj[lMax[i]].emplace_back(rMax[i]);
        }
        if(lMin[i] < rMin[i] && h[i] > max(h[lMin[i]], h[rMin[i]])){
            adj[lMin[i]].emplace_back(rMin[i]);
        }
    }

    queue<int> q;
    f[1] = 1;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            if(!f[v]){
                f[v] = f[u] + 1;
                q.push(v);
            }
        }
    }
    cout << f[n] - 1;
}
#define NAME ""
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



