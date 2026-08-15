#include<bits/stdc++.h>
using namespace std;
using ii = __int128;
using ull = unsigned long long;
using ll = long long;
ll n;
mt19937_64 rands(chrono::steady_clock::now().time_since_epoch().count());
map<ull,ull> mp;
ii mod_pow(ll a,ll b,ll mod){
    ii res = 1;
    while(b){
        if(b & 1) res = res * a%mod;
        a = a*a %mod;
        b >>= 1;
    }
    return res;
}
ll base[] = {2,3,5,7,11,13,17,19,23,29,31,37};
bool isPrime(ll mod){
    if(mod==1||mod==0||mod==4) return false;
    if(mod==2||mod==3||mod==5) return true;
    for(auto val : base){
        if(val==mod) return true;
    } 
    ll t = mod;
    ll cnt = 0;
    while(t%2==0) t/=2,cnt++;
    for(auto val : base){
        if(mod%val==0) return false;
        ii y = mod_pow(val,mod-1,mod);
        if(y==1||y==mod-1) continue;
        bool fl = false;
        for(int i=0;i<cnt;i++){
            y = y*y%mod;
            if(y==1||y==mod-1) {
                fl = true;
                break;
            }
        }
        if(fl) continue;
        else return false;
    }
    return true;
}
ull ubs(ull a,ull b){
    return a>b?a-b:b-a;
}
ll pollard_rho(ll n){
    for(auto val : base){
        if(n%val==0) return val;
    }
    uniform_int_distribution<ull> dc(1, (n - 1));
    uniform_int_distribution<ull> dx(0, (n - 1));
    while(true){
        ull c = dc(rands);
        ull x = dx(rands);
        ull y = x;
        ull d = 1;
        while(d==1){
            x = (x*x+c)%n;
            y = (y*y+c)%n;
            y = (y*y+c)%n;
            d = gcd(ubs(x,y),n);
        }
        if(d!=n) return d;
    }
}

void select(ull a){
    if(a==1) return ;
    if(isPrime(a)){
        mp[a]++;
        return ;
    }
    ull d = pollard_rho(a);
    select(d);
    select(a/d);
}

void solve(){
    if(n==1){
        cout<<1<<" "<<1<<"\n";
    }
    select(n);
    for(auto [val,num] : mp){
        cout<<val<<" "<<num<<"\n";
    }
}


int main(){
    cin>>n;
    solve();
}
