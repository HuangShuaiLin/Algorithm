#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const ll MAX = 200007;
struct Node{
    int data,tag = 0;
    int left = -1,right = -1;
};
vector<Node> tree(20*MAX);
int version[MAX];
int tot = 0;
ll a[MAX+7];

int createTree(int l,int r){
    int rt = ++tot;
    if(l==r){
        tree[rt].data = a[l];
        return rt;
    }
    int mid = (l+r)>>1;
    tree[rt].left = createTree(l,mid);
    tree[rt].right = createTree(mid+1,r);
    tree[rt].data = tree[tree[rt].left].data+tree[tree[rt].right].data;
    return rt;
}

int add(int l,int r,int dl,int dr,int data,int pre){//区间加永久标记化
    int rt = ++tot;
    tree[rt] = tree[pre];
    int sum = (min(dr,r)-min(l,dl)+1)*data;
    tree[rt].data += sum;
    if(l>=dl&&r<=dr){
        tree[rt].tag += data;
        return rt;
    }
    int mid = (l+r)>>1;
    if(dl<=mid){
        tree[rt].left = add(l,mid,dl,dr,data,tree[rt].left);
    }
    if(dr>mid){
        tree[rt].right = add(mid+1,r,dl,dr,data,tree[rt].right);
    }
    return rt;
}


int query(int l,int r,int dl,int dr,int tagSum,int pre){//区间查询永久标记化
    tagSum += tree[pre].tag;
    if(l>=dl&&r<=dr){
        return tree[pre].data+tagSum*(r-l+1);
    }
    int mid = (l+r)>>1,left = 0,right = 0;
    if(dl<=mid){
        left = query(l,mid,dl,dr,tagSum,tree[pre].left);
    }
    if(dr>mid){
        right = query(mid+1,r,dl,dr,tagSum,tree[pre].right);
    }
    return left + right;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    int op = 0;
    version[op++] = createTree(1,n);
    for(int i=1;i<=m;i++){
        int p,l,r,x,z;
        cin>>p;
        if(p==1){
            cin>>z>>l>>r>>x;
            version[op++] = add(1,n,l,r,x,version[z]);
        }
        else {
            cin>>z>>l>>r;
            cout<<query(1,n,l,r,0,version[z])<<"\n";
        }
    }
}

