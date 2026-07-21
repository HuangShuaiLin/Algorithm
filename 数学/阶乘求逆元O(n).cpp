#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 200007;
const ll mod = 998244353;
ll inv[MAX+1],pos[MAX+1];
ll mod_pow(ll a,ll b){
	ll res = 1;
	while(b){
		if(b & 1) res = res*a%mod;
		a = a*a%mod;
		b>>=1;
	}
	return res;
}
void preProcess(){
	pos[1] = 1;
	pos[0] = 1;
	for(int i=2;i<MAX;i++){
		pos[i] = pos[i-1]*i%mod;
	}
	inv[MAX] = mod_pow(pos[MAX],mod-2);
	for(int i=MAX;i>=1;i--){
		inv[i-1] = inv[i]*(i)%mod;
	}
}
int main(){
	preProcess();	
} 
