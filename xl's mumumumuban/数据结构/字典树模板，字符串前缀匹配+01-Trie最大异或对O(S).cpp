#include <bits/stdc++.h>
using namespace std;

/**
 * Trie 字典树
 * 支持插入字符串、查询字符串/前缀
 * son[节点编号][字符] = 子节点编号，根节点为0
 */
struct Trie {
    static const int ALPHABET = 26;
    vector<array<int, ALPHABET>> son;
    vector<int> cnt; // 以该节点结尾的字符串数
    vector<int> pass; // 经过该节点的字符串数

    Trie() {
        son.push_back({});
        cnt.push_back(0);
        pass.push_back(0);
    }

    // 插入字符串
    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!son[u][c]) {
                son[u][c] = son.size();
                son.push_back({});
                cnt.push_back(0);
                pass.push_back(0);
            }
            u = son[u][c];
            pass[u]++;
        }
        cnt[u]++;
    }

    // 查询字符串是否存在
    int find(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!son[u][c]) return 0;
            u = son[u][c];
        }
        return cnt[u];
    }

    // 查询前缀出现次数
    int prefix(const string& s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!son[u][c]) return 0;
            u = son[u][c];
        }
        return pass[u];
    }
};

/**
 * 01-Trie (二进制Trie)
 * 用于处理异或有关问题，如最大异或对
 * 最好统一位数为 MAXBIT（如 30 处理 10^9 以内的数）
 */
struct Trie01 {
    static const int MAXBIT = 30;
    vector<array<int, 2>> son;
    vector<int> cnt;

    Trie01() {
        son.push_back({0, 0});
        cnt.push_back(0);
    }

    void insert(int x) {
        int u = 0;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!son[u][bit]) {
                son[u][bit] = son.size();
                son.push_back({0, 0});
                cnt.push_back(0);
            }
            u = son[u][bit];
            cnt[u]++;
        }
    }

    // 查询与 x 异或的最大值
    int maxXor(int x) {
        int u = 0, res = 0;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (son[u][bit ^ 1]) {
                res |= (1 << i);
                u = son[u][bit ^ 1];
            } else {
                u = son[u][bit];
            }
        }
        return res;
    }

    // 查询与 x 异或的最小值
    int minXor(int x) {
        int u = 0, res = 0;
        for (int i = MAXBIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (son[u][bit]) {
                u = son[u][bit];
            } else {
                res |= (1 << i);
                u = son[u][bit ^ 1];
            }
        }
        return res;
    }
};
