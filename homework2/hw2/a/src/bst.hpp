#ifndef BST_HPP
#define BST_HPP

#include <queue>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    int height() {
        if (!root) return 0;
        std::queue<Node*> q;
        q.push(root);
        int h = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front(); q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            h++;
        }
        return h;
    }
};

#endif // BST_HPP

