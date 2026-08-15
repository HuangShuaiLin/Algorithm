#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int MAX = 200007;
using ii = __int128;
const ll mod = 1000000007;
struct Edge{
    int to,next;
};
vector<bool> flag;
int n;
vector<Edge> edge;
vector<ll> head,belong,dfn,par,sz;
int indx = 0,cnt = 0,tot = 0;
void add(int u,int v){
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}

void dfs1(int begin){
    dfn[begin] = ++tot;
    for(int i = head[begin];i!=-1;i = edge[i].next){
        int to = edge[i].to;
        if(!dfn[to]){
            par[to] = begin;
            dfs1(to);
        }else if(dfn[to]>dfn[begin]){
            int x = 1;
            cnt++;
            while(to!=begin){
                belong[to] = cnt;
                x++;
                to = par[to];
            }
            belong[begin] = cnt;
            sz[begin] = x;
        }
    }
}
void dfs2(int begin){
    sz[begin] = 1;
    for(int i=head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(!flag[to]){
            flag[to] = true;
            dfs2(to);
            sz[begin] += sz[to];
        }
    }
}
void solve(){
    indx = 0;
    tot = 0;
    cnt = 0;
    edge = vector<Edge> (4*(n+1));
    head = vector<ll> ((n+1),-1);
    belong = vector<ll> (n+1,0);
    sz = par = dfn = belong;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1);
    flag = vector<bool> (n+1,0);
    vector<ll> start;
    for(int i=1;i<=n;i++){
        if(belong[i]) {start.push_back(i);flag[i] = true;}
    }
    for(int i=0;i<start.size();i++){
        dfs2(start[i]);
    }
    ll ans = 0;
    ll res = 0;
    for(int i=0;i<start.size();i++){
        res += (sz[start[i]] *(sz[start[i]]-1))/2;
        ans += sz[start[i]] * (n-sz[start[i]]);
    }
    cout<<ans+res<<"\n";
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        solve();
    }
}
