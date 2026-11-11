#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e9;
struct Node{
    int l,r;
    mutable ll w;
    Node(int _l,int _r,ll _w) : l(_l),r(_r),w(_w){}
    bool operator<(const Node& a) const{
        return l < a.l;
    }
};
set<Node> ODT;
unordered_map<int,int> mp;
auto split(int pos){
    auto it = ODT.lower_bound(Node(pos,0,0));
    if(it != ODT.end() && it->l == pos) return it;
    int l = it->l,r = it->r,w = it->w;
    --it;
    ODT.erase(it);
    ODT.insert(Node(l,pos - 1,w));
    return  ODT.insert(Node(pos,r,w)).first;
}
void assign(int l,int r,int x){
    auto right = split(r + 1),left = split(l);
    for(auto it = left;it != right;){
        mp[it->w] -= it->r - it->l + 1;
        if(mp[it->w] == 0) mp.erase(it->w);
        auto nxt = ++it;
        ODT.erase(--it);
        it = nxt; 
    }
    mp[x] += r - l + 1;
    ODT.insert(Node(l,r,x));
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ODT.insert(Node(0,1e5 + 2,0));
    mp[0] = INF;
    int q;
    cin>>q;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        assign(l,r,x);
        cout<<mp.size()<<"\n";
    }
}