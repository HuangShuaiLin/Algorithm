#include <bits/stdc++.h>
using ll = long long;
using namespace std;
void extend_gcd(ll a,ll m,ll &x,ll &y){
    if(m==0){
        x = 1;
        y = 0;
        return ;
    }
    ll mod = a%m;
    ll div = a/m;
    extend_gcd(m,mod,x,y);
    ll t = (x-div*y);
    x = y;  
    y = t;
}
int main() {
    int t;
    cin>>t;
    while(t--){
        ll a,m;
        cin>>a>>m;
        ll x = 0,y = 0;
        extend_gcd(a,m,x,y);
        x = (x+m)%m;
        cout<<x<<"\n";
    }
}
