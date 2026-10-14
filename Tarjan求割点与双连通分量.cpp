#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int to,next;
};
vector<Edge> edge;
vector<bool> fl;
vector<int> head,dfn,low,belong,a;
int tot = 0,cnt = 0,indx = 0;
void add(int u,int v){
    edge.emplace_back(v,head[u]);
    head[u] = indx++;
    edge.emplace_back(u,head[v]);
    head[v] = indx++;
}

/*
    求割点  

*/
void tarjan(int begin,bool flag){
    dfn[begin] = low[begin] = ++tot;
    int son = 0;
    for(int i = head[begin];i != -1;i = edge[i].next){
        int to = edge[i].to;
        if(!dfn[to]){
            son++;
            tarjan(to,false);
            low[begin] = min(low[begin],low[to]);
            if(low[to] >= dfn[begin]){
                if(!flag || son >= 2){
                    fl[begin] = true;
                }
                // cout<<son<<endl;
            }
        }else{
            low[begin] = min(low[begin],dfn[to]);
        }
    }
}

map<int,vector<int> > mp;
/*
    求割点+点双连通分量
*/
void Tarjan(int begin,stack<int> &st,bool root){
    dfn[begin] = low[begin] = ++tot;
    int son = 0;
    st.push(begin);
    for(int i = head[begin];i != -1;i = edge[i].next){
        int to = edge[i].to;
        if(!dfn[to]){
            son++;
            Tarjan(to,st,false);
            low[begin] = min(low[begin],low[to]);
            if(low[to] >= dfn[begin]){
                if(!root || son >= 2){
                    fl[begin] = true;
                }
                ++cnt;//点双生成的条件就只是low[to] >= dfn[begin]
                while(st.top() != to){
                    mp[cnt].push_back(st.top());
                    st.pop();
                }
                mp[cnt].push_back(to);
                mp[cnt].push_back(begin);
                st.pop();        
            }
        }else{
            low[begin] = min(low[begin],dfn[to]);
        }
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    head.assign(n * 2 + 1,-1);
    dfn.assign(n * 2 + 1,0);
    belong = low = dfn;
    fl.assign(n + 1,0);
    for(int i = 1;i <= m;i ++){
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    // for(int i = 1;i <= n;i ++)
    //     if(!dfn[i])
    //     tarjan(i,true);
    // int cnt = 0;
    // for(int i = 1;i <= n;i ++){
    //     if(fl[i])cnt++;
    // }
    // cout<<cnt<<"\n";
    // for(int i = 1;i <= n;i ++){
    //     if(fl[i])
    //     cout<<i<<" ";
    // }
    // cout<<endl;
    stack<int> st;
    for(int i = 1;i <= n;i ++){
        if(!dfn[i] && head[i] != -1){
            Tarjan(i,st,true);
        }else if(!dfn[i]){
            mp[++cnt].push_back(i);
        }
    }
    cout<<mp.size()<<"\n";
    for(auto [val,num] : mp){
        cout<<num.size()<<" ";
        for(int i = 0;i < num.size();i ++){
            cout<<num[i]<<" ";
        }
        cout<<"\n";
    }
}