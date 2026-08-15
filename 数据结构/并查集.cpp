#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll c[1000001];
ll find(ll a)
{
    if(c[a]!=a)
       c[a] = find(c[a]);
    return c[a];
}
int main()
{
    for(int i=0;i<1000001;i++)
        c[i]=i;
    ll n;
    scanf("%lld",&n);
    ll x=n;
    while(n--){
        ll q,a,b;
        scanf("%lld%lld%lld",&q,&a,&b);
        if(q==1)
        {
            ll RootA=a;
            ll RootB=b;
            while(RootA!=c[RootA])
                RootA=c[RootA];
            while(RootB!=c[RootB])
                RootB=c[RootB];
            if(RootB==RootA)
                continue;
            else{
                c[RootB]=RootA;
            }
        }
        else{
            if(a>b)
            {
                if(find(b)==find(a))
                {
                    cout<<"YES"<<"\n";
                }
                else cout<<"NO"<<"\n";
            }
            else {
                if(find(b)==find(a))
                {
                    cout<<"YES"<<"\n";
                }
                else cout<<"NO"<<"\n";
            }
        }
    }
    return 0;
}
