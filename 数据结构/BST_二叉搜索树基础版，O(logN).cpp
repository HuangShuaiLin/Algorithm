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
#include<stack>
using namespace std;
typedef long long ll;
struct bstTree {
	int data;
	bstTree* lchild;
	bstTree* rchild;
};//二叉搜索树右孩子比根节点大，左孩子比根结点小 

void InsertNode(bstTree* &tree,int data) { 
	if (tree == NULL) {				//如果当前节点为空将该节点赋值意味着找到了该插入的位置 
		tree = new bstTree;
		tree->data = data;
		tree->lchild = NULL;
		tree->rchild = NULL;
	}
	else {
		if (data > tree->data) {//如果说要插入的data比当前节点值大说明要插入到他的右子树中并递归 
			InsertNode(tree->rchild,data);
		}
		else {
			InsertNode(tree->lchild, data);//如果说要插入的data比当前节点值小说明要插入到他的左子树并递归 
		}
	}
}

void printTree(bstTree* tree) {
	if (tree == NULL) {
		return;
	}
	printTree(tree->lchild);
	cout << tree->data<<" ";
	printTree(tree->rchild);
}

int main() {
	bstTree* T = NULL;
	vector<int> data(20);
	for (int i = 0;i < 20;i++) {
		data[i] = i;
	}
	for (int i = 0;i < 20;i++) {
		InsertNode(T, i);
	}
	printTree(T);//BST的用中序遍历会发现输出就是数组中从小到大的顺序 
}
