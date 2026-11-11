#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include<map>
#include<unordered_map>
#include<queue>
#include<array>
#include<string.h>
#include<random>
#include<stack>
#include<list>
#include<deque>
#include<set>
#include<sstream>
#include<chrono>
/*
                                Kruskal重构树
*/
using namespace std;
using ll = long long;
using ii = long long;
using ull = unsigned long long;
const int MAX = 200010;
const ll mod = 998244353;
struct Edge {
    int to, next;
};
int n, m;
vector<Edge> edge;
//重链剖分+链式前向星
vector<ll> mainPar, head, par, sz, son, depth, belong;
vector<tuple<ll, int, int> > tii;//
vector<ll> weight;//新建节点的点权
int indx = 0, tot = 0;
ll sum = 0;
int find(int u) {
    if (u != par[u]) {
        par[u] = find(par[u]);
    }
    return par[u];
}
void merge(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru != rv) {
        par[ru] = rv;
    }
}
void add(int u, int v) {
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}
vector<bool> flag;
void dfs1(int begin) {
    if (flag[begin]) return;
    flag[begin] = true;
    sz[begin] = 1;
    int ma = 0, dx = 0;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if (!flag[to]) {
            mainPar[to] = begin;
            depth[to] = depth[begin] + 1;
            dfs1(to);
            sz[begin] += sz[to];
            if (ma < sz[to]) {
                ma = sz[to];
                dx = to;
            }
        }
    }
    son[begin] = dx;
}
void dfs2(int begin, int par) {
    if (son[par] == begin) belong[begin] = belong[par];
    if (son[begin]) dfs2(son[begin], begin);
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if (son[begin] != to && par != to) {
            dfs2(to, begin);
        }
    }
}
int getLCA(int u, int v) {
    while (belong[u] != belong[v]) {
        if (depth[belong[u]] > depth[belong[v]]) swap(u, v);
        v = mainPar[belong[v]];
        // cout<<u<<" ";
    }
    return depth[u] > depth[v] ? v : u;
}
void solve() {
    flag = vector<bool>(n * 2 + 1, 0);
    mainPar = son = sz = depth = belong = vector<ll>(n * 2 + 1, 0);
    sort(tii.begin() + 1,tii.end());
    tot = n;
    for(int i=1;i<=m;i++){//Kruskal建树逻辑
        auto [d, u, v] =  tii[i];//贪心找最小
        int ru = find(u), rv = find(v);//找到他们当前树中的根
        if (ru == rv) continue;
        ++tot;
        merge(ru, tot);//并查集创建新节点并将这个节点变成新的根
        merge(rv, tot);
        add(ru, tot), add(tot, ru);//加边
        add(rv, tot), add(tot, rv);
        sum += d;//统计权值
        weight[tot] = d;//创建新节点他们的距离就是点权
    }
    int root = 0;
    for (int i = 1;i <= tot;i++) mainPar[i] = i, belong[i] = i;
    unordered_map<int,int> mp;
    for(int i=1;i<=n;i++){//图不连通时 收集森林每个树的根节点
        mp[find(i)]++;
    }
    for(auto [val,num] : mp){//对每一个根进行树链剖分
        dfs1(val);
        dfs2(val, val);
    }
    int q;
    cin >> q;
    for (int i = 1;i <= q;i++) {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v)) {//若不在一个DSU里，那么就不连通
            cout << "impossible\n";
            continue;
        }
        cout << weight[getLCA(u, v)] << "\n";//得到LCA的点权，就是他们连通时最大边的最小的权值
    }
}

int main() {
    cin >> n >> m;
    indx = 0, tot = 0;
    par = weight = vector<ll>(n * 2 + 1, 0);
    edge = vector<Edge>(n * 4 + 7);
    head = vector<ll>(n * 2, -1);
    tii = vector<tuple<ll, int, int> >(m + 1);
    for (int i = 1;i <= m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        tii[i] = { w,u,v };
    }
    for (int i = 1;i <= 2 * n;i++) {
        par[i] = i;
    }
    if(n == 1){
        int q;
        cin>>q;
        for(int i=1;i<=q;i++){
            int u,v;
            cin>>u>>v;
            cout<<0<<"\n";
        }
        return 0;
    }
    solve();
}