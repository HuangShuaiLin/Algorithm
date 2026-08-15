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

int main() {
	pre_mod();
}
