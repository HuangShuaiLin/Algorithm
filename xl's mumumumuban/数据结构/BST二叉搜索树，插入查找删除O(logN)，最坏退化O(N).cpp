#include <bits/stdc++.h>
using namespace std;

/**
 * BST 二叉搜索树
 * 支持：插入、查找、删除、中序遍历(得到有序序列)
 * 注意：不平衡的 BST 可能退化为链表 O(n)，通常用平衡树替代
 * 时间复杂度: 平均 O(log n)，最坏 O(n)
 */

struct BSTreeNode {
    int val;
    BSTreeNode* left;
    BSTreeNode* right;
    BSTreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 插入
BSTreeNode* insert(BSTreeNode* root, int val) {
    if (!root) return new BSTreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    return root;
}

// 查找
BSTreeNode* find(BSTreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val)
        return find(root->left, val);
    else
        return find(root->right, val);
}

// 找最小值
BSTreeNode* findMin(BSTreeNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// 删除
BSTreeNode* erase(BSTreeNode* root, int val) {
    if (!root) return nullptr;
    if (val < root->val) {
        root->left = erase(root->left, val);
    } else if (val > root->val) {
        root->right = erase(root->right, val);
    } else {
        // 只有一个或没有子节点
        if (!root->left) {
            BSTreeNode* tmp = root->right;
            delete root;
            return tmp;
        } else if (!root->right) {
            BSTreeNode* tmp = root->left;
            delete root;
            return tmp;
        }
        // 两个子节点：用右子树最小值替换
        BSTreeNode* minNode = findMin(root->right);
        root->val = minNode->val;
        root->right = erase(root->right, minNode->val);
    }
    return root;
}

// 中序遍历 (有序输出)
void inorder(BSTreeNode* root, vector<int>& res) {
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

// =============================================
// 迭代版 BST 查找（避免递归开销）
// =============================================
BSTreeNode* findIter(BSTreeNode* root, int val) {
    while (root && root->val != val) {
        if (val < root->val)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

// =============================================
// 判断是否为合法 BST
// =============================================
bool isValidBST(BSTreeNode* root, long long minVal = -1e18,
                long long maxVal = 1e18) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValidBST(root->left, minVal, root->val) &&
           isValidBST(root->right, root->val, maxVal);
}
