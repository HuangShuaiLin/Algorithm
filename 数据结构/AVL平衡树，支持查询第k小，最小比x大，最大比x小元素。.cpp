#include<bits/stdc++.h>
using namespace std;
struct Node{
    int key,height,left,right,count,size;
};
int n;
vector<Node> AVL;
int cnt = 1;
int head = 1;
int balance(int begin);
int insert(int begin,int x){
    if(AVL[begin].count == 0){
        int root = ++cnt;
        AVL[root].key = x;
        AVL[root].left = AVL[root].right = 0;
        AVL[root].count = AVL[root].size = 1;
        AVL[root].height = 1;
        return root;
    }
    if(AVL[begin].key == x){
        AVL[begin].count++;
        AVL[begin].size++;
        return begin;
    }
    if(AVL[begin].key > x){
        AVL[begin].left = insert(AVL[begin].left,x);
    }else {
        AVL[begin].right = insert(AVL[begin].right,x);
    }
    AVL[begin].size = AVL[AVL[begin].left].size + AVL[AVL[begin].right].size + AVL[begin].count;
    AVL[begin].height = max(AVL[AVL[begin].left].height + 1,AVL[AVL[begin].right].height + 1);
    return balance(begin);
}

void up(int begin){
    if(begin == 0) return ;
    AVL[begin].size = AVL[AVL[begin].left].size + AVL[AVL[begin].right].size + AVL[begin].count;
    AVL[begin].height = max(AVL[AVL[begin].left].height + 1,AVL[AVL[begin].right].height + 1);
}

int leftSpin(int begin){    
    int r = AVL[begin].right;
    int nr = AVL[r].left;
    AVL[begin].right = nr;
    AVL[r].left = begin;
    up(begin);
    up(r);
    return r;
}

int rightSpin(int begin){
    int l = AVL[begin].left;
    int nl = AVL[l].right;
    AVL[begin].left = nl;
    AVL[l].right = begin;
    up(begin);
    up(l);
    return l;
}

int find(int begin,int &root){
    if(AVL[begin].left != 0){
        AVL[begin].left = find(AVL[begin].left,root);
        AVL[begin].size = AVL[AVL[begin].left].size + AVL[AVL[begin].right].size + AVL[begin].count;
        AVL[begin].height = max(AVL[AVL[begin].left].height + 1,AVL[AVL[begin].right].height + 1); 
        return balance(begin);
    }else {
        root = begin;
        return AVL[begin].right;
    }
}
int update(int begin){
    if(AVL[begin].left == 0 && AVL[begin].right == 0){
        return 0;
    }else if(AVL[begin].left == 0){
        return AVL[begin].right;
    }else if(AVL[begin].right == 0){
        return AVL[begin].left;
    }else{
        int t = 0;
        int root = find(AVL[begin].right,t);
        AVL[t].right = AVL[begin].right = root;
        AVL[t].left = AVL[begin].left;
        AVL[t].height = max(AVL[AVL[t].right].height + 1,AVL[AVL[t].left].height + 1);
        AVL[t].size = AVL[AVL[t].left].size + AVL[AVL[t].right].size + AVL[t].count;
        return balance(t);
    }
}
int del(int begin,int x){//É¾³ý½Úµã
    if(AVL[begin].key == x){
        AVL[begin].count--;
        if(AVL[begin].count == 0){
            return update(begin);
        }else{
            AVL[begin].size--;
            return balance(begin);
        }
    }
    if(AVL[begin].key > x){
        AVL[begin].left = del(AVL[begin].left,x);
    }else {
        AVL[begin].right = del(AVL[begin].right,x);
    }
    AVL[begin].size = AVL[AVL[begin].left].size + AVL[AVL[begin].right].size + AVL[begin].count;
    AVL[begin].height = max(AVL[AVL[begin].right].height + 1,AVL[AVL[begin].left].height + 1);
    return balance(begin);
}

int balance(int begin){
    int leftHeight = AVL[AVL[begin].left].height;
    int rightHeight = AVL[AVL[begin].right].height;
    if(leftHeight - rightHeight > 1){
        if(AVL[AVL[AVL[begin].left].left].height >= AVL[AVL[AVL[begin].left].right].height){
            return rightSpin(begin);
        }else{
            AVL[begin].left = leftSpin(AVL[begin].left);
            return  rightSpin(begin);
        }
    }else if(rightHeight - leftHeight > 1){
        if(AVL[AVL[AVL[begin].right].right].height >= AVL[AVL[AVL[begin].right].left].height){
            return leftSpin(begin);
        }else{
            AVL[begin].right = rightSpin(AVL[begin].right);
            return leftSpin(begin);
        }
    }
    return begin;
}

int queryMin(int begin,int x){
    if(AVL[begin].count == 0){
        return 0;
    }
    if(AVL[begin].key < x){
        return AVL[begin].count + AVL[AVL[begin].left].size + queryMin(AVL[begin].right,x);
    }else{
        return queryMin(AVL[begin].left,x);   
    }
}

int queryRank(int begin,int rank){
    int rem = rank - AVL[AVL[begin].left].size;
    if(rem > 0 && AVL[begin].count >= rem){
        return AVL[begin].key;
    }
    if(rem - AVL[begin].count > 0){
        return queryRank(AVL[begin].right,rem - AVL[begin].count);
    }else{
        return queryRank(AVL[begin].left,rank);
    }
}

int qyf(int begin,int x){
    if(AVL[begin].count == 0){
        return INT_MIN;
    }
    if(AVL[begin].key >= x){
        return qyf(AVL[begin].left,x);
    }else{
        return max(qyf(AVL[begin].right,x),AVL[begin].key);
    }
}
int qyb(int begin,int x){
    if(AVL[begin].count == 0){
        return INT_MAX;
    }
    if(AVL[begin].key <= x){
        return qyb(AVL[begin].right,x);
    }else {
        return min(qyb(AVL[begin].left,x),AVL[begin].key);
    }
}

void solve(){
    AVL.assign(n + 7 ,{0,0,0,0,0,0});
    unordered_map<int,int> mp;
    for(int i=1;i<=n;i++){
        int op = 1,x;
        cin>>op>>x;
        if(op == 1){
            head = insert(head,x);
            mp[x]++;
        }else if(op == 2){
            if(!mp.count(x)) continue;
            mp[x]--;
            if(mp[x] == 0) mp.erase(x);
            head = del(head,x);
        }else if(op == 3){
            cout<<queryMin(head,x) + 1<<"\n";
        }else if(op == 4){
            cout<<queryRank(head,x)<<"\n";
        }else if(op == 5){
            cout<<qyf(head,x)<<"\n";
        }else{
            cout<<qyb(head,x)<<"\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    solve();
}
