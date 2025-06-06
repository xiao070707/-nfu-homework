# 41243254和41243226

## 作業二-2(b) BST 刪除操作示範與效能分析

---

## 解題說明

本題的目標是實現並展示 BST 的 **插入**、**刪除** 操作，以及 **中序走訪** 與 **樹狀結構輸出**。  
此外，還要利用 C++11 的 `std::chrono` 庫計算並顯示刪除某個節點所需的時間，以便了解 BST 刪除操作的效能。

---

## 解題策略

1. **節點結構（Node）設計**  
   每個節點包含整數鍵值 `key`，以及左右兩個子指標 `left`、`right`，以支援遞迴方式進行插入或刪除。

2. **BST 類別實作**  
   - **插入 (`insert`)**  
     使用遞迴方式：  
     - 若當前節點為空，建立並回傳新節點  
     - 否則根據鍵值大小決定插入到左子樹或右子樹  
   - **刪除 (`deleteNode`)**  
     依照 BST 刪除三種情況處理：  
     1. 無子節點：直接刪除並回傳 `nullptr`。  
     2. 單一子節點：用唯一子節點取代被刪除節點。  
     3. 兩個子節點：找出右子樹的最小節點（繼承者），將其鍵值搬到當前節點，然後刪除該繼承者原位置節點。  
   - **中序走訪 (`inorder`)**  
     遞迴走訪：先左子樹 → 印出節點鍵值 → 再右子樹。  
   - **樹狀結構輸出 (`printTree`)**  
     遞迴方式：先走訪右子樹、列印當前節點、再走訪左子樹，並透過 `space` 和 `indent` 參數製造縮排，以達到側向樹狀輸出效果。

3. **隨機鍵值產生**  
   - 使用 `rand() % 100 + 1` 產生 1～100 的亂數，並透過 `std::set<int>` 容器避免重複插入。  
   - 當 `set` 大小達到 7 時停止插入新節點。

4. **效能測量**  
   - 採用 `std::chrono::high_resolution_clock::now()` 在刪除前後各取一次時間點，並以 `duration_cast<microseconds>` 計算刪除操作耗時（微秒級）。

5. **使用者互動**  
   - 程式會在插入完成且顯示原始 BST 結構後，提示使用者輸入欲刪除的鍵值。  
   - 讀取後執行刪除，印出刪除後的中序走訪結果與 BST 結構，並顯示刪除耗時。

---

## 程式實作

以下完整貼出程式碼，以便對照與編譯執行：

```cpp
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
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

    // 遞迴插入
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        return node;
    }

    // 遞迴刪除
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
            // 兩個子節點：尋找右子樹最小者繼承
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
        cout << node->key << "\\n";
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

int main() {
    srand(time(0));      // 設定亂數種子
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
    cout << "Binary Search Tree (up to 3 levels):\\n";
    tree.printTree();

    // 中序走訪結果
    cout << "\\nIn-order traversal:\\n";
    tree.inorderTraversal();

    // 提示使用者輸入欲刪除的鍵值
    int k;
    cout << "\\nEnter a key to delete: ";
    cin >> k;

    // 計算刪除操作所需時間（微秒）
    auto start = high_resolution_clock::now();
    tree.deleteKey(k);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // 刪除後中序走訪
    cout << "\\nIn-order traversal after deletion:\\n";
    tree.inorderTraversal();

    // 顯示刪除耗時
    cout << "Deletion time: " << duration.count() << " microseconds\\n";

    // 刪除後 BST 結構
    cout << "\\nBST structure after deletion:\\n";
    tree.printTree();

    return 0;
}
```

---

## 效能分析

1. **插入操作**  
   - 平均時間複雜度：O(log n)  
   - 最差時間複雜度：O(n)（當輸入序列使 BST 退化為線性鏈狀）

2. **刪除操作**  
   - 平均時間複雜度：O(log n)  
   - 最差時間複雜度：O(n)（同理若 BST 退化為鏈狀）

3. **中序走訪**  
   - 時間複雜度：O(n)（必須遍歷所有節點）

4. **樹狀列印**  
   - 時間複雜度：O(n)（遞迴遍歷整棵樹並輸出）

5. **刪除耗時測量**  
   - 使用 `std::chrono::high_resolution_clock` 測量單次刪除操作的微秒級耗時，能粗略反映刪除效率。

---

## 測試與驗證

