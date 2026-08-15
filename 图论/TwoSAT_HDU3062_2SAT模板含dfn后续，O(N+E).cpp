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
};
struct node {
	int lazy = 0;
	int sum = 0;
};
Edge edge[2][MAX];
int head[2][MAX];
bool vis[2][MAX];

void add(Edge edge[], int head[], int& indx, int u, int v) {
	edge[indx].to = v;
	edge[indx].next = head[u];
	head[u] = indx++;
}
void dfs1(Edge edge[], int head[], vector<int>& dfn, int begin, bool vis[]) {
	if (vis[begin]) return;
	vis[begin] = true;
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (!vis[to]) {
			dfs1(edge, head, dfn, to, vis);
		}
	}
	dfn.push_back(begin);
}
void dfs2(Edge edge[], int head[], bool vis[], vector<int> &grp, int begin) {
	if (vis[begin]) return;
	vis[begin] = true;
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (!vis[to]) {
			grp[to] = grp[begin];
			dfs2(edge, head, vis, grp, to);
		}
	}
}
void solve(int n,int m) {

	memset(vis, 0, sizeof(vis));
	memset(head, -1, sizeof(head));
	int indx1 = 0;
	int indx2 = 0;
	for (int i = 0;i < m;i++) {
		int a1, a2, c1, c2;
		cin >> a1 >> a2 >> c1 >> c2;
		if (c1 == 0) {
			if (c2 == 0) {
				add(edge[0],head[0],indx1, a1, a2 + n);
				add(edge[0],head[0],indx1, a2, a1 + n);
				add(edge[1], head[1], indx2, a1 + n, a2);
				add(edge[1], head[1], indx2, a2 + n, a1);
			}
			else {
				add(edge[0], head[0], indx1, a1, a2);
				add(edge[0],head[0],indx1, a2 + n, a1 + n);
				add(edge[1], head[1], indx2, a1 + n, a2+n);
				add(edge[1], head[1], indx2, a2, a1);
			}
		}
		else {
			if (c2 == 0) {
				add(edge[0], head[0], indx1,a1 + n, a2 + n);
				add(edge[0], head[0], indx1, a2, a1);
				add(edge[1], head[1], indx2, a2 + n, a1 + n);
				add(edge[1], head[1], indx2, a1, a2);
			}
			else {
				add(edge[0],head[0],indx1, a1 + n, a2);
				add(edge[0],head[0],indx1 , a2 + n, a1);
				add(edge[1], head[1], indx2, a2, a1+n);
				add(edge[1], head[1], indx2, a1, a2+n);
			}
		}
	}
	vector<int> dfn;
	for (int i = 0;i < 2*n;i++) {
		if (!vis[0][i]) {
			dfs1(edge[0], head[0], dfn, i, vis[0]);
		}
	}
	vector<int> grp(2*n + 1);
	for (int i = 0;i < 2 * n;i++) {grp[i] = i;}
	for (int i = 2*n-1;i >=0 ;i--) {
		if (!vis[1][dfn[i]]) {
			dfs2(edge[1], head[1], vis[1], grp, dfn[i]);
		}
	}
	bool flag = false;
	for (int i = 0;i < n;i++) {
		if (grp[i] == grp[i + n]) {
			flag = true;
			break;
		}
	}
	if (!flag) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	while(cin >> n >> m) solve(n,m);
}

