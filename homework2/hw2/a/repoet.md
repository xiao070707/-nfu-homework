#  二元搜尋樹高度與 log₂(n) 比值分析

---

##  解題說明

本專案旨在透過隨機產生不重複整數，建立二元搜尋樹（Binary Search Tree, BST），並觀察在不同節點數量 `n` 下，BST 的實際高度與理論上最佳高度 `log₂(n)` 的比值，藉以分析 BST 在未平衡情況下的高度趨勢與效率影響。

---

##  解題策略

1. **隨機產生資料**：使用 `rand()` 函式產生不重複的亂數作為節點值。
2. **建構 BST**：透過遞迴方式插入節點建構 BST。
3. **計算高度**：使用層序走訪（BFS）計算整棵樹的高度。
4. **理論比較**：計算 `log₂(n)` 作為理論值，觀察與實際高度的比值。
5. **輸出結果**：將分析結果輸出至 CSV 檔並同步顯示於終端。

---

##  程式實作

程式以 C++ 撰寫，實作如下：

```cpp
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip> // 為了控制小數點輸出

using namespace std;

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
        queue<Node*> q;
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

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<int> n_values = { 100, 500, 1000, 2000, 3000, 4000,
                            5000, 6000, 7000, 8000, 9000, 10000 };

    ofstream fout("bst_height_log_ratio.csv");
    if (!fout) {
        cerr << "無法開啟檔案 bst_height_log_ratio.csv\n";
        return 1;
    }

    // 標題列
    fout << "n,Height,log2(n),Height/log2(n)\n";
    cout << left << setw(6) << "n"
        << setw(8) << "Height"
        << setw(10) << "log2(n)"
        << "Height/log2(n)\n";

    double totalRatio = 0;
    int count = 0;

    for (int n : n_values) {
        BST tree;
        vector<int> keys;

        while (keys.size() < static_cast<size_t>(n)) {
            int val = rand();
            if (find(keys.begin(), keys.end(), val) == keys.end()) {
                keys.push_back(val);
            }
        }

        for (int key : keys) {
            tree.insert(key);
        }

        int h = tree.height();
        double log2n = log2(n);
        double ratio = h / log2n;
        totalRatio += ratio;
        count++;

        // 寫入檔案
        fout << n << "," << h << "," << log2n << "," << ratio << "\n";

        // 同時顯示在終端
        cout << left << setw(6) << n
            << setw(8) << h
            << setw(10) << fixed << setprecision(4) << log2n
            << fixed << setprecision(4) << ratio << "\n";
    }

    fout.close();

    cout << "\n平均 Height/log2(n)："
        << fixed << setprecision(4) << (totalRatio / count) << endl;
    cout << "結果已輸出到 bst_height_log_ratio.csv\n";

    return 0;
}

```

---

##  效能分析

### 時間複雜度分析

| 操作 | 平均情況 | 最差情況 |
|------|-----------|------------|
| 插入節點 | O(log n) | O(n)（資料呈遞增或遞減） |
| 計算高度 | O(n) | O(n) |

### 空間複雜度

- 主要由 BST 結構與 `keys` 向量組成，皆為 O(n)。

---

##  測試與驗證

- 測試了多組節點數（100~10000），觀察高度與 `log₂(n)` 的比值。
- 輸出結果至 `bst_height_log_ratio.csv`，並於終端同步列印。
- 每次執行結果會略有變動，但比值範圍穩定。

---

##  測試案例

| 節點數 n | 實際高度 h | log₂(n) | h / log₂(n) |
|----------|------------|----------|--------------|
| 100      | 14         | 6.64     | 2.11         |
| 1000     | 24         | 9.97     | 2.41         |
| 5000     | 36         | 12.29    | 2.93         |
| 10000    | 39         | 13.28    | 2.94         |

> 註：數據為某次執行結果，實際會略有變動。

---
##  實測案例
![image](https://github.com/xiao070707/-nfu-homework/blob/main/img/Screenshot%202025-06-02%20180338.png)

### 透過Python生成圖片
![image](https://github.com/xiao070707/-nfu-homework/blob/main/img/Screenshot%202025-06-02%20180324.png)

程式以 Python 撰寫，實作如下：
```python
import matplotlib.pyplot as plt
import pandas as pd

# 讀取 CSV 檔
df = pd.read_csv('bst_height_log_ratio.csv')

# 繪圖
plt.figure(figsize=(10, 6))
plt.plot(df['n'], df['Height/log2(n)'], marker='o', color='blue', linestyle='-')
plt.title('Height / log₂(n) vs n for Random BST')
plt.xlabel('n (number of nodes)')
plt.ylabel('Height / log₂(n)')
plt.grid(True)
plt.xticks(df['n'])  # 每個 n 值都標示
plt.tight_layout()

# 顯示圖表
plt.show()
```
---

##  正確性驗證方法

- 使用 `find()` 確保亂數不重複，避免插入重複節點。
- 利用 BFS 層序遍歷精確計算 BST 高度。
- `log₂(n)` 使用 `cmath` 提供的 `log2()` 函式。
- 結果以檔案與終端雙重輸出，便於驗證與觀察。

---

##  結論

- BST 在隨機輸入下，平均高度約為 `log₂(n)` 的 2 ~ 3 倍，並不等於理想平衡樹。
- 若未使用平衡機制（如 AVL 或紅黑樹），BST 仍可能出現偏高問題。
- 此實驗強調在需要高效查找與插入場景下使用平衡樹的重要性。

---

##  申論及開發報告

本專案不僅展示了 BST 建樹與高度計算技巧，也讓我們理解隨機資料在實務上雖比最差情況理想，但仍會有高度偏離理論的現象。若應用於查詢密集的場景，建議採用平衡樹或雜湊結構進一步提升效率。

此外，本程式碼結構清晰，可進一步擴充分析更多 BST 屬性，例如節點總數、葉節點數或平均深度等。

