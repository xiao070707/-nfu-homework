# 41243254和41243226

## 作業二-1 堆積結構（MinHeap 和 MaxHeap）

## 解題說明

本題目旨在實作最小堆（MinHeap）與最大堆（MaxHeap）的資料結構，並藉由抽象類別設計統一介面，完成插入、刪除、查詢頂端元素、陣列輸出、以及以樹狀結構印出堆的功能。使用者將輸入一串整數，程式需同時建立對應的 MinHeap 與 MaxHeap 並印出內容。

### 解題策略
1. **抽象設計**：定義 MinPQ 和 MaxPQ 抽象類別，提供基本操作介面。

2. **堆實作**：分別實作 MinHeap 和 MaxHeap 類別，並繼承對應的抽象類別。

3. **核心操作**：
  + 插入（Push）：新節點從末端加入並向上調整（heapify up）。
  + 移除（Pop）：將根節點刪除，用最後一個節點取代後向下調整（heapify down）。
  + 查詢頂端元素（Top）。
    
4. **輔助操作**：
  + 印出陣列內容。
  + 遞迴方式印出樹狀結構（右 → 根 → 左）。
    
5. **主程式流程**：讀取整數直到 0 結尾，並同時插入 MinHeap 與 MaxHeap，再分別印出結果。

## 程式實作

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
using namespace std;

// ===================== 抽象類別宣告 =====================
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MaxPQ {
public:
    virtual ~MaxPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

// ===================== MinHeap 實作 =====================
template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap;

    // 將新元素向上調整至正確位置（維持最小堆性質）
    void HeapifyUp(int index) {
        while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // 將根節點向下調整至正確位置
    void HeapifyDown(int index) {
        int left, right, smallest;
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < heap.size() && heap[left] < heap[smallest]) smallest = left;
            if (right < heap.size() && heap[right] < heap[smallest]) smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else break;
        }
    }

    // 遞迴印出樹狀結構（右 → 根 → 左）
    void PrintTreeHelper(int index, int indent) const {
        if (index >= heap.size()) return;
        int right = 2 * index + 2;
        if (right < heap.size()) PrintTreeHelper(right, indent + 4);

        if (indent) cout << setw(indent) << " ";
        cout << heap[index] << endl;

        int left = 2 * index + 1;
        if (left < heap.size()) PrintTreeHelper(left, indent + 4);
    }

public:
    bool IsEmpty() const override { return heap.empty(); }

    const T& Top() const override {
        if (IsEmpty()) throw underflow_error("MinHeap is empty.");
        return heap[0];
    }

    void Push(const T& item) override {
        heap.push_back(item);
        HeapifyUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw underflow_error("MinHeap is empty.");
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty()) HeapifyDown(0);
    }

    // 印出堆陣列內容
    void PrintArray() const {
        cout << "MinHeap 陣列: ";
        for (const auto& val : heap) cout << val << " ";
        cout << endl;
    }

    // 印出樹狀結構
    void PrintTree() const {
        cout << "MinHeap 樹狀結構:\n";
        PrintTreeHelper(0, 0);
    }
};

// ===================== MaxHeap 實作 =====================
template <class T>
class MaxHeap : public MaxPQ<T> {
private:
    vector<T> heap;

    // 將新元素向上調整至正確位置（維持最大堆性質）
    void HeapifyUp(int index) {
        while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // 將根節點向下調整至正確位置
    void HeapifyDown(int index) {
        int left, right, largest;
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < heap.size() && heap[left] > heap[largest]) largest = left;
            if (right < heap.size() && heap[right] > heap[largest]) largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            }
            else break;
        }
    }

    // 遞迴印出樹狀結構（右 → 根 → 左）
    void PrintTreeHelper(int index, int indent) const {
        if (index >= heap.size()) return;
        int right = 2 * index + 2;
        if (right < heap.size()) PrintTreeHelper(right, indent + 4);

        if (indent) cout << setw(indent) << " ";
        cout << heap[index] << endl;

        int left = 2 * index + 1;
        if (left < heap.size()) PrintTreeHelper(left, indent + 4);
    }

