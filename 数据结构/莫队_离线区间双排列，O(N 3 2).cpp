#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
vector<int> a, d;
int cnt[210000];
bool compare(const tuple<int, int, int, int>& p1, const tuple<int, int, int , int>& p2) {
    auto [l, r, s,id1] = p1;
    auto [u, v, w,id2] = p2;
    if (s != w) {
        return s < w;
    }
    return r > v;
}

void solve() {
    vector<long long> pre(n+1,0);
    d = a = vector<int> (n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }
    vector<tuple<int, int, int,int> > pq(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, q;
        cin >> u >> v;
        pq[i] = {u, v, 0,i};
    }
    int len = sqrt(n);
    for (int i = 0; i * len < n; i++) {
        for (int j = i * len + 1, cnt = 1;  j <= n && cnt <= len; cnt++, j++) {
            d[j] = i + 1;
        }
    }
    for (int i = 1; i <= m; i++) {
        auto &[l, r, s,w] = pq[i];
        s = d[l];
    }
    sort(pq.begin() + 1, pq.end(), compare);
    vector<tuple<int ,int, int> > v(m + 1);
    for (int i = 1; i <= m; i++) {
        auto [l, r, s , w] = pq[i];
        v[i] = {l, r, w};
    }
    bool fl = false;
    auto [left, right,id1] = v[1];

    int good = 0;
    for (int i = left; i <= right; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) {
            good++;
        } else if (cnt[a[i]] == 3) {
            good--;
        }
    }
    vector<bool> ans(m + 1);
    if (good * 2 == (right - left + 1)) {
        ans[id1] = true;
    }
    for (int i = 2; i <= m; i++) {
        auto [l, r , id] = v[i];
        while (l > left) {
            cnt[a[left]]--;
            if (cnt[a[left]] == 2) {
                good++;
            } else if (cnt[a[left]] == 1) {
                good--;
            }
            left++;
        }
        while (l < left) {
            left--;
            cnt[a[left]]++;
            if (cnt[a[left]] == 2) {
                good++;
            } else if (cnt[a[left]] == 3) {
                good--;
            }
        }
        while (right > r) {
            cnt[a[right]]--;
            if (cnt[a[right]] == 2) {
                good++;
            } else if (cnt[a[right]] == 1) {
                good--;
            }
            right--;
        }
        while (right < r) {
            right++;
            cnt[a[right]]++;
            if (cnt[a[right]] == 2) {
                good++;
            } else if (cnt[a[right]] == 3) {
                good--;
            }
        } 
        if (right - left + 1 == 2 * good && pre[right] - pre[left-1]==((r-l+1)/2+1)*(long long)(r-l+1)/2) fl = true;
        else fl = false;
        ans[id] = fl;
    }
    for (int i = 1; i <= m; i++) {
        if (ans[i]) cout << "Yes\n";
        else cout << "No\n";
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    solve();
}
