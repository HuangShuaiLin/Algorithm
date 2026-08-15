#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int to, next;
};
int indx = 0;
int head[510];
bool vis[510];
bool flag = false;
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
void add(vector<Edge>& edge, int u, int v) {
    edge[indx].next = head[u];
    edge[indx].to = v;
    head[u] = indx++;
}
bool dfs(int begin, vector<int>& par, vector<Edge>& edge) {

    for (int i = head[begin]; i != -1; i = edge[i].next) {
        int to = edge[i].to;
        if (!vis[to]) {
            vis[to] = true;
            if (par[to] == -1 || dfs(par[to], par, edge)) {
                par[to] = begin;
                return true;
            }
        }
    }

    return false;

}
int main() {
    int n;
    memset(head, -1, sizeof(head));
    cin >> n;
    vector<Edge> edge(n * n * 2 + 1);
    vector<int> par(n + 1, -1);
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int t = gcd(a[i], b[j]);
            if (t == 1) {
                add(edge, j, i);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        dfs(i, par, edge);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (par[i] != -1) cnt++;
    }
    if (cnt == n) cout << "Bob\n";
    else cout << "Alice\n";
}
// 64 位输出请用 printf("%lld")