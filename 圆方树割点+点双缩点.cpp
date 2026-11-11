#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int to,next;
};
vector<int> SegTree;
vector<Edge> edge1,edge2;
vector<int> head,dfn,son,d,b,low,cur,sz,par,belong,depth;
unordered_map<int,int> mp;
vector<bool> flag;
int indx1 = 0,indx2 = 0,tot = 0,cnt = 0,num = 0,tt = 0;
vector<vector<int> > g;
void add(vector<Edge> &edge,vector<int> &head,int u,int v,int &indx){
    edge.emplace_back(v,head[u]);
    head[u] = indx++;
    edge.emplace_back(u,head[v]);
    head[v] = indx++;
}

void build(int l,int r,int rt){
    if(l == r){
        SegTree[rt] = b[mp[l]];
        return ;
    }
    int mid = (l + r) >> 1;
    build(l,mid,rt << 1);
    build(mid + 1,r,rt << 1 | 1);
    SegTree[rt] = SegTree[rt << 1] + SegTree[rt << 1 | 1];
} 

int query(int l,int r,int rt,int tl,int tr){
    if(tl <= l && tr >= r){
        return SegTree[rt];
    }
    int left = 0,right = 0;
    int mid = (l + r) >> 1;
    if(tl <= mid) left = query(l,mid,rt << 1,tl,tr);
    if(tr > mid) right = query(mid + 1,r,rt << 1 | 1,tl,tr);
    return left + right;
}

void Tarjan(int begin,stack<int> &st){
    dfn[begin] = low[begin] = ++tot;
    st.push(begin);
    for(int i = head[begin];i != - 1;i = edge1[i].next){
        int to = edge1[i].to;
        if(!dfn[to]){
            Tarjan(to,st);
            low[begin] = min(low[begin],low[to]);
            if(low[to] >= dfn[begin]){
                ++cnt;
                ++num;
                while(st.top() != to){
                    add(edge2,cur,num,st.top(),indx2);
                    st.pop();
                }
                st.pop();
                add(edge2,cur,num,begin,indx2);
                add(edge2,cur,num,to,indx2);
            }    
        }else{
            low[begin] = min(low[begin],dfn[to]);
        }
    }
}

void dfs(int begin){
    if(flag[begin]){
        return ;
    }
    flag[begin] = true;
    sz[begin] = 1;
    int ma = 0,indx = 0;
    for(int i = cur[begin];i != -1;i = edge2[i].next){
        int to = edge2[i].to;
        if(flag[to]) continue;
        par[to] = begin;
        depth[to] = depth[begin] + 1;
        dfs(to);
        sz[begin] += sz[to]; 
        if(ma < sz[to]){
            ma = sz[to];
            indx = to;
        }
    }
    son[begin] = indx;
}

void dfs2(int begin,int parent){
    if(son[parent] == begin) belong[begin] = belong[parent];
    d[begin] = ++tt;
    mp[tt] = begin;
    if(son[begin]) dfs2(son[begin],begin);
    for(int i = cur[begin];i!=-1;i = edge2[i].next){
        int to = edge2[i].to;
        if(son[begin] == to || par[begin] == to){
            continue;
        }
        dfs2(to,begin);
    }
}


int main(){
    int n,m,q;
    cin>>n>>m>>q;
    head.assign(2 * n + 7,-1);
    cur = head;
    flag.assign(n * 2 + 7,0);
    dfn.assign(n * 2 + 7,0);
    d = belong = sz = par = son = depth = low = dfn;
    for(int i = 1;i <= m;i ++){
        int u,v;
        cin>>u>>v;
        add(edge1,head,u,v,indx1);
    }
    for(int i = 1;i <= 2 * n + 1;i ++){
        belong[i] = par[i] = i;
    }
    num = n;
    stack<int> st;
    for(int i = 1;i <= n;i ++){
        if(!dfn[i] && head[i] != -1){ 
            Tarjan(i,st);        
            while(!st.empty()) st.pop();
        }else if(!dfn[i]){
            num++;
            add(edge2,cur,num,i,indx2);
        }
    }
    dfs(1);
    dfs2(1,1);

    vector<int> a(n * 2 + 1,0);
    b = a;
    map<int,int> mp;
    SegTree.assign(num * 4 + 7,0);
    for(int i = n + 1;i <= num;i ++){
        int ct = 0;
        for(int j = cur[i];j != -1;j = edge2[j].next){
            int to = edge2[j].to;
            // if(par[i] == to) continue;
            a[to]++;
            if(a[to] >= 2) b[to] = 1;
        }
    }
    build(1,num,1);
    for(int i = 1;i <= q;i ++){
        int s,t;
        cin>>s>>t;
        int ans = 0;
        if(s == t){
            cout<<ans<<"\n";
            continue;
        }
        int u = s,v = t;
        while(belong[t] != belong[s]){
            if(depth[belong[t]] < depth[belong[s]]) swap(s,t);
            ans += query(1,num,1,d[belong[t]],d[t]);
            t = par[belong[t]];
        }
        if(depth[t] < depth[s]) swap(t,s);
        ans += query(1,num,1,d[s],d[t]);
        ans -= b[u] + b[v];
        cout<<ans<<"\n";
    }
}