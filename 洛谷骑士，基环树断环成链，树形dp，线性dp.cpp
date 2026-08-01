#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Edge {
    int to, next;
};
vector<Edge> edge;
ll n, indx = 0, tot = 0, cnt = 0;
vector<int> a, head, belong, dfn, par;
void add(int u, int v) {
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}
void dfs1(int begin) {//找出基环树的环
    dfn[begin] = ++tot;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if (!dfn[to]) {
            par[to] = begin;
            dfs1(to);
        }
        else if (dfn[to] > dfn[begin]) {
            ++cnt;
            while (to != begin) {
                belong[to] = cnt;
                to = par[to];
            }
            belong[begin] = cnt;
        }
    }
}
vector<vector<ll> > dp;
vector<bool> cir;
void dfs2(int begin, int parent) {//树形dp出环上节点的权值
    if (cir[begin]) return;
    cir[begin] = true;
    dp[begin][1] = a[begin];
    dp[begin][0] = 0;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if(belong[to]) continue;
        if (!cir[to]) {
            dfs2(to, begin);
            dp[begin][1] = max(dp[begin][1], dp[to][0] + dp[begin][1]);
            dp[begin][0] = max(dp[to][1] + dp[begin][0], dp[to][0] + dp[begin][0]);
        }
    }
}
vector<bool> flag;
map<int,vector<ll>> ds;
void dfs3(int begin,int version) {//将环上节点推入对应的集合中处理
    if (flag[begin]) return;
    flag[begin] = true;
    ds[version].push_back(begin);
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if (!flag[to]&&belong[to]) {
            dfs3(to,version);
        }
    }
}
ll pos_mod(ll a,ll b) {
    return (a % b + b) % b;
}
void solve() {
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs1(i);
    }
    dp = vector<vector<ll> >(n + 1, vector<ll>(3, 0));
    map<int,vector<int> > start;
    cir = vector <bool>(n + 1);
    for (int i = 1;i <= n;i++) {
        if (belong[i]) {
            start[belong[i]].push_back(i);
        }
    }
    flag = vector<bool>(n + 1);
    for(auto [val,v] : start){
        for (int i = 0;i < v.size();i++) {
            dfs2(v[i], -1);
        }
    }
    ll ans = 0;
    int bg = 0;
    for(auto [val,v] : start){
        dfs3(v[0],++bg);
    }
    ll ans1 = 0,ans2 = 0;
    for(auto [version,v] : ds){
        vector<vector<ll> > f1(v.size()+1,vector<ll> (2,0));
        vector<vector<ll> > f2(v.size()+1,vector<ll> (2,0));
        f1[0][0] = -1e12;
        f1[0][1] = dp[v[0]][1];
        f2[0][1] = -1e12;
        f2[0][0] = dp[v[0]][0];
        for (int i = 1;i < v.size();i++) {//处理环形dp我强制第一个拿将不拿设为-1e12，再设一个f2为第一个强制不拿
            f1[i][0] = max(dp[v[i]][0]+f1[(i-1)%v.size()][0],f1[(i-1)%v.size()][1]+dp[v[i]][0]);
            f1[i][1] = max(f1[i][1],f1[pos_mod(i-1,v.size())][0]+dp[v[i]][1]);    
        }
        ans1 = f1[v.size()-1][0];
        for(int i = 1;i < v.size(); i++){
            f2[i][0] = max(f2[(i-1)%v.size()][0] + dp[v[i]][0],f2[(i-1)%v.size()][1]+dp[v[i]][0]);
            f2[i][1] = max(f2[(i-1)%v.size()][0] + dp[v[i]][1],f2[i][1]);
        }
        ans2 = max(f2[v.size()-1][0],f2[v.size()-1][1]);
        // cout<<ans1<<" "<<ans2<<"\n";
        ans += max(ans1,ans2);
        // cout<<ans1<<ans2<<"\n";
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> n;
    a = vector<int>(n + 1);
    edge = vector<Edge>((n + 1) * 3);
    belong = vector<int>(n + 1, 0);
    dfn = par = belong;
    head = vector<int>(n + 1, -1);
    for (int i = 1;i <= n;i++) {
        int u;
        cin >> a[i] >> u;
        add(u, i);
        add(i, u);
    }
    solve();
}
