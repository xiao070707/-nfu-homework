#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include "heap.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));  // 設定亂數種子
    BST tree;
    set<int> inserted;   // 儲存已插入的鍵值

    const int maxNodes = 7;  // 節點數上限

    // 隨機插入 1~100 不重複整數，直到插入 7 個節點
    while (inserted.size() < maxNodes) {
        int val = rand() % 100 + 1;
        if (inserted.count(val) == 0) {
            inserted.insert(val);
            tree.insert(val);
        }
    }

    // 顯示原始 BST 結構
    cout << "Binary Search Tree (up to 3 levels):\n";
    tree.printTree();

    // 中序走訪結果
    cout << "\nIn-order traversal:\n";
    tree.inorderTraversal();

    // 提示使用者輸入欲刪除的鍵值
    int k;
    cout << "\nEnter a key to delete: ";
    cin >> k;

    // 計算刪除操作所需時間（微秒）
    auto start = high_resolution_clock::now();
    tree.deleteKey(k);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // 刪除後中序走訪
    cout << "\nIn-order traversal after deletion:\n";
    tree.inorderTraversal();

    // 顯示刪除所需時間
    cout << "Deletion time: " << duration.count() << " microseconds\n";

    // 刪除後 BST 結構
    cout << "\nBST structure after deletion:\n";
    tree.printTree();

    return 0;
}

