#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node{
    int l,r;
    mutable ll v;
    Node(int _l,int _r,ll _v) : l(_l),r(_r),v(_v){};
    bool operator<(const Node& a)const{
        return l < a.l;
    }
};
ll n,m,s,v;
set<Node> ODT;
ll mod_pow(ll a,ll b,ll mod){
    ll res = 1;
    if(mod == 1) return 0;
    a %= mod;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
auto split(int pos){
    auto it = ODT.lower_bound(Node(pos,0,0));
    if(it != ODT.end() && it->l == pos) return it;
    it--;
    if(it != ODT.end() && it->r < pos) return ODT.end();
    ll val = it->v,l = it->l,r = it->r;
    ODT.erase(it);
    ODT.insert(Node(l,pos-1,val));
    return ODT.insert(Node(pos,r,val)).first;
}
void assign(int l,int r,ll x){
    auto ed = split(r + 1),bg = split(l);
    ODT.erase(bg,ed);
    ODT.insert(Node(l,r,x));
}
void add(int l,int r,ll x){
    auto ed = split(r + 1),bg = split(l);
    for(auto it = bg;it != ed;it++){it->v += x;}    
}
ll POW(int l,int r,ll x,ll y){
    auto ed = split(r + 1),bg = split(l);
    ll ans = 0;
    for(auto it = bg;it != ed ;it ++ ){
        ans = (ans + mod_pow(it->v,x,y) * (it->r - it->l + 1) % y) % y; 
    }
    return ans;
}
ll qyRank(int l,int r,int x){
    auto ed = split(r + 1),bg = split(l);
    vector<pair<ll,ll> > a;
    for(auto it = bg;it != ed;it++){
        a.emplace_back(it->v,it->r - it->l + 1);
    }
    ll rank = x;
    sort(a.begin(),a.end());
    for(int i=0;i<a.size();i++){
        ll sz = a[i].second,val = a[i].first;
        ll rem = rank - sz;
        if(rem <= 0){
            return val;
        }else{
            rank = rem;   
        }
    }
    return 0;
}
ll rnd() {
    ll ret = s;
    s = (s * 7 + 13) % 1000000007;
    return ret;
}
void solve(){
    vector<ll> a(n+1,0);
    for (int i = 1; i <= n; i++) {
        a[i] = (rnd() % v) + 1;
    }
    int cnt = 1;
    for(int i=2;i<=n;i++){
        if(a[i] == a[i - 1]) cnt++;
        else {
            ODT.insert(Node(i - cnt,i - 1,a[i - 1]));
            cnt = 1;
        }
    }
    // if(cnt != 1)
    ODT.insert(Node(n - cnt + 1, n ,a[n]));
    for (int i = 1; i <= m; i++) {
        int op = (rnd() % 4) + 1;
        int l = (rnd() % n) + 1;
        int r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        ll x, y;
        if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
        } else {
            x = (rnd() % v) + 1;
        }
        if(op == 1) add(l,r,x);
        if(op == 2) assign(l,r,x);
        if(op == 3)
        cout<<qyRank(l,r,x)<<'\n';
        if (op == 4) {
            y = (rnd() % v) + 1;
            cout<<POW(l,r,x,y)<<"\n";
        }
    }

}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>s>>v;
    solve();
}
