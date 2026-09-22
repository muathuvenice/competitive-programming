#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 5;
int T, N, Q, K;
const int LOG = 16;
vector<int> adj[maxN];
vector<int> ver;
int w[maxN];
int par[LOG + 1][maxN], Max[LOG + 1][maxN];
int depth[maxN], in[maxN], cnt, imp[maxN];
void DFS(int u = 1){
    in[u] = ++cnt;
    for(int v : adj[u]){
        depth[v] = depth[u] + 1;
        par[0][v] = u;
        Max[0][v] = w[v];
        DFS(v);
    }
}
long long res = 0;
int lca(int u, int v){
    if(depth[v] > depth[u]) swap(u, v);
    for(int i = LOG; i >= 0; --i)if(depth[par[i][u]] >= depth[v]){
        u = par[i][u];
    }
    if(u == v) return u;
    for(int i = LOG; i >= 0; --i){
        if(par[i][u] != par[i][v]){
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][u];
}
int getMax(int u, int v){
    if(depth[v] > depth[u]) swap(u, v);
    int res = 0;
    for(int i = LOG; i >= 0; --i)if(depth[par[i][u]] >= depth[v]){
        res = max(res, Max[i][u]);
        u = par[i][u];
    }
    if(u == v) return res;
    for(int i = LOG; i >= 0; --i){
        if(par[i][u] != par[i][v]){
            res = max(res, Max[i][u]);
            res = max(res, Max[i][v]);
            u = par[i][u];
            v = par[i][v];
        }
    }
    res = max(res, Max[0][u]);
    res = max(res, Max[0][v]);
    return res;
}
bool comp(const int &a, const int &b){
    return in[a] < in[b];
}
struct edge{
    int u, v, w;
    bool operator < (const edge &rhs){
        return w < rhs.w;
    }
}e[maxN];
int root[maxN], sz[maxN];
int find_root(int v){
    return root[v] = root[v] == v ? v : find_root(root[v]);
}
void union_set(int u, int v, int w){
    u = find_root(u);
    v = find_root(v);
    if(sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    root[v] = u;
    res += 1ll * w * imp[u] * imp[v];
    imp[u] += imp[v];
    return ;
}
void solve(){
    sort(ver.begin(), ver.end(), comp);
    int szz = ver.size();
    int cnt = 0;
    for(int i = 0; i < szz - 1; ++i){
        ver.push_back(lca(ver[i], ver[i + 1]));
    }
    sort(ver.begin(), ver.end(), comp);
    ver.erase(unique(ver.begin(), ver.end()), ver.end());
    stack<int> st;
    st.push(ver[0]);
    for(int i = 1; i < ver.size(); ++i){
        int u = ver[i];
        while(lca(u, st.top()) != st.top())st.pop();
        e[++cnt] = {st.top(), u, getMax(st.top(), u)};
        st.push(u);
    }
    sort(e + 1, e + 1 + cnt);
    for(int v : ver)root[v] = v, sz[v] = 1;
    for(int i = 1; i <= cnt; ++i){
        union_set(e[i].u, e[i].v, e[i].w);
    }
}
int main(){

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    depth[0] = -1;
    cin >> T;
    while(T--){
        cnt = 0;
        cin >> N >> Q;
        for(int i = 1; i <= N; ++i){
            adj[i].clear();
        }
        for(int i = 2, p; i <= N; ++i){
            cin >> p;
            adj[p].push_back(i);
        }
        for(int i = 2; i <= N; ++i){
            cin >> w[i];
        }
        for(int j = 0; j <= 16; ++j){
            for(int i = 1; i <= N; ++i){
                par[j][i] = Max[j][i] = 0;
            }
        }
        DFS();
        for(int j = 1; j <= 16; ++j){
            for(int i = 1; i <= N; ++i){
                par[j][i] = par[j - 1][par[j - 1][i]];
                Max[j][i] = max(Max[j - 1][i], Max[j - 1][par[j - 1][i]]);
            }
        }
        while(Q--){
            cin >> K;
            res = 0;
            ver.clear();
            for(int i = 1, u; i <= K; ++i){
                cin >> u;
                ver.push_back(u);
                imp[u] = 1;
            }
            solve();
            for(int x : ver)imp[x] = 0;
            cout << res << " ";
        }
    }
    return 0;
}
