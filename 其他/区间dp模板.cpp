#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int dp[510][510] = {0};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    s = " " + s;
    int ma = 0;
    vector<int> pre(n + 2, 0), pos(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') pre[i] = pre[i - 1] + 1;
        else pre[i] = pre[i - 1];
    }
    for (int i = n; i >= 1; i--) {
        if (s[i] == '1') pos[i] = pos[i + 1] + 1;
        else pos[i] = pos[i + 1];
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int right = l + len - 1;
            for (int i = l+1; i <= right; i++) {
                int pe = pre[i - 1] - pre[l - 1], po = pos[i] - pos[right + 1];
                if (abs(pe - po) >= x && abs(pe - po) <= y) {
                    int t = (dp[i][right]+dp[l][i-1]);
                    dp[l][right] = max(dp[l][right], t + 1);
                }
            }
        }
    }
    cout << dp[1][n]<< "\n";
}
