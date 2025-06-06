#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <set>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;

// 節點結構
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// BST 類別
class BST {
private:
    Node* root;

    // 遞迴插入節點
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    // 遞迴刪除節點
    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            // 找到要刪除的節點
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // 兩個子節點：尋找右子樹最小者（in-order successor）
            Node* succ = node->right;
            while (succ->left)
                succ = succ->left;
            node->key = succ->key;
            node->right = deleteNode(node->right, succ->key);
        }
        return node;
    }

    // 中序走訪遞迴
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    // 側向列印樹狀結構
    void printTree(Node* node, int space, int indent = 4) {
        if (!node) return;
        space += indent;
        printTree(node->right, space);
        for (int i = indent; i < space; i++) cout << " ";
        cout << node->key << "\n";
        printTree(node->left, space);
    }

public:
    BST() : root(nullptr) {}

    // 公開插入介面
    void insert(int key) {
        root = insert(root, key);
    }

    // 公開刪除介面
    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    // 執行中序走訪並列印
    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

    // 列印整棵樹
    void printTree() {
        printTree(root, 0);
    }
};

#endif // BST_HPP

