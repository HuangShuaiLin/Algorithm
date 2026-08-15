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
struct node {
	int lazy = 0;
	int sum = 0;
};
int n, m;
int indx = 0;
vector<int> head;
ull has[MAX];
array<int, MAX> log2N = { 0 };
bool prime[MAX];
void add(vector<Edge>& edge, int u, int v) {
	edge[indx].to = v;
	edge[indx].next = head[u];
	head[u] = indx++;
}
// 树链刨分---求LCA
vector<int> dfn(MAX), order(MAX);
int cnt = 0;
//预处理深度，重儿子，子树大小，每个点的父节点
void dfs(int begin, int par, vector<Edge>& edge, vector<int>& son, vector<int>& depth, vector<int>& size, vector<int>& f) {
	size[begin] = 1;
	int maxSon = 0;
	int maxIndex = 0;
	if (begin == 1) {
		depth[begin] = 0;
		f[begin] = 1;
	}
	else {
		depth[begin] = depth[par] + 1;
		f[begin] = par;
	}
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (to != par) {
			dfs(to, begin, edge, son, depth, size, f);
			size[begin] += size[to];
			if (size[to] > maxSon) {
				maxSon = size[to];
				maxIndex = to;
			}
		}
	}
	son[begin] = maxIndex;
}
void mergeTop(vector<int>& a, vector<int>& top, vector<int>& son, vector<Edge>& edge, int begin, int par) {//将重链上的所有点的top改为顶点方便查询往上跳
	top[begin] = top[par];
	//修改top为端点
	dfn[++cnt] = a[begin];//整理链顺序
	order[begin] = cnt;
	//如果还有重儿子向下递归
	if (son[begin]) mergeTop(a, top, son, edge, son[begin], begin);
	for (int i = head[begin]; i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (par != to && son[begin] != to)//没有重儿子后去轻儿子那里，将轻儿子作为新的重链顶点进行标记
			mergeTop(a, top, son, edge, to, begin);
	}
}
int queryLCA(int u, int v, vector<int>& f, vector<int>& depth, vector<int>& top) {//查询LCA
	while (depth[top[u]] != depth[top[v]]) {
		if (depth[top[u]] < depth[top[v]]) swap(u, v);//总是让top[u]是深度更深的那个
		u = f[top[u]];//跳到重链顶点的父节点
	}
	return depth[u] < depth[v] ? u : v;//返回深度更浅的同链节点
}
void pushDown(int rt, int l, int r, vector<node>& tree) {
	if (tree[rt].lazy != 0) {
		int mid = (l + r) / 2;
		int t = tree[rt].lazy;
		tree[rt].lazy = 0;
		tree[rt * 2].lazy += t;
		tree[rt * 2].sum += (mid - l + 1) * t;
		tree[rt * 2 + 1].lazy += t;
		tree[rt * 2 + 1].sum += (r - mid) * t;
	}
}
void addRange(vector<node>& tree, int data, int l, int r, int rt, int il, int ir) {
	if (il > r || ir < l) {
		return;
	}
	if (il <= l && ir >= r) {
		tree[rt].sum += (r - l + 1) * data;
		tree[rt].lazy += data;
		return;
	}
	pushDown(rt, l, r, tree);
	int mid = (l + r) / 2;
	addRange(tree, data, l, mid, rt * 2, il, ir);
	addRange(tree, data, mid + 1, r, rt * 2 + 1, il, ir);
	tree[rt].sum = tree[rt * 2].sum + tree[rt * 2 + 1].sum;
}
int query(vector<node>& tree, int l, int r, int rt, int il, int ir) {
	if (il > r || ir < l) {
		return 0;
	}
	if (il <= l && ir >= r) {
		return tree[rt].sum;
	}
	pushDown(rt, l, r, tree);
	int mid = (l + r) / 2;
	int left = query(tree, l, mid, rt * 2, il, ir);
	int right = query(tree, mid + 1, r, rt * 2 + 1, il, ir);
	return left + right;
}
void createTree(vector<int>& a, vector<node>& tree, int l, int r, int rt) {
	if (l == r) {
		tree[rt].sum = a[l];
		return;
	}
	int mid = (r + l) / 2;
	createTree(a, tree, l, mid, rt * 2);
	createTree(a, tree, mid + 1, r, rt * 2 + 1);
	tree[rt].sum = tree[rt * 2].sum + tree[rt * 2 + 1].sum;
}
//路径更改查询本质是将几条链拼起来操作
//对路径点权和的更改操作
void addChain(vector<int>& f, vector<int>& top, vector<node>& tree, vector<int>& depth, int data, int u, int v) {
	while (top[u] != top[v]) {
		//把u作为深度更深的点
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
		addRange(tree, data, 1, n, 1, order[top[u]], order[u]);
		u = f[top[u]];//top[u]在dfn序中一定是更靠前的只需要把u跳到的地方的到顶点的值修改即可
	}
	addRange(tree, data, 1, n, 1, min(order[u], order[v]), max(order[u], order[v]));
	//最后在同一链上时进行修改
}
//对路径点权和的查询
int queryChain(vector<int>& f, vector<int>& top, vector<node>& tree, vector<int>& depth, int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
		res += query(tree, 1, n, 1, order[top[u]], order[u]);
		u = f[top[u]];//不同链上累加端点到u的权值
	}
	//在同一链上时查询
	res += query(tree, 1, n, 1, min(order[u], order[v]), max(order[u], order[v]));
	return res;
}
int main() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	vector<int> son(n + 1, 0);//重儿子
	vector<int> depth(n + 1, 0);//节点深度
	vector<int> size(n + 1, 0);//节点的子树大小
	vector<int> top(n + 1, 0);//重链的顶点
	for (int i = 1;i <= n;i++) {
		cin >> a[i];//每个节点的点权
	}
	for (int i = 1;i <= n;i++) top[i] = i;
	vector<int> f(n + 1, 0);//父节点
	vector<Edge> edge(n * 2);//边
	head = vector<int>(n + 1, -1);
	vector<node> tree(n * 4 + 1);
	for (int i = 1;i < n;i++) {
		int u, v;
		cin >> u >> v;
		add(edge, u, v);
		add(edge, v, u);
	}
	dfs(1, 0, edge, son, depth, size, f);
	mergeTop(a, top, son, edge, 1, 1);
	createTree(dfn, tree, 1, n, 1);
	int q;
	cin >> q;
	//查询u与v的LCA节点
	for (int i = 1;i <= q;i++) {
		int u, v;
		cin >> u >> v;
		cout << queryLCA(u, v, f, depth, top);
	}
	int k;
	cin >> k;
	while (k--) {
		int op;
		cin >> op;
		if (op == 1) {//x到y的路径上的每个节点点权加z
			int x, y, z;
			cin >> x >> y >> z;
			addChain(f, top, tree, depth, z, x, y);
		}
		else if (op == 2) {//x子树每个节点的点权加上z
			int x, z;
			cin >> x >> z;
			int len = size[x];
			int bg = order[x];
			addRange(tree, z, 1, n, 1, bg, bg + len - 1);
		}
		else if (op == 3) {//查询x到y路径上每个点的点权之和
			int x, y;
			cin >> x >> y;
			cout << queryChain(f, top, tree, depth, x, y)<<"\n";
		}
		else if (op == 4) {//查询x子树内每个点权之和
			int x;
			cin >> x;
			int len = size[x];
			int bg = order[x];
			cout << query(tree, 1, n, 1, bg, bg + len - 1)<<"\n";
		}
	}
