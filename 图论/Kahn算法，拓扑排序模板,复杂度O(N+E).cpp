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
int indx = 0;
vector<int> head;
int pos[MAX] = { 0 };
void add(vector<Edge> &edge,int u,int v,vector<int> &input) {
	edge[indx].to = v;
	edge[indx].now = u;
	edge[indx].next = head[u];
	head[u] = indx++;
	input[v]++;
}
void solve(int n,int m) {
	vector<int> input(n + 1,0);
	vector<Edge> edge(m + 1);
	head = vector<int>(n + 1, -1);
	for (int i = 0;i < m;i++) {
		int u, v;
		cin >> u >> v;
		add(edge, u, v,input);
	}
	int start = 0;
	for (int i = 1;i <= n;i++) if (input[i] == 0) {
		start = i;
		break;
	}
	bool flag = false;
	int cnt = 1;
	queue<int> pq;
	if (!start) {
		cout << "Not DAG\n";
		return;
	}
	pq.push(start);
	vector<int> order;
	vector<bool> vis(n + 1, 0);
	while (!pq.empty()) {
		int bg = pq.front();
		pq.pop();
		if (vis[bg]) {
			cout << "Not DAG\n";
			return;
		}
		vis[bg] = true;
		for (int i = head[bg];i != -1;i = edge[i].next) {
			int to = edge[i].to;
			if (--input[to] == 0) {
				pq.push(to);
				cnt++;
			}
		}
		order.push_back(bg);
	}
	if (cnt == n) {
		for (int i = 0;i < order.size();i++) {
			cout << order[i] << " ";
		}
	}
	else cout << "Not DAG\n";
}

int main() {
	int n, m;
	cin >> n >> m;
	solve(n, m);
}

