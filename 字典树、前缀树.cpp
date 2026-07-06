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
#include<bitset>
using ull = unsigned long long;
using ll = long long;
using namespace std;
const ll mod = 998244353;
const ll MAX = 6001;
using namespace std;
int n, m;
int cnt = 1;
void insert(vector<int> &pass,vector<int> &end,vector<vector<int> > &trie,string s) {
	int root = 1;//构造字典树 
	pass[root]++;
	for (char c : s) {
		int index = c - 'a';
		if (trie[root][index] == 0) {
			cnt++;
			trie[root][index] = cnt;
		}
		root = trie[root][index];
		pass[root]++;
	}
	end[root]++;
}
int search(string word,vector<vector<int> > &trie,vector<int> &pass,vector<int> &end) {
	int root = 1;//查询字典树有多个 
	for (char c : word) {
		int index = c - 'a';
		if (trie[root][index]==0) {
			return 0;
		}
		root = trie[root][index];
	}
	return end[root];
}
int prefixNumber(string prefix, vector<vector<int> >& trie, vector<int>& pass, vector<int>& end) {
	int root = 1;//查询以prefix为前缀有多少个
	for (char c : prefix) {
		int index = c - 'a';
		if (trie[root][index] == 0) {
			return 0;
		}
		root = trie[root][index];//不断的向下层查询 
	}
	return pass[root];
}
void deleteTrie(string word, vector<vector<int> >& trie, vector<int>& pass, vector<int>& end) {
	int root = 1;//删除 
	int fl = search(word,trie,pass,end);
	if (fl == 0) return;
	pass[root]--;
	for (char c : word) {
		int index = c - 'a';
		int next = trie[root][index];//发现pass已经为0说明没有复用了这个节点直接删除return剪枝 
		if (--pass[next] == 0) {
			trie[root][index] = 0;
			return;
		}
		root = next;
	}
	end[root]--;
}

int main() {
	int n, k;
	cin >> n >> k;
	vector<vector<int> > trie(MAX, vector<int>(27, 0));
	vector<int> pass(MAX,0), end(MAX,0);
	for (int i = 0;i < k;i++) {
		string s;
		cin >> s;
		
	}
}

