#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 20000007;
ll z[MAX],e[MAX];
int n;
void solve(){
    string s;
    string b;
    cin>>b>>s;
    ll r = 1,c = 1;
    z[0] = s.size();
    for(int i=1;i<s.size();i++){//自己和自己的每一个以i为下标开始的后缀与前缀比较看有多少重叠
        int len = i < r ? min(z[i-c],r-i) : 0; 
        while(i+len<s.size()&&s[i+len]==s[len]){
            len++;
        }
        if(i+len>r){
            r = i+len;
            c = i;
        }
        z[i] = len;
    }
    ll ans = 0;
    for(ll i=0;i<s.size();i++){
        // cout<<z[0]+1<<" "<<i+1<<"\n";
        ans = ans ^ ((i+1)*(z[i]+1));
        // cout<<z[i]<<" ";
    }
    r = 0,c = 0;
    ll res = 0;
    for(ll i=0;i<b.size();i++){//与其他字符串进行比较
        int len = i < r ? min(z[i-c],r-i) : 0;
        while(i+len<b.size()&&len<s.size()&&b[i+len]==s[len]){
            len++;
        }
        if(i+len>r){
            r = i+len;
            c = i;
        }
        e[i] = len;
    }
    for(int i=0;i<b.size();i++){
        res = res ^ ((i+1)*(e[i]+1));
        // cout<<p[i]<<" ";
    }
    // cout<<endl;
    cout<<ans<<"\n";
    cout<<res<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    // cin>>n;
    solve();
}
