#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 1100;
struct Node{
    int left = -1;
    int right = -1;
    int size = 0;
};
int tot = 0;//用于对每一个需要更改，创建一个新的节点下标
vector<Node> tree;//主席树
ll a[MAX]; //输入数据
ll b[MAX];
int sorted[MAX];
int version[MAX];//记录根节点
int createTree(int l,int r){
    int rt = ++tot;
    if(l==r){
        return rt;
    }
    int mid = (l+r)>>1;
    tree[rt].left = createTree(l,mid);
    tree[rt].right = createTree(mid+1,r);
    return rt;
}

int add(int l,int r,int pre,int indx){
    int rt = ++tot;
    tree[rt].left = tree[pre].left;
    tree[rt].right = tree[pre].right;
    tree[rt].size = tree[pre].size + 1; 
    if(l==r){
        return rt;
    }
    int mid = (l+r)>>1;
    if(indx>=l&&indx<=mid)
        tree[rt].left = add(l,mid,tree[rt].left,indx);
    if(indx>=mid+1&&indx<=r)
        tree[rt].right = add(mid+1,r,tree[rt].right,indx);    
    return rt;
}

int query(int l,int r,int k,int u,int v){
    if(l==r){
        return l;
    }
    int lsize = tree[tree[v].left].size - tree[tree[u].left].size;
    int mid = (l+r)>>1;
    if(k>lsize){
        return query(mid+1,r,k-lsize,tree[u].right,tree[v].right);
    }else if(k<=lsize){
        return query(l,mid,k,tree[u].left,tree[v].left);
    }
}

int main() {
    ios:: sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    map<int,int> mp;
    unordered_map<int,int> cast;
    for(int i=1;i<=n;i++){
        cin>>b[i];
        mp[b[i]]++;
    } 
    int s = 1;
    for(auto it : mp){
        cast[it.first] = s;
        sorted[s++] = it.first;
    }
    int cnt = 0;
    tree = vector<Node>(n*20+1);
    version[0] = createTree(1,n);
    for(int i=1;i<=n;i++){
        version[i] = add(1,n,version[i-1],cast[b[i]]);
    }
    for(int i=1;i<=m;i++){
        int rank,l,r;
        cin>>l>>r>>rank;
        cout<<sorted[query(1,n,rank,version[l-1],version[r])]<<"\n";
    }

}
