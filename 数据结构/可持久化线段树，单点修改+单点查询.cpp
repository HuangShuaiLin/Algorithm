#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 1100;
struct Node{
    int val,lazy = 0;
    int left = -1;
    int right = -1;
};
int tot = 0;//用于对每一个需要更改，创建一个新的节点下标
vector<Node> tree;//树
ll a[MAX]; //输入数据
int version[MAX];//记录根节点
int createTree(int l,int r){
    int rt = ++tot;
    if(l==r){
        tree[rt].val = a[l];
        return rt;
    }
    int mid = (l+r)>>1;
    tree[rt].left = createTree(l,mid);
    tree[rt].right = createTree(mid+1,r);
    tree[rt].val = max(tree[tree[rt].left].val,tree[tree[rt].right].val);
}

int update(int l,int r,int indx,int data,int pre){//单点修改
    int rt = ++tot;
    tree[rt].left = tree[pre].left;
    tree[rt].right = tree[pre].right;
    tree[rt].val = tree[pre].val;
    if(l==indx&&l==r){
        tree[rt].val = data;
        return rt;
    }
    int mid = (l+r)>>1;
    if(indx>=l&&indx<=mid)
    tree[rt].left = update(l,mid,indx,data,tree[pre].left);
    if(indx>=mid+1&&indx<=r)
    tree[rt].right = update(mid+1,r,indx,data,tree[pre].right);

    tree[rt].val = max(tree[tree[rt].left].val,tree[tree[rt].right].val);
    return rt;
}

int query(int l,int r,int rt,int indx){//单点查询
    if(l==r&&l==indx){
        return tree[rt].val;
    }
    int mid = (l+r)>>1;
    if(l<=indx&&indx<=mid){
      return query(l,mid,tree[rt].left,indx);
    }
    if(indx>=mid+1&&indx<=r){
       return query(mid+1,r,tree[rt].right,indx);
    }
}

int main() {
    ios:: sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    } 
    int cnt = 0;
    tree = vector<Node>(n*10+1);
    createTree(1,n);

    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){//输入1则对p版本对u位置进行更新为v
            int p,u,v;
            cin>>p>>u>>v;
            version[++cnt] = update(1,n,u,v,version[p]);
        }else if(op==2){//对特定版本进行单点查询
            int p,u;
            cin>>p>>u;
            cout<<"version "<<p<<":"<<query(1,n,version[p],u);
        }
    }
}
