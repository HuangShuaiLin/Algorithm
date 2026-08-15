#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 8000;
int n;
ll getBit(ll a){//返回低位1
    return a & (-a);
}
void build(vector<int> &tree,vector<int> &a){//建树
    for(int i=1;i<=n;i++){
        tree[i] += a[i];
        int bit = getBit(i);
        if(bit+i<=n){
            tree[bit] += tree[i];
        }
    }
}
void update(vector<int> &tree,int data,int rank){//动态修改段中数字出现频率
    while(rank<=n){
        tree[rank] += data;
        int bit = getBit(rank);
        rank += bit;
    }
}
int query(vector<int> &tree,int rank){//查询区间第k小
    int step = 0;
    while((1<<step)<=(rank>>1)) step++;
    int now = 0;
    for(;step;step--){
        int nt = (1<<step) + now;
        if(nt<=n&&tree[nt]<rank){
            rank -= tree[nt];
            now = nt;
        }
    }
    return now+1;
}

void solve(){
    vector<int> a(n+1),c,tree(n+1,0);
    map<int,int> mp,cast,rk;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    int cnt = 0;
    c = vector<int> (mp.size()+1,0);
    for(auto [val,time] : mp){//去重，离散化
        c[++cnt] = time;
        cast[cnt] = val;
        rk[val] = cnt;
    }
    build(tree,c);
    int q;
    cin>>q;
    for(int i=1;i<=q;i++){
        int op;
        cin>>op;
        if(op==1){//加新元素
            int u;
            cin>>u;
            update(tree,1,rk[u]);
        }
        else{//查询当前第k名
            int rank;
            cin>>rank;
            cout<<query(tree,rank);
        }
    }
}
int main(){
    cin>>n;
    solve();
}
