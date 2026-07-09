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
#include<bitset>
using ull = unsigned long long;
using ll = long long;
using namespace std;
const ll mod = 998244353;
const ll MAX = 2000007;
using namespace std;
struct Edge {
	int to, next;
	int now;
};
struct node {
	int lazy = 0;
	int sum = 0;
};
Edge edge[MAX];
int head[MAX];
int indx = 0;
int h[MAX];
array<int, MAX> dfn = { 0 };
array<int, MAX> low = { 0 };
array<int, MAX> belong = { 0 };
// Tarjon算法求强连通分量
void add(int u, int v) {
	edge[indx].now = u;
	edge[indx].to = v;
	edge[indx].next = head[u];
	head[u] = indx++;
}
int cnt = 0;
void dfs(int begin,stack<int> &st) {
	if (dfn[begin]) return;
	dfn[begin] = begin;//先给dfs序
	low[begin] = begin;//给定在其子树中的一条回路中能到的最小dfn序号点
	st.push(begin);//进栈
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (belong[to]) continue;
		if (dfn[to]) {
			low[begin] = min(low[begin], dfn[to]);
		}
		else {
			dfs(to,st);
			low[begin] = min(low[begin], low[to]);
		}
	}
	if (low[begin] == dfn[begin]) {//如果dfs序和low相等
		//则构成强连通分量，一直弹栈知道弹出自己
		int t = st.top();
		while (t != begin) {
			belong[t] = cnt;
			st.pop();
			t = st.top();
		}
		belong[begin] = cnt;
		st.pop();
		cnt++;//给每个强连通分量发号子
	}
}
void add(vector<Edge>& edge,int &indx ,int u, int v) {//加缩点的边
	edge[indx].next = h[u];
	edge[indx].to = v;
	h[u] = indx++;
}
void solve(int n,int m) {
	memset(head, -1, sizeof(head));
	memset(h, -1, sizeof(h));
	for (int i = 1;i <= m;i++) {
		int u, v;
		cin >> u >> v;
		add(u, v);
	}
	stack<int> st;
	for(int i=1;i<=n;i++)
	dfs(i,st);
	int ct = 0;
	unordered_map<int, int> mp;
	map<pair<int,int>,int> mark;
	for (int i = 1;i <= n;i++) {
		if (!mp.count(belong[i])) {
			mp[belong[i]]++;
			ct++;
		}
	}
	if (ct == 1)
		cout << "DAG\n";
	else cout << "Not DAG\n";
	
	cout << ct << "\n";
	vector<Edge> e(ct * 2);
	int indx = 0;
	for (int i = 0;i < m;i++) {//缩点建图
		int u = belong[edge[i].now];
		int v = belong[edge[i].to];
		if (mark[{u,v}]) continue;
		add(e,indx,u,v);
		mark[{u,v}]++;
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	solve(n, m);
}

