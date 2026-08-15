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
const ll MAX = 200007;
using namespace std;
struct Edge {
	int to, next,weight;
	int now;
};
struct node {
	int lazy = 0;
	int sum = 0;
};
ll pre_sum[MAX];
ll pre_mod[MAX];
int dx[] = { 0,1 };
int dy[] = { 1,0 };
ll mod_pow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int dist[MAX];
Edge edge[MAX];
int head[MAX];
int indx = 0;
void add(int u, int v,int w) {
	edge[indx].now = u;
	edge[indx].to = v;
	edge[indx].weight = w;
	edge[indx].next = head[u];
	head[u] = indx++;
}
bool SPFA(int n,int m) {

}

int extend_gcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1, y = 0;return a;
	}
	int div = a / b;
	int d = extend_gcd(b, a % b, x, y);
	int m = x;
	x = y, y = m - div * y;
	return d;
}
void solve() {
	int a, b, x = 0, y = 0;
	cin >> a >> b;
	int d = extend_gcd(a,b,x,y);
	cout << d << " " << x << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}

