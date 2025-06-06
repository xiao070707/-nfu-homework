#ifndef BST_HPP
#define BST_HPP

#include <queue>

// 節點結構
struct Node {
    int key;       // 節點的值
    Node* left;    // 左子樹指標
    Node* right;   // 右子樹指標

    // 節點建構子，初始化 key 並將左右子指標設為 nullptr
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// 二元搜尋樹類別
class BST {
public:
    Node* root;    // 樹根節點

    BST() : root(nullptr) {}  // 建構子，初始化 root 為空

    // 遞迴插入節點
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);   // 遇到空節點，建立新節點並回傳

        if (key < node->key)
            node->left = insert(node->left, key);   // 小於目前節點，插入左子樹
        else if (key > node->key)
            node->right = insert(node->right, key); // 大於目前節點，插入右子樹

        return node;   // 回傳節點指標
    }

    // 對外介面：插入節點
    void insert(int key) {
        root = insert(root, key);
    }

    // 計算樹的高度（層數）
    int height() {
        if (!root) return 0;   // 空樹高度為0

        std::queue<Node*> q;
        q.push(root);
        int h = 0;   // 高度計數器

        // 層級遍歷 BFS，計算樹的高度
        while (!q.empty()) {
            int levelSize = q.size();  // 目前層的節點數
            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front(); q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            h++;   // 完成一層，深度加一
        }
        return h;
    }
};

#endif // BST_HPP