1. 程式會隨機產生 7 個節點並插入 BST，顯示原始樹結構與中序走訪結果，手動檢查節點插入是否正確。  
2. 使用者輸入欲刪除的鍵值（可能為葉節點、只有一個子節點或兩個子節點），執行刪除並檢查中序走訪與樹結構是否如預期。  
3. 顯示刪除操作的耗時，可多次嘗試刪除不同節點，比較不同情況下刪除時間差異。

---

## 測試案例

| 測試編號 | 初始節點集合                    | 欲刪除鍵值 | 預期行為                                                       |
|----------|---------------------------------|------------|----------------------------------------------------------------|
| T1       | `{50, 30, 70, 20, 40, 60, 80}` | `70`       | 節點 70 有左右子樹；刪除後由右子樹最小節點（80）繼承位置；中序結果變 `{20,30,40,50,60,80}` |
| T2       | `{15, 10, 20, 8, 12, 18, 25}`  | `8`        | 8 為葉節點；刪除後葉節點直接移除；中序結果變 `{10,12,15,18,20,25}`                     |
| T3       | `{35, 20, 50, 10, 30, 40, 60}` | `20`       | 20 有單一子節點（10 和 30）；刪除後由右子節點 30 繼承原位置；中序結果變 `{10,30,35,40,50,60}`   |
| T4       | `{5, 3, 7, 2, 4, 6, 8}`        | `100`      | 100 不在樹中；刪除操作不改變樹；中序結果仍為 `{2,3,4,5,6,7,8}`                         |

# 實際案例
![image](https://github.com/xiao070707/-nfu-homework/blob/main/img/Screenshot%202025-06-02%20193403.png)
| 測試編號 | 初始節點集合                    | 欲刪除鍵值 | 預期行為                                                       |
|----------|---------------------------------|------------|----------------------------------------------------------------|
| T5       | `{6, 19, 23, 32, 34, 45, 74}`  | `45`       | 45 只有右子節點 74；刪除後由 74 覆蓋 45 位置；中序結果變 `{6,19,23,32,34,74}`            |

---

## 正確性驗證方法

1. **中序走訪結果檢查**  
   - 刪除前後中序走訪輸出皆為「遞增排序」的序列。刪除後序列應少了刪除鍵值，其餘順序不變。  
2. **樹結構確認**  
   - 側向印出的 BST 結構應保持 BST 性質（左子 < 父，右子 > 父），且刪除後不得出現重複或遺失節點。  
3. **刪除耗時測量**  
   - 刪除耗時需為非負整數，並且在合理範圍內（微秒級），驗證 `std::chrono` 的使用方法無誤。  
4. **極限與例外情況**  
   - 嘗試刪除不存在的鍵值，程式不應出現崩潰或異常。  
   - 嘗試刪除整棵樹僅剩單一節點或空樹，應正確返回並印出空狀態。

---

## 結論

1. **功能驗證**  
   - 程式完整實作 BST 的插入、刪除、中序走訪與側向樹狀列印功能，並能正確測量刪除耗時。  
2. **效能觀察**  
   - 在隨機插入情況下，BST 結構較趨近平衡，刪除操作可近似 O(log n)。  
   - 若輸入資料呈現退化（例如有序或逆序插入），BST 將退化為鏈狀，刪除效率最差達 O(n)。  
3. **可視化效果**  
   - 側向列印方法能讓使用者直觀了解 BST 結構，便於教學與除錯。

---

## 申論及開發報告

1. **開發心得**  
   - BST 刪除操作需同時考量「是否有子節點」與「繼承者尋找」。實作過程中最容易出錯的，就是處理有兩個子節點那種情況，必須先找到右子樹最小者（in-order successor），再遞迴刪除它。  
   - 使用 `std::set` 產生不重複亂數鍵值，簡化鍵值重複檢查。若要進一步提高性能，可使用 Fisher–Yates shuffle 產生 1～100 的隨機排列。

2. **延伸思考**  
   - 若需保持 BST 始終平衡，可考慮使用自平衡樹（如 AVL Tree、紅黑樹），保證最差情況也為 O(log n)。  
   - 測量刪除耗時目前採用單次運算，較易受系統與硬體影響。可改為多次取平均，以減少誤差。  
   - 可加入更多操作，例如搜尋、修改節點、印出層級順序圖形等，或將此程式改寫成 GUI 介面，讓使用者更直觀觀察樹的動態變化。

---

