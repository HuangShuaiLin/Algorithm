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
const ll MAX = 1000007;
using namespace std;
struct Edge {
	int to, next;
};
int n, m;
int indx = 0;
vector<int> head;
ull has[MAX];
array<int, MAX> log2N = { 0 };
bool prime[MAX];
void add(vector<Edge> &edge,int u,int v) {
	edge[indx].to = v;
	edge[indx].next = head[u];
	head[u] = indx++;
}

//ST ------LCA求树上两个点最近公共祖先
void compute() {
	for (int i = 0;i <= 1e6;i++) {
		int t = 0;
		int x = i;
		while ((1 << t) <= (x >> 1)) t++;
		log2N[i] = t;
	}
}
void dfs(int begin,int step,vector<int> &depth,vector<Edge>& edge,vector<int> & father) {
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		depth[to] = step + 1;
		dfs(to, step + 1, depth, edge,father);
		father[to] = begin;
	}
}
//预处理出来st表即从i跳1<<len步能够到达哪些点如果为0即那也到不了
void PreProcess(int n,vector<vector<int> > &st,vector<int> &father,vector<Edge>&edge,vector<int>&depth) {
	for (int i = 1;i <= n;i++) {
		st[i][0] = father[i];
	}
	for (int len = 1;(1<<len) <= n;len++) {
		for (int i = 1;i <= n;i++) {
			st[i][len] = st[st[i][len - 1]][len-1];
		}
	}
}
int queryLCA(vector<int> &depth,vector<int> &father,vector<vector<int> > &st,int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	for (ll i = log2N[depth[u]];i>=0;i--) {
		if (depth[u] - (1 << i) >= depth[v]) {
			u = st[u][i];
		}
	}
	if (u == v) return u;
	for (int i = log2N[depth[u]];i >= 0;i--) {
		if (st[u][i]&&st[u][i]!=st[v][i]) {
			u = st[u][i];
			v = st[v][i];
		}
	}
	return father[u];
}
int main() {
	compute();
	int n;
	cin >> n;
	vector<vector<int> > st(n+1,vector<int>(64,0));
	vector<int> father(n + 1);
	vector<int> depth(n + 1);
	vector<Edge> edge(n);
	for (int i = 1;i < n;i++) {
		int u, v;
		cin >> u >> v;
		add(edge, u, v);
	}
	dfs(1, 0, depth, edge,father);
	PreProcess(n,st,father,edge,depth);
	int q;
	cin >> q;
	for (int i = 1;i <= q;i++) {
		int u, v;
		cin >> u >> v;
		cout << queryLCA(depth,father,st,u,v);
	}
}
