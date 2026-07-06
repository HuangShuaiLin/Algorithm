#include <bits/stdc++.h>
using namespace std;
using ii =  __int128;  //防溢出 
using ull = unsigned long long;
array<int,11> base = {2,3,5,7,11,13,17,19,23,31,37};//基准值测试作为a^(mod-1)=1的底数a 

ii mod_pow(ii a,ii b,ii mod){//快速幂 
    ii res = 1;
    while(b){
        if(b & 1) res = res*a%mod;
        a = a*a%mod;
        b>>=1;
    }
    return res;
}

bool isPrime(ull n){
    if(n<=1) return false;
    if(n<=3) return true;
    if(n%2==0) return false;//特判如果说n mod 2== 0直接说明不是素数 
    int cnt = 0;//记录我需要平方的次数 
    ii y = n-1;//记录费马小引理通过不断/2找到最初的奇数y 
    while(y%2==0){
        y/=2;
        cnt++;
    }
    ii mod = n;
    for(auto a : base){
        
        if(a%mod==0) continue;
        ii x = mod_pow(a,y,mod);//取刚开始a^y的值 
        if(x==1||x==mod-1) continue;//如果刚开始就是1/mod-1后续不用判断了 
        bool flag = false;
        for(int i=0;i<cnt;i++){
            x = x*x%mod;//不断平方 
            if(x==1|| x== mod-1) {//如果说出现1或mod-1则后续全为1不用判断break 
                flag = true;
                break;
            }
        }
        if(!flag) return false;//如果有一个基准值没过那么一定是合数 
    }
    return true;//通过所有基准值才算过关 
}

int main() {
    int t;
    cin>>t;
    while(t--){
        ull n ;
        cin>>n;
        if(isPrime(n)){
            cout<<"Yes\n";
        }else{
            cout<<"No\n";
        }
    }
}
