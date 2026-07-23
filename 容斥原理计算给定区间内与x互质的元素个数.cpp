#include<bits/stdc++.h>
using namespace std;
using ll = long long;
bool prime[1000007];
void isPrime(){
	prime[0] = true;
	prime[1] = true;
	for(int i=2;i<=100000;i++){
		if(!prime[i]){
			for(int j=2;j*i<=100000;j++){
				prime[i*j] = true;
			}
		}
	}
}
int count(vector<int> &a,ll x){
	if(x<=0) return 0;
	int size = a.size();
	ll cnt = 0;
	for(int i=0;i<(1<<size);i++){
		ll t = 1;
		int bit = 0;
		for(int j=0;j<size;j++){
			if((1<<j) & i){
				bit++;
				t *= a[j];
			}
		}
		if(t & 1) cnt -= x/t;
		else cnt += x/t;
	}
	return cnt;
}

int main(){

	int n,x,y;
	cin>>n>>x>>y;
	vector<int> a;
	for(int i=2;i*i<=n;i++){
		if(!prime[i] && n%i==0){
			a.push_back(i);
			while(n%i==0){
				n/=i;
			}
		}
	}
	if(n!=1) a.push_back(n);
	int r = count(a,y);
	int l = count(a,x-1);
	cout<<r-l<<endl;
} 
