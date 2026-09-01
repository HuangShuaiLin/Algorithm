#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int to,next;
};
int n,m,s;
vector<int> ans;
vector<tuple<int,int,int> > q;
vector<vector<pair<int,int> > > g;
vector<bool> flag;
vector<Edge> edge;
vector<int> head;
int par[1100000];
int indx = 0;
void add(int u,int v){
    edge.emplace_back(v,head[u]);
    head[u] = indx++;
    edge.emplace_back(u,head[v]);
    head[v] = indx++;
}
int find(int u){
    if(u != par[u]){
        par[u] = find(par[u]);
    }
    return par[u];
}
void merge(int u,int v){
    int ru = find(u),rv = find(v);
    if(ru != rv){
        par[ru] = rv;
    }
}

void tarjan(int begin){
    if(flag[begin]) return ;
    flag[begin] = true;
    for(int i=0;i<g[begin].size();i++){
        if(!flag[g[begin][i].first]) continue;
        int cop = find(g[begin][i].first);
        int root = find(begin);
        // if(cop == root) continue;
        // cout<<begin<<" "<<root<<endl;
        ans[g[begin][i].second] = cop;
        // merge(root,cop);//在收集答案的过程中不要去合并集合
    }
    for(int i=head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(flag[to]) continue;
        tarjan(to);
        merge(to,begin);//只有在访问完子树后再合并子树集合
        // cout<<begin<<" "<<to<<" "<<find(begin)<<"\n";
    }
}

void solve(){
    head.assign(n+1,-1);
    for(int i=1;i<=n;i++) par[i] = i;
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    ans.assign(n+1,0);
    flag.assign(n+1,0);
    g = vector<vector<pair<int,int> > > (n+1);
    q.assign(m+1,{0,0,0});
    for(int i = 1;i <= m;i ++){
        int u,v;
        cin>>u>>v;
        // q[i] = {u,v,i};
        g[u].push_back({v,i});
        g[v].push_back({u,i});      
    }
    tarjan(s);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<"\n";
    }
}
int main(){
    cin>>n>>m>>s;
    solve();
}
