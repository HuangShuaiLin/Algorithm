#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
ll logN[60];
void preProcess(vector<ll> a){
    for(int i=1;i<=n;i++){
        ll cur = a[i];
        for(ll j=30;j>=0;j--){
            if((1ll<<j) & cur){
                if(logN[j]) cur ^= logN[j];
                else {
                    logN[j] = cur;
                    break;
                }
            }
        }
    }
}
void solve(){
    vector<ll> a(n+1);
    ll ans = 0;
    memset(logN,0,sizeof(logN));
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ans ^= a[i];
    }
    for(int i=1;i<=n;i++){
        a[i] = (a[i] & (~ ans));
    }
    ll t = 0;
    preProcess(a);
    for(ll i=30;i>=0;i--){
        if(logN[i] && ((logN[i] ^ t) & (1ll<<i))){
            t ^= logN[i];
        }
    }
    cout<<(t + (t ^ ans))<<"\n";
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n;
        solve();
    }
}
