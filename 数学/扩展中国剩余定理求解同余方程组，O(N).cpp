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
T pos_mod(T a, T b) {
	return (a % b + b) % b;
}
ll mod_pow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int inv[MAX];
void pre_mod() {
	inv[1] = 1;
	for (int i = 2;i < MAX;i++) {
		inv[i] = -mod / i * inv[mod % i] % mod;
	}
}
int dist[MAX];
Edge edge[MAX];
int head[MAX];
int indx = 0;


void add(int u, int v, int w) {
	edge[indx].now = u;
	edge[indx].to = v;
	edge[indx].weight = w;
	edge[indx].next = head[u];
	head[u] = indx++;
}
bool SPFA(int n, int m) {

}
//求同余方程组
ll extend_ChineseRemain(vector<ll> m,vector<ll> a,int n) {
	ll M = m[1], x = 0, y = 0;
	ll ans = a[1];
	for (int i = 2;i <= n;i++) {
		ll c = a[i]-ans;
		ll d = extend_gcd(M,m[i],x,y);//求gcd，顺便求系数x，y
		if (c % d) {
			return -1;//如果发现c不是gcd倍数说明无解
		}
		c /= d,m[i]/=d;//得到最小解，因为扩欧求出ax+by = gcd(a,b)的时候这个c可能已经两边同乘系数变大了
		x = pos_mod(x*c, m[i]);
		//为啥能这样因为我将ax+by=c中a，b中c/gcd的倍数提到了x，y里面使之成为新的变量，然后mod数也变了
		//将扩欧后的系数取最小正整数
		ans = (ans % M + x * M) % (M*m[i]);//将要求的特解x累加
		M *= m[i];//后面通解的系数变为i的lcm
	}
	return ans;
}
void solve() {
	int n;
	cin >> n;
	vector<ll> a(n + 1), m(n + 1);
	for (int i = 1;i <= n;i++) {
		cin >> m[i] >> a[i];
	}
	ll x =extend_ChineseRemain(m,a,n);
	cout << x << "\n";

}

int main() {
	int t;
	while (t--) {
		solve();
	}
}
