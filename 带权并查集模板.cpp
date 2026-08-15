#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = __int128;
const ll MAX = 2000007;
const ii INF = 2000000000000000000000000;
int par[MAX];
ii dist[MAX];
ll find(ll u){
    if(u!=par[u]){
        int p = par[u];
        par[u] = find(par[u]);
        dist[u] += dist[p];
    }
    // cout<<u<<" "<<par[u]<<endl;
    return par[u];
}
ii query(int u,int v){//查询u到v的两点距离
    if(find(u) == find(v)){
        return dist[u] - dist[v]; 
    }
    return INF;
}
void merge(int u,int v,ii w){//前->后,u的老父亲是v并且在一维数轴上表现出来的样子的距离就是w
    int ru = find(u);
    int rv = find(v);
    if(ru != rv){
        par[ru] = rv;
        dist[ru] =  dist[v] - dist[u] + w;
        // cout<<ru<<" "<<rv<<" "<<dist[ru]<<endl;
    }
}
string print(ii a){
    if(a == 0) return "0";
    string s;
    bool fl = false;
    if(a < 0){
        a = -a;
        fl = true;
    }
    while(a){
        int t = a % 10;
        a /= 10;
        s += t + '0';
    }
    if(fl) s += '-';
    reverse(s.begin(),s.end());
    return s;
}
int n,m,q;
void solve(){
    for(int i=1;i<MAX;i++){par[i] = i;}
    for(int i=1;i<=m;i++){
        ll l,r,S;
        cin>>l>>r>>S;
        merge(l,r+1,ii(S));
        // cout<<dist[l]<<" "<<dist[r]<<endl;
        // cout<<l<<" "<<r<<" "<<S<<" "<<query(l,r)<<endl;
        // cout<<query(1,3)<<endl;
        // cout<<query(l,r+1)<<endl;
    }
    // cout<<query(1,4)<<endl;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        if(query(l,r+1) == INF){
            cout<<"UNKNOWN\n";
        }else cout<<print(query(l,r+1))<<"\n";
    }
}
int main(){
    cin>>n>>m>>q;
    solve();
}
