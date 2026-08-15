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
int pos[MAX] = { 0 };
//KMP算法
void solve() {
	int n, m;
	cin >> n >> m;
	string a, b;
	cin >> a >> b;
	a = " " + a;
	b = "#" + b;
	int j = 0;
	for (int i = 1;i < m;i++) {
		while (j > 0 && b[j+1] != b[i+1]) j = pos[j];//预处理模式串的next[]即前缀和后缀相等的情况，
		//保证后续与文本串每次i+1和j+1比较都能够回溯到正确位置
		if (b[j + 1] == b[i + 1]) {j++;}
		pos[i+1] = j;
	}
	for (int i = 1;i <= m;i++) {
		cout << pos[i] << " ";
	}
	int l = 0;
	bool flag = false;
	int ans = 0;
	for (int i = 0;i < a.size();i++) {
		while (l+1<b.size() && a[i + 1] != b[l + 1]) {
			l++;
		}
		if (l + 1 == b.size()) {
			flag = true;
			ans++;//允许字符串可以重叠的情况
			//字符串不可以重叠
			//l = 0;continue;   
			l = pos[l];
		}
	}
	if (flag) {
		cout << "Found!\n";
		cout << "Found " << ans << "substring\n";
	}
	else cout << "Not Found\n";

}
int main() {
	solve();
}
