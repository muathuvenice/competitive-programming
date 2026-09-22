#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
int t, n, m, x[100001], y[100001], cnt=0, num[100001], low[100001], canh[100001], sz[100001], cntscc=0;
bool bridge[100001], vis[100001], edge[100001];
vector<pair<int, int>> ke[100001];
vector<int> now;
void dfs(int u, int p){
    low[u]=num[u]=++cnt;
    for(auto [v, id]: ke[u]){
        if(v==p)continue;
        if(num[v]==0){
            dfs(v, u);
            low[u]=min(low[u], low[v]);
            if(num[v]==low[v])bridge[id]=true;
        }
        else low[u]=min(low[u], num[v]);
    }
}
void dfs2(int u){
    now.push_back(u);
    for(auto [v, id]: ke[u]){
        if(!bridge[id] and !edge[id]){
            canh[cntscc]++;
            edge[id]=true;
        }
        if(!vis[v] and !bridge[id]){
            vis[v]=true;
            sz[cntscc]++;
            dfs2(v);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(nullptr);
   
    cin>>t;
    while(t--){
        cin>>n>>m;
        memset(vis, false, sizeof(vis));
        memset(bridge, false, sizeof(bridge));
        memset(edge, false, sizeof(edge));
        int res=1e9;
        cnt=0;
        for(int i=1;i<=n;i++){
            low[i]=0;
            num[i]=0;
            ke[i].clear();
        }
        for(int i=1;i<=m;i++){
            cin>>x[i]>>y[i];
            ke[x[i]].push_back({y[i], i});
            ke[y[i]].push_back({x[i], i});
        }
        for(int i=1;i<=n;i++){
            if(num[i]==0)dfs(i, 0);
        }
        int chutrinh=0;
        cntscc=0;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                cntscc++;
                sz[cntscc]=1;
                canh[cntscc]=0;
                vis[i]=true;
                dfs2(i);
                if(sz[cntscc]>=3){
                    chutrinh++;
                    while(!now.empty()){
                        int v=now.back();
                        int N=sz[cntscc]-1;
                        int M=canh[cntscc];
                        for(auto [k, id] : ke[v]){
                            if(!bridge[id])M--;
                        }
                        if(N-1>=M){
                            //cout<<"xoadc: "<<v<<"\n";
                            res=min(res, v);
                        }
                        now.pop_back();
                    }
                }
                else now.clear();
            }
        }
        if(chutrinh>=2 || res==1e9)cout<<"-1\n";
        else cout<<res<<"\n";
    }
    return 0;
}


