#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node{
    ll lazy = 0;
    int curl,curr;
    array<int,3> sum = {0};
};
vector<Node> tree;
vector<ll> a;

void pushDown(int l,int r,int rt){
    if(tree[rt].lazy){
        int t = tree[rt].lazy;
        tree[rt].lazy = 0;
        tree[rt*2].lazy = (tree[rt*2].lazy + t)%3;
        tree[rt*2+1].lazy = (tree[rt*2+1].lazy + t) %3;
        tree[rt*2].curr = (tree[rt*2].curr+t)%3;
        tree[rt*2+1].curr += t,tree[rt*2+1].curr%=3;
        tree[rt*2].curl += t,tree[rt*2].curl %= 3;
        tree[rt*2+1].curl += t,tree[rt*2+1].curl %= 3;
        array<int,3> col1 = {0},col2 = {0};
        for(int i=0;i<3;i++){
            int t1 = tree[rt*2].sum[i];
            int t2 = tree[rt*2+1].sum[i];
            col1[(i+t)%3] = t1;
            col2[(i+t)%3] = t2;
        }
        tree[rt*2].sum =  col1;
        tree[rt*2+1].sum = col2;
    }
}

void build(int l,int r,int rt){
    if(l == r){
        tree[rt].curl = a[l];
        tree[rt].curr = a[r];
        tree[rt].sum[a[l]]++;    
        return ;
    }    
    int mid = (l + r) >>1;
    build(l,mid,rt*2);
    build(mid+1,r,rt*2 + 1);
    for(int i=0;i<3;i++){
        tree[rt].sum[i] = tree[rt*2].sum[i] + tree[rt*2+1].sum[i];
    }
    tree[rt].curl = tree[rt*2].curl,tree[rt].curr = tree[rt*2+1].curr;
    if(tree[rt*2].curr == tree[rt*2+1].curl){
        tree[rt].sum[tree[rt*2].curr]--;
    }
}

void update(int l,int r,int rt,int tl,int tr){
    if(tl <= l && tr >= r){
        tree[rt].curr += 1,tree[rt].curr %= 3;
        tree[rt].curl += 1,tree[rt].curl %= 3;
        tree[rt].lazy += 1,tree[rt].lazy %= 3;
        array<int,3> col = {0};
        for(int i=0;i<3;i++){
            int t = tree[rt].sum[i];
            col[(i+1)%3] += t; 
        }
        tree[rt].sum = col;
        return ;
    }
    pushDown(l,r,rt);
    int mid = (l + r) >> 1;
    if(tl <= mid) update(l,mid,rt*2,tl,tr);
    if(tr > mid) update(mid+1,r,rt*2+1,tl,tr);
    tree[rt].curr = tree[rt*2 + 1].curr;
    tree[rt].curl = tree[rt * 2].curl;
    for(int i=0;i<3;i++){
        tree[rt].sum[i] = tree[rt*2].sum[i] + tree[rt*2+1].sum[i];
    }
    if(tree[rt*2].curr == tree[rt*2+1].curl){
        tree[rt].sum[tree[rt*2].curr]--;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    s = " " +s;
    a = vector<ll>(n+1,2e18);
    tree = vector<Node>(n*4+7);
    for(int i=1;i<=n;i++){
        if(s[i] == 'A') a[i] = 0;
        if(s[i] == 'B') a[i] = 1;
        if(s[i] == 'C') a[i] = 2;
    }
    build(1,n,1);
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){
            int l,r;
            cin>>l>>r;
            update(1,n,1,l,r);
        }else{
            cout<<tree[1].sum[0]<<"\n";
        }
    }
}
