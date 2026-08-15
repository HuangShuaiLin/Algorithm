#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include<map>
#include<unordered_map>
#include<queue>
#include<string.h>
#include<random>
#include<stack>
#include<list>
#include<deque>
#include<set>
#include<sstream>
#include<bitset>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll MAX = 5001;
const ll HashValue = 131;
const ll Hash = 1331;
ll HashKey[1000001];//编码1的Hash进制的n次方
ll hash_set[1000001];//编码2的Hash进制的n次方
ll positive_mod(ll a, ll b) {//对负数取模
    return (a % b + b) % b;
}
ll get(vector<ll> &prefix,int l,int r,ll HashKey[]) {//小心prefix[r]-会产生负数要注意
    return positive_mod((prefix[r] - prefix[l - 1] * HashKey[r - l + 1]%mod),mod);
}
void solve(int n,int m,int k) {
    vector <ll> prefix(n+1),pre(n+1);
    map<pair<ll,ll>, pair<int,int> > mp;
    string s;
    cin >> s;
    s = "0"+s;//base-1
    HashKey[0] = 1;
    prefix[0] = 0;
    hash_set[0] = 1;
    pre[0] = 0;
    for (int i = 1;i <= n;i++) {
        hash_set[i] = hash_set[i-1]*Hash%mod;
        HashKey[i] = HashKey[i - 1] * HashValue % mod;//记录HashValue的n次
        prefix[i] = (prefix[i - 1] * HashValue%mod +(s[i]-'0'+1)) % mod;//记录前缀和
        pre[i] = (pre[i-1]*Hash%mod+(s[i]-'0'+1))%mod;
    }

    for (int i = 1;i + m - 1<= n;i++) {
        ll y = get(pre,i,i+m-1,hash_set);//得到当前字串第二编码
        ll x = get(prefix, i, i + m - 1,HashKey);//得到第一编码
        if (!mp.count({x,y})) {//注意一个编码可能因为字串的长度大导致你的进制转换会有重合的数出现
            mp[{x,y}] = {i+m-1,1};//记录后缀i+m-1
        }
        else if(mp[{x,y}].first<i) {//因为前面被删掉了所以我的i不能取在前一个i+m-1
            mp[{x,y}].first = i+m-1;
            mp[{x,y}].second++;
        }
    }
    ll ans = 0;
    for (auto it : mp) {
        if (it.second.second == k) ans++;
    }
    cout << ans << "\n";
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n,m,k;
    cin >> n >> m >> k;
    solve(n,m,k);
    
}
