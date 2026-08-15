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
using namespace std;
using ll = long long;
using ii = __int128;
using ull = unsigned long long;
const int MAX = 200010;
const ll mod = 998244353;
struct Edge {
    int to, next;
};
/*
    1、dfs(每个轻儿子，0)
    2、dfs(重儿子,1)
    3、统计u自己贡献
    4、每个轻子树重新贡献
    5、得到u的答案
    6、keep==1 保留信息
    7、keep==0 取消
*/
int indx = 0;
vector<Edge> edge;
vector<int> head , color , sz , qy , par , son , res , stacol;
vector<bool> flag;
unordered_map<int,unordered_map<int,bool> > mp;
int diff = 0;
// vector<bool> isMain;
int n, m;
void add(int u, int v) {
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}
void dfs1(int begin) {//树链剖分，区分重儿子和轻儿子
    if(flag[begin])  return ;
    flag[begin] = true;
    sz[begin] = 1;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if(flag[to]) continue;
        mp[begin][to] = true;
        par[to] = begin;
        dfs1(to);
        sz[begin] += sz[to];
    }
    int ma = 0, indx = 0;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if(!mp[begin].count(to)) continue;
        if (ma < sz[to]) {
            ma = sz[to];
            indx = to;
        }
    }
    son[begin] = indx;
}
void dfs3(int begin) {
    stacol[color[begin]]--;
    if(!stacol[color[begin]]) diff--;
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if(!mp[begin].count(to)) continue;
        dfs3(to);
    }
}
void addSon(int begin){
    stacol[color[begin]]++;
    if(stacol[color[begin]] == 1) diff++;
    for(int i=head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(!mp[begin].count(to)) continue;
        addSon(to);
    }
}
void dfs2(int begin, int keep) {//树上启发式合并
    for (int i = head[begin];i != -1;i = edge[i].next) {
        int to = edge[i].to;
        if (to == son[begin]) continue;
        if(!mp[begin].count(to)) continue; 
        dfs2(to, 0);
    }
    if (son[begin]) {
        dfs2(son[begin], 1);
    }
    stacol[color[begin]]++;
    if (stacol[color[begin]] == 1) {
        diff++;
    }
    for(int i=head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        if(to == son[begin]) continue;
        if(!mp[begin].count(to)) continue;
        addSon(to);
    }
    if (!keep) {
        res[begin] = diff;
        dfs3(begin);
    }
    else {
        res[begin] = diff;
    }
}
void solve() {
    dfs1(1);
    dfs2(1, 0);
    for (int i = 1;i <= m;i++) {
        cout << res[qy[i]] << "\n";
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    color = vector<int>(n + 1, 0);
    edge = vector<Edge>((n + 1) * 2);
    res = stacol = sz = par = son = vector<int>(n + 1, 0);
    flag = vector<bool> (n + 1 , 0);
    // isMain = vector<bool>(n + 1, 0);
    head = vector<int>(n + 1, -1);
    for (int i = 1;i <= n;i++) {
        par[i] = i;
    }
    for (int i = 1;i < n;i++) {
        int u, v;
        cin >> u >> v;
        add(u , v);
        add(v , u);
    }
    for (int i = 1;i <= n;i++) {
        cin >> color[i];
    }
    cin >> m;
    qy = vector<int>(m + 1);
    for (int i = 1;i <= m;i++) {
        cin >> qy[i];
    }
    solve();
}
