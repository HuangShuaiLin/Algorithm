#include<bits/stdc++.h>
using ull = unsigned long long;
using ll = long long;
using namespace std;
const ll mod = 998244353;
const ll MAX = 6001;
using namespace std;
int n;

int lowbit(int x) {//二进制取最低位的1 
	return (x & (-1 * x));
}
int query(vector<int>& a,int right) {//范围查询 
	int r = right;
	int res = 0;
	while (r >= 1) {
		res += a[r];
		r = (r ^ lowbit(r));
	}
	return res;
}
void addPoint(vector<int>& a, int data, int low) {//单点更新 
	int l = low;
	while (l <= n) {
		a[l] += data;
		l += lowbit(l);
	}
}
void addRange(vector<int>& d, int l, int r, int data) {//范围修改d是差分数组 
	addPoint(d, data, l);
	addPoint(d, -1 * data, r + 1);
}
int queryPoint(vector<int>& d, int indx) { //通过差分实现单点查询
	return query(d,indx);
}
int queryRange(vector<int>& tree, int left, int right) {
	return (query(tree, right) - query(tree, left - 1));
}
int new_Prequery(vector<int> &new_d,vector<int> &d,int dx) {//用k*∑(d[i])-∑(i-1)*d[i]查询前缀和
	return (dx * queryPoint(d, dx) - queryPoint(new_d,dx));
}
void new_updateRange(vector<int>& new_d, vector<int>& d, int l, int r,int data) { //根据修改data来维护差分和，(i-1)*d[i]树状数组
	addRange(d,l,r,data);
	addPoint(new_d,(l-1)*data,l);
	addPoint(new_d,-r*data,r+1);
}

int main() {
	cin >> n;
	vector<int> a(n + 1), tree(n + 1, 0), d_tree(n + 1, 0),new_tree(n+1 , 0);
	for (int i = 1;i <= n;i++) {
		cin >> a[i];
	}
	new_tree[1] = 0;//(i-1)*d[i] 的差分信息，前缀和可以通过k*∑(d[i])-∑(i-1)*d[i];
	d_tree[1] = a[1];
	for (int i = 1;i <= n;i++) {
		tree[i] += a[i];
		ll t = 0;
		if (i >= 2) {
			d_tree[i] += a[i] - a[i - 1];
			t = (a[i] - a[i - 1]) * (i - 1);
			new_tree[i] += t;
		}
		int parent = i + lowbit(i);
		if (parent <= n) {
			d_tree[parent] += d_tree[i];
			tree[parent] += tree[i];
			new_tree[parent] += t;
		}
	}
}
