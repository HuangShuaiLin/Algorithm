#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
struct Edge{
    ll to,next,cap;
};
int n,m,s,t;
vector<Edge> edge;
vector<ll> cur,level,head;
int indx = 0;
void add(int u,int v,int w){
    edge.emplace_back(v,head[u],w);
    head[u] = indx++;

    edge.emplace_back(u,head[v],0);
    head[v] = indx++;
}
bool bfs(int begin){
    queue<int> pq;
    pq.push(begin);
    fill(level.begin(),level.end(),-1);
    level[begin] = 0;
    while(!pq.empty()){
        int bg = pq.front();
        pq.pop();
        for(int i=head[bg];i!=-1;i=edge[i].next){
            int to = edge[i].to;
            if(edge[i].cap <= 0) continue;
            if(level[to] != -1) continue;
            level[to] = level[bg] + 1;
            pq.push(to);
        }
    }
    if(level[t] == -1) return false;
    return true;
}

ll dfs(int begin,ll flow){
    if(begin == t){
        return flow;
    }
    for(ll &i=cur[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(edge[i].cap <= 0) continue;
        if(level[to] != level[begin] + 1) continue;
        ll fl = dfs(to,min(flow,edge[i].cap));
        if(fl){
            edge[i ^ 1].cap += fl;
            edge[i].cap -= fl;
            return fl;
        }
    }
    return 0;
}

void Dinic(){
    ll ans = 0;
    while(bfs(s)){
        cur = head;
        ll flow = INF;
        while(ll fl = dfs(s,flow)){
            ans += fl;
        }
    }
    cout<<ans<<"\n";
}
void solve(){
    level.assign(n + 7 , -1);
    head.assign(n + 7 , -1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
    }
    Dinic();
}


int main(){
    cin>>n>>m>>s>>t;
    solve();
}
