#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int to,next;
};
void dfs1(vector<Edge> &edge,vector<int> &dfn,int begin,vector<bool> &vis,vector<int> &head){
        if(vis[begin]) return ;
        vis[begin] = true;
        for(int i = head[begin];i!=-1;i=edge[i].next){
            int to = edge[i].to;
            if(!vis[to]){
                dfs1(edge,dfn,begin,vis,head);
            }
        }
    dfn.push_back(begin);
}
void dfs2(int begin,vector<Edge> &edge,vector<int> &head,vector<bool> &vis){
    if(vis[begin]) return;
    vis[begin] = true;
    for(int i = head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(!vis[to]){
            dfs2(to,edge,head,vis);
        }
    }
}
void add(vector<Edge> &edge,vector<int> &head,int u,int v,int &indx){
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}
void solve(int n,int m){
    int indx1 = 0,indx2 = 0;
    vector<vector<Edge> > edge(2,vector<Edge>(m+1));
    vector<vector<int> > head(2,vector<int> (n+1,-1));
    vector<vector<bool> > vis(2,vector<bool> (n+1,0));
    vector<int> dfn;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(edge[0],head[0],u,v,indx1);
        add(edge[1],head[1],v,u,indx2);
    }
    for(int i=1;i<=n;i++)
    if(!vis[0][i])
    dfs1(edge[0],dfn,i,vis[0],head[0]);

    dfs2(dfn.back(),edge[1],head[1],vis[1]);
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(vis[1][i]) cnt++;
    }
    if(cnt==n) cout<<"Yes\n";
    else cout<<"No\n";
}
int main(){
    int n,m;
    cin>>n>>m;
    solve(n,m);
}