public:
    bool IsEmpty() const override { return heap.empty(); }

    const T& Top() const override {
        if (IsEmpty()) throw underflow_error("MaxHeap is empty.");
        return heap[0];
    }

    void Push(const T& item) override {
        heap.push_back(item);
        HeapifyUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw underflow_error("MaxHeap is empty.");
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty()) HeapifyDown(0);
    }

    // 印出堆陣列內容
    void PrintArray() const {
        cout << "MaxHeap 陣列: ";
        for (const auto& val : heap) cout << val << " ";
        cout << endl;
    }

    // 印出樹狀結構
    void PrintTree() const {
        cout << "MaxHeap 樹狀結構:\n";
        PrintTreeHelper(0, 0);
    }
};

// ===================== 主程式 =====================
int main() {
    MinHeap<int> minHeap;
    MaxHeap<int> maxHeap;

    int num;
    cout << "請輸入一串整數（以 0 結尾）: ";
    while (cin >> num && num != 0) {
        minHeap.Push(num);
        maxHeap.Push(num);
    }

    // 印出原始陣列內容
    cout << "\n======= 陣列輸出 =======\n";
    minHeap.PrintArray();
    maxHeap.PrintArray();

    // 印出樹狀結構
    cout << "\n======= 樹狀結構輸出 =======\n";
    minHeap.PrintTree();
    cout << endl;
    maxHeap.PrintTree();

    return 0;
}
```

## 效能分析
**時間複雜度**：
1. 插入 Push：O(log n)
2. 移除 Pop：O(log n)
3. 查詢頂端 Top：O(1)
4. 印出陣列：O(n)
5. 印出樹狀結構：O(n)

**空間複雜度**：
使用 vector 儲存堆資料，空間複雜度為 O(n)。

## 測試與驗證

### 測試案例

| 測試編號 | 輸入資料         | 預期輸出摘要                                                  |
|----------|------------------|---------------------------------------------------------------|
| TC01     | `10 20 30 0`     | MinHeap：`10 20 30`  MaxHeap：`30 20 10`                     |
| TC02     | `3 1 4 1 5 9 0`  | MinHeap：`1 1 3 4 5 9`  MaxHeap：`9 5 4 3 1 1`                 |
| TC03     | `-5 -1 -3 0`     | MinHeap：`-5 -3 -1`  MaxHeap：`-1 -3 -5`                   |
| TC04     | `0`              | 不印出任何內容（輸入為空）                                    |

---

### 驗證方法

1. **邊界測試**  
   輸入空集合、負整數、重複元素等，確保不發生例外錯誤或程式崩潰。

2. **手動比對結果**  
   根據輸入手動推導堆的內容與結構，比對 `PrintArray()` 與 `PrintTree()` 的輸出。

3. **堆結構正確性驗證**  
   - MinHeap：每個父節點值應 ≤ 子節點值  
   - MaxHeap：每個父節點值應 ≥ 子節點值

4. **輸出格式確認**  
   - `PrintArray()`：應印出堆的陣列內部結構  
   - `PrintTree()`：應以樹狀結構（右 → 根 → 左）清晰呈現堆的樣貌

### 實測案例

![image](https://github.com/xiao070707/-nfu-homework/blob/main/img/Screenshot%202025-06-02%20174450.png)

### 正確性驗證方法

1. **邊界測試**：測試空輸入、單一元素、負數等特殊狀況。

2. **手動比對**：與手動建立的堆進行比對，驗證 Top、Push、Pop 結果。

3. **樹狀結構驗證**：檢查每個節點是否符合堆的性質（MinHeap 每個父節點小於子節點，MaxHeap 則反之）。

## 結論
本程式成功實作了通用的 MinHeap 與 MaxHeap 結構，具有良好的可讀性與擴充性。透過抽象類別達成介面統一，實作中涵蓋插入、刪除、查詢等基本操作，並附有可視化的樹狀輸出，有助於學習與理解堆積結構的運作方式。   

## 申論及開發報告
本專案設計主要著重於**物件導向設計**與**堆積資料結構應用**。採用 C++ 的模板與虛擬函式機制，實作高度可重用與型別獨立的最小堆與最大堆類別。
