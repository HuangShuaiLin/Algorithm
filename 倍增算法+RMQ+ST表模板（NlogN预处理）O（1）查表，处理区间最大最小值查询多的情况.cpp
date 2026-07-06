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
bool prime[MAX];
void add(vector<Edge> &edge,int u,int v) {
	edge[indx].to = v;
	edge[indx].next = head[u];
	head[u] = indx++;
}

// ST——RMQ查找区间最大最小
//也可以变化成区间gcd，lcm 

ll query(ll l,ll r,vector<ull> &log2,vector<vector<ll> > &st) {
	return min(st[l][log2[r - l + 1]], st[r - (1 << log2[r - l + 1]) + 1][log2[r - l + 1]]);
}//查询区间的min 
void createLog2(vector<ull> &log2) {//预处理出2的64次方的值
	for (int i = 0;i <= MAX;i++) {
		ull x = i;
		ull t = 0;
		while ((1 << t) <= (x >> 1ULL)) t++;
		log2[i] = t;
	}
}
void createST(int n,vector<ll> &a,vector<vector<ll> > &st) {
	for (int i = 1;i <= n;i++) {
		st[i][0] = a[i];
	}
	for (int len = 1;(1 << len) <= n;len++) {
		for (int i = 1;i <= n;i++) {
			if (i + (1 << len)-1 > n) break;
			st[i][len] = min(st[i][len-1], st[i + (1 << (len - 1))][len-1]);
		}
	}
}
int main() {
	vector<ull> log2(MAX);
	createLog2(log2);
	int n;
	cin >> n;
	vector<ll> a(n + 1);
	for (int i = 1;i <= n;i++) {
		cin >> a[i];
	}
	vector<vector<ll> > st(n+1, vector<ll>(64, 0));
	createST(n, a, st);
	int q;
	cin >> q;
	for (int i = 0;i < q;i++) {
		int l, r;
		cin >> l >> r;
		ll ans = query(l, r, log2, st);
	}
}
