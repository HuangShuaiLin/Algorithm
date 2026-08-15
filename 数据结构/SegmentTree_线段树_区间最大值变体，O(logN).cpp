#include <cstdio>
#include<iostream>
#include <memory>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
typedef long long ll ;
typedef __int128 ii;
struct dom {
    ii data, lazy = 0;
    ii sum=0;
};
void pushDown(vector<dom>& tree, int rt,int l,int r);
int queryMax(vector<dom>& tree, int rt, int ql, int qr, int l,
             int r);
void upDateDot(vector<dom>& tree, int data, int rt, int indx, int l,
               int r);
void upDateRange(vector<dom>& tree, int data, int rt, int ql, int qr, int l,
                 int r) ;
void createLinarTree(vector<dom>& tree, vector<ll>& data, int rt, int l,
                     int r);
void upDateRange(vector<dom>& tree, int data, int rt, int ql, int qr, int l,
                 int r) {//区间更新
    if (ql > r || qr < l) {
        return ;
    }//如果当前要更新区间不在该范围内则返回

    if (ql <= l && qr >= r) {
        tree[rt].data += data;
        tree[rt].lazy += data;
        tree[rt].sum += data*(r-l+1);
        return ;//如果说找到了该区间中的子区间直接更新后返回
    }

    pushDown(tree,
             rt,l,r); //如果需要访问当前节点，向子节点传递懒标记

    int mid = (r + l) / 2;

    upDateRange(tree, data, rt * 2, ql, qr, l, mid);//递归找修改区间

    upDateRange(tree, data, rt * 2 + 1, ql, qr, mid + 1, r);//递归找修改区间
    tree[rt].data = max(tree[rt * 2].data,
                        tree[rt * 2 +
                                1].data); //更新完后需要重新根据更新后的子节点更新自己的数据
}


void pushDown(vector<dom>& tree, int rt,int l,int r) { //传递懒标记
    if (tree[rt].lazy != 0) {
            int mid = (l+r)/2;

        tree[rt * 2].data +=tree[rt].lazy;//更新左节点数据为数据加上懒标记
        tree[rt * 2].lazy += tree[rt].lazy;//更新懒标记
        tree[rt*2].sum += tree[rt].lazy*(mid-l+1);

        tree[rt * 2 + 1].data += tree[rt].lazy;//更新右节点懒标记与数据
        tree[rt * 2 + 1].lazy += tree[rt].lazy;
        tree[rt*2+1].sum += tree[rt].lazy*(r-mid+1);

        tree[rt].lazy = 0;///清空当前节点懒标记
    }
}
void upDateDot(vector<dom>& tree, int data, int rt, int indx, int l,
               int r) { //更新单点数据
    if (indx == l&&l==r) {
        tree[rt].data += data;//找到叶子节点直接返回
        tree[rt].sum=tree[rt].data;
        return ;
    }
    if(indx<l||indx>r){
        return ;
    }

    pushDown(tree, rt,l,r);
    int mid = (l + r )/2;
    upDateDot(tree, data, rt * 2 + 1, indx, mid + 1,r); //如果要更改元素在这个区间里就递归向下一层搜索
    upDateDot(tree, data, rt * 2, indx, l, mid);

    tree[rt].data=max(tree[rt*2].data,tree[rt*2+1].data);
    tree[rt].sum=tree[rt*2].sum+tree[rt*2+1].sum;

}
int queryMax(vector<dom>& tree, int rt, int ql, int qr, int l,
             int r) { //查询区间最大值
    if (ql > r || qr < l) {
        return 0;//如果不在直接返回0
    }
    if (ql <= l && qr >= r) {
        return tree[rt].data;//如果整个要查寻区间就在范围内返回
    }
    pushDown(tree, rt,l,r);
    int mid = (l + r) / 2;
    int leftMax = queryMax(tree, rt * 2, ql, qr, l, mid);
    int rightMax = queryMax(tree, rt * 2 + 1, ql, qr, mid + 1, r);
    return max(leftMax, rightMax);
}

void  querySum(vector<dom> &tree,int rt,int ql,int qr,int l,int r,ll &sum){
    if(ql>r||qr<l){
        return ;
    }
    if(ql<=l&&qr>=r){
        sum+=tree[rt].sum;
        return;
    }
    pushDown(tree,rt,l,r);
    int mid = (l+r)/2;
    querySum(tree, 2*rt,  ql, qr,  l, mid,sum);
    querySum(tree,2*rt+1,ql,qr,mid+1,r,sum);
}


void createLinarTree(vector<dom>& tree, vector<ll>& data, int rt, int l,
                     int r) {//构建线段树
    if (l == r) {
        tree[rt].data = data[l];//抵达叶子节点直接赋值
        tree[rt].sum=data[l];
        return ;
    }
    int mid = (l + r) / 2;
    createLinarTree(tree, data, rt * 2, l, mid);//传递左孩子的rt*2，递归；
    createLinarTree(tree, data, rt * 2 + 1, mid + 1,
                    r); //传递有孩子的rt*2，递归；
    tree[rt].data = max(tree[rt * 2].data,
                        tree[rt * 2 +
                                1].data);//如果当前根节点的叶子节点的值都更新完了比较两个子节点的大小，挑最大值赋值给自己作为当前区间最大值
    tree[rt].sum=tree[rt*2].sum+tree[rt*2+1].sum;
}

int main() {
    int n,m;
    cin >> n>>m;
    vector<ll> data(n + 1);
    for (int i = 1; i <= n; i++) {
        cin>>data[i];
        }
    vector<dom> tree(n * 4 + 1);
    createLinarTree(tree, data, 1, 1, n);
    for(int i=0;i<m;i++){
        int op;
        cin>>op;
        if(op==1){
            ll x,y;
            cin>>x>>y;
            upDateDot(tree,y,1,x,1,n);
        }else{
            ll l,r;
            cin>>l>>r;
            ll sum=0;
            querySum(tree, 1, l,r, 1, n,sum);
            cout<<sum<<"\n";
        }
    }
}
