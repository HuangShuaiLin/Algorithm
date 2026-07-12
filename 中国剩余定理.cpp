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
//void pre_mod() {
//	inv[1] = 1;
//	for (int i = 2;i < MAX;i++) {
//		inv[i] = -mod / i * inv[mod % i] % mod;
//	}
//}
int dist[MAX];
Edge edge[MAX];
int head[MAX];
int indx = 0;
int inv[MAX];

void add(int u, int v, int w) {
	edge[indx].now = u;
	edge[indx].to = v;
	edge[indx].weight = w;
	edge[indx].next = head[u];
	head[u] = indx++;
}
bool SPFA(int n, int m) {

}
template<class T>
T extend_gcd(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1, y = 0;return a;
	}
	T div = a / b;
	T d = extend_gcd(b, a % b, x, y);
	T m = x;
	x = y, y = m - div * y;
	return d;
}
template<class T>
T pos_mod(T a,T b) {
	return (a % b + b) % b;
}
void ChineseRemain() {
	int n;
	cin >> n;
	vector<ll> a(n + 1), m(n + 1);
	ll M = 1;
	ll ans = 0;
	for (int i = 1;i <= n;i++) M *= m[i];
	for (int i = 1;i <= n;i++) {
		ll t = M / m[i];
		ll x = 0, y = 0;
		extend_gcd(t,m[i], x, y);
		ans = (ans + pos_mod(x,M)*t * a[i]) % M;
	}
	cout << (ans+M)%M << "\n";
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		ChineseRemain();
	}
}

