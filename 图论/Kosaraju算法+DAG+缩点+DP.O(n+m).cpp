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
	int now;
};
struct node {
	int lazy = 0;
	int sum = 0;
};
int input[MAX];
vector <vector<int> > head;
void add(vector<Edge>& edge,vector<int> &head, int &indx,int u, int v) {
	edge[indx].to = v;
	edge[indx].now = u;
	edge[indx].next = head[u];
	head[u] = indx++;
}
void dfs1(int begin,vector<Edge> &edge,vector<int> &head,vector<bool> &vis,vector<int> &dfn) {
	if (vis[begin]) return;
	vis[begin] = true;
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (!vis[to]) {
			dfs1(to, edge,head ,vis, dfn);
		}
	}
	dfn.push_back(begin);
}
void dfs2(int begin,vector<int> &head,vector<bool> &vis,vector<Edge> &edge,vector<int> &grp) {
	if (vis[begin]) return;
	vis[begin] = true;
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int to = edge[i].to;
		if (!vis[to]) {
			grp[to] = grp[begin];
			dfs2(to, head,vis, edge,grp);
		}
	}
}
void dfs3(vector<int> &dp,vector<Edge> &edge,vector<int> &a,vector<int >&head,int begin){
	dp[begin] = a[begin];
	for (int i = head[begin];i != -1;i = edge[i].next) {
		int  to = edge[i].to;
		dfs3(dp, edge, a,head, to);
		dp[begin] = max(dp[begin], dp[to]);
	}
}
void solve(int n) {
	int m;
	int indx1 = 0;
	int indx2 = 0;
	cin >> m;
	vector<vector<Edge> > edge(2, vector<Edge>(m + 1));//反向图和正向图
	vector<vector<bool> > vis(2, vector<bool>(n + 1, 0));//标记防止无限递归
	vector<int> dfn;//第一次dfs的后续序列
	vector<int> grp(n + 1);//记录强连通分量
	vector<int> w(n + 1);//点权
	for (int i = 1;i <= n;i++) grp[i] = i;
	head = vector<vector<int> >(2, vector<int>(n + 1, -1));//head
	for (int i = 1;i <= n;i++) cin >> w[i];
	for (int i = 1;i <= m;i++) {
		int u, v;
		cin >> u >> v;
		add(edge[0], head[0], indx1,u, v);//加正向
		add(edge[1], head[1], indx2,v, u);//反向
	}
	//先对正向图求后续序列，在对反向图求强连通分量并不影响结果。
	for(int i=1;i<=n;i++) if(!vis[0][i])dfs1(i, edge[0], head[0], vis[0], dfn);
	//第一次找顺序
	bool flag = false;
	int link = 0;//连通分量个数
	vector<int> dp(n + 1,0), d(n + 1,INT_MIN);//连通分量的点权最大值，dp准备缩点后记录u可达v时最大的点权
	unordered_map<int, int> mp;
	for(int i=dfn.size()-1;i>=0;i--)
		if (!vis[1][dfn[i]] ) {
			dfs2(dfn[i], head[1], vis[1], edge[1],grp);//第二次记录联通量
			link++;
		}
	for (int i = 1;i <= n;i++) {
		d[grp[i]] = max(d[grp[i]],w[i]);//记录各联通分量最大点权
	}
	int indx3 = 0;
	vector<int> h(link + 1, -1);//缩点的链式前向星
	vector<Edge> e(link + 1);
	vector<int> a(m + 1);
	int t = 0;
	unordered_map<int, int> ref;
	for (int i = 1;i <= n;i++) {
		if (d[grp[i]]!=INT_MIN&&!ref.count(grp[i])) {
			a[++t] = d[grp[i]];
			ref[grp[i]] = t;
		}
	}
	int root = 0;
	for (int i = 0;i < m;i++) {
		if (grp[edge[0][i].to] != grp[edge[0][i].now]&&!mp.count(grp[edge[0][i].to])) {
			add(e, h, indx3, ref[grp[edge[0][i].now]], ref[grp[edge[0][i].to]]);//加缩点
			mp[grp[edge[0][i].to]] = 1;//用ref用hash表映射成我要的节点并记录入度找到根节点
			input[ref[grp[edge[0][i].to]]]++;
		}
	}
	for (int i = 1;i <= link;i++) {
		if (input[i] == 0) {
			root = i;
			break;
		}
	} 
	dfs3(dp,e,a,h,root);//缩点的dfs
	for (int i = 1;i <= n;i++) {
		//输出每个点到可达点的最大值
		cout << dp[grp[i]] << " ";
	}
	cout << "\n";
	if (link == 1) {
		cout << "Yes\n";
	}
	else cout << "No\n";	
	cout << "连通分量:" << link << "\n";

}
int main() {
	int t;
	cin >> t;
	while (t--) {
		memset(input, 0, sizeof(input));
		int n;
		cin >> n;
		solve(n);
	}
}
