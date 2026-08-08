#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MAX = 711000;
struct Edge{
    int to,next;
};
vector<Edge> edge;
vector<int> head;
int edd[MAX],timer[MAX],pass[MAX],fail[MAX],par[MAX];
int trie[MAX][27],listed[MAX][27];
int cnt = 0,indx = 0;
vector<bool> flag ;
vector<int> finally;
int tot = 0;
void add(int u,int v){
    edge[indx].to = v;
    edge[indx].next = head[u];
    head[u] = indx++;
}
void insert(string word){//插入自动机的字符串
    int root = 0;
    pass[root]++;
    for(char s : word){
        int val = s - 'a';
        if(!trie[root][val]){
            trie[root][val] = ++cnt;
        }
        root = trie[root][val];
        pass[root]++;
    }
    edd[root]++;
    finally[++tot] = root;
}
void buildAC(){//普通AC自动机的构建
    queue<int> pq;
    pq.push(0);
    while(!pq.empty()){
        int f = pq.front();
        pq.pop();
        if(flag[f]) continue;
        flag[f] = true;
        for(int i=0;i<26;i++){
            if(!flag[trie[f][i]]){
                int to = fail[f];
                while(to&&!trie[to][i]){to = fail[to];}
                if(!to) fail[trie[f][i]] = 0;
                else fail[trie[f][i]] = trie[to][i];  
                pq.push(trie[f][i]);
            }
        }
    }
}
bool check(string word){//检查字符串是否存在
    int root = 0;
    for(int i=0;i<word.size();i++){
        int val = word[i]-'a';
        if(!trie[root][val]||!pass[root]){
            return false;
        }
        root = trie[root][val];
    }
    return true;
}
void build(){//查表构建
    queue<int> pq;
    pq.push(0);
    while(!pq.empty()){
        int f = pq.front();
        pq.pop();
        if(flag[f]) continue;
        flag[f] = true;
        for(int i=0;i<26;i++){
            if(trie[f][i]){
                listed[f][i] = trie[f][i];
                pq.push(trie[f][i]);
            }else if(f!=0){
                listed[f][i] = listed[fail[f]][i];
            }
        }
        for(int i=0;i<26;i++){
            if(!trie[f][i]||!flag[trie[f][i]]) continue;
            if(f==0){
                fail[trie[f][i]] = 0;
            }else{
                fail[trie[f][i]] = listed[fail[f]][i];
            }
        }

    }
}
void work(string word){//对每一个输入字符串检查词频
    // if(!check) return ;
    int root = 0;
    for(int i=0;i<word.size();i++){
        int val = word[i] - 'a';
        if(!trie[root][val]){
            root = listed[fail[root]][val];
            timer[root]++;
        }else{
            root = trie[root][val];
            timer[root]++;
        }
    }
}
void dfs(int begin){//回溯词频
    for(int i = head[begin];i!=-1;i=edge[i].next){
        int to = edge[i].to;
        dfs(to);
        timer[begin] += timer[to];
    }
}
void solve(){
    int n;
    cin>>n;
    indx = cnt = 0;
    finally = vector<int> (n+1);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s);
    }
    flag = vector<bool> (cnt+1,0);
    // buildAC();
    build();
    head = vector<int> (cnt+1,-1);
    edge = vector<Edge>(cnt*2+1);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        work(s);    
    }
    for(int i=1;i<=cnt;i++){//建反图
        add(fail[i],i);
    }
    dfs(0);
    for(int i=1;i<=n;i++){
        cout<<timer[finally[i]]<<"\n";
    }
}
int main(){
    solve();    
}
