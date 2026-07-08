#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
vector<vector<ll> > power(vector<vector<ll>> mat,ll b,int k){
        vector<vector<ll>> mt(k,vector<ll>(k));
        vector<vector<ll>> ans(k,vector<ll>(k));
        mt=mat;
    vector<vector<ll>> E(k,vector<ll> (k));
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            if(i==j)
            E[i][j]=1;
        }
    }
    if(b<=0)
        return E;
    if(b==1)
        return mt;
    mt = power(mat,b/2,k);
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            ans[j][i]=0;
            for(int l=0;l<k;l++){
                    ans[j][i]=(ans[j][i]+(mt[j][l]*mt[l][i])%mod)%mod;
            }
        }
    }
    if(b%2==1){
       mt=ans;
        for(int i=0;i<k;i++){
            for(int j=0;j<k;j++){
                ans[j][i]=0;
                for(int l=0;l<k;l++){
                        ans[j][i]=(ans[j][i]+(mat[j][l]*mt[l][i])%mod)%mod;
                }
            }
        }
    }
    return ans;
}
int main(){
	
} 
