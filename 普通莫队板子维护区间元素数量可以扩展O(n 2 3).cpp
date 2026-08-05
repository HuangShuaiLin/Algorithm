#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 1000000;
int n,m;
bool compare(const tuple<int,int,int,int> &p1,const tuple<int,int,int,int> &p2){//按照左端点块号顺序升序排序，按右端点升序
    auto [l,r,s,id1] = p1;
    auto [u,v,w,id2] = p2;
    if(s!=w){
        return s<w;
    }
    return r<v;
}
array<int,MAX> cnt = {0};
void solve(){
    vector<int> a(n+1);
    vector<int> b(n+1);
    unordered_map<int,int> mp;
    vector<tuple<int,int,int,int> > pq(m+1);//存查询区间与块编号
    for(int i=1;i<=n;i++){
        cin>>a[i];    
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        pq[i] = {u,v,0,i};
    }
    int len = sqrt(n);//将arr长度分为根号n的块
    for(int i=0;i*len<=n;i++){
        for(int j=len*i+1,cnt=0;cnt<len&&j<=n;j++,cnt++){
            d[j] = i+1;
        }
    }
    for(int i=1;i<=m;i++){
        auto &[l,r,s,w] = pq[i];
        s = d[l];
    }
    vector<bool> ans()
    sort(pq.begin()+1,pq.end(),compare);
    auto [left,right,s,id1] = pq[1];
    for(int i=left;i<=right;i++){//维护第一个区间
        cnt[a[i]]++;
    }

    for(int i=1;i<=m;i++){//开始滑动区间窗口
        auto [l,r,w,id2] = pq[i];
        while(left<l){
            cnt[a[left]]--;
            left++;
        }
        while(left>l){
            left--;
            cnt[a[left]]++;
        }
        while(right>r){
            cnt[a[right]]--;
            right--;
        }
        while(right<r){
            right++;
            cnt[a[right]]++;
        }
    }
}   

int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        solve();
    }
}
