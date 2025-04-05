# 41243254和4124326

作業一
## 解題說明

本題要求實現四種常見排序算法，並測量其在不同數量元素下的運行時間。這些排序算法包括：插入排序、快速排序、合併排序和堆積排序。

### 解題策略

1. 插入排序 (Insertion Sort)：
利用遞增順序將元素一個一個插入到已排序的部分。
2. 快速排序 (QuickSort)：
使用分治法，將數列劃分成兩個部分，並分別對這兩個部分遞迴排序。
3. 合併排序 (MergeSort)：
利用分治法將數列不斷拆分為子數列，再將子數列合併。
4. 堆積排序 (HeapSort)：
基於堆積數據結構，將數列轉化為最大堆或最小堆，並不斷取出最大元素來排序。

## 程式實作

```cpp
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm> // 用於 std::swap

using namespace std;

// 插入排序實現
template <typename T>
void InsertionSort(vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 快速排序實現，使用三數中位數法作為基準
template <typename T>
int Partition(vector<T>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);

    swap(arr[mid], arr[high - 1]); // 將中位數移到倒數第二位
    T pivot = arr[high - 1];

    int i = low;
    for (int j = low; j < high - 1; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high - 1]);
    return i;
}

template <typename T>
void QuickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// 合併排序實現，使用迭代方法
template <typename T>
void Merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void MergeSort(vector<T>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size = 2 * size) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);
            Merge(arr, left, mid, right);
        }
    }
}

// 堆積排序實現
template <typename T>
void Heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

template <typename T>
void HeapSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

// 主程序：測量不同數量元素下的排序時間
int main() {
    srand(static_cast<unsigned int>(time(0)));

    int sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        vector<int> arr(size);

        // 隨機生成數列
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10000;
        }

        // 插入排序測試
        vector<int> arr_copy = arr;
        clock_t start = clock();
        InsertionSort(arr_copy);
        clock_t end = clock();
        cout << "插入排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        // 快速排序測試
        arr_copy = arr;
        start = clock();
        QuickSort(arr_copy, 0, size - 1);
        end = clock();
        cout << "快速排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        // 合併排序測試
        arr_copy = arr;
        start = clock();
        MergeSort(arr_copy);
        end = clock();
        cout << "合併排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        // 堆積排序測試
        arr_copy = arr;
        start = clock();
        HeapSort(arr_copy);
        end = clock();
        cout << "堆積排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";
    }

    return 0;
}
```

## 效能分析
時間複雜度：
1. 插入排序：O(n²)
2. 快速排序：O(n log n)（平均情況）
3. 合併排序：O(n log n)
4. 堆積排序：O(n log n)
   
空間複雜度：
1. 插入排序：O(1)
2. 快速排序：O(log n)
3. 合併排序：O(n)
4. 堆積排序：O(1)

## 測試與驗證

### 測試案例（正確性驗證）

使用固定的小型資料集，驗證每種排序演算法的排序結果是否正確。

| 測試案例 | 輸入資料             | 預期排序結果      | 插入排序 | 快速排序 | 合併排序 | 堆積排序 |
|----------|----------------------|-------------------|-----------|-----------|-----------|-----------|
| 測試一   | `{5, 2, 9, 1, 3}`    | `{1, 2, 3, 5, 9}` | ✅        | ✅        | ✅        | ✅        |
| 測試二   | `{10, 8, 6, 4, 2}`   | `{2, 4, 6, 8, 10}`| ✅        | ✅        | ✅        | ✅        |
| 測試三   | `{1, 2, 3, 4, 5}`    | `{1, 2, 3, 4, 5}` | ✅        | ✅        | ✅        | ✅        |
| 測試四   | `{7}`                | `{7}`             | ✅        | ✅        | ✅        | ✅        |
| 測試五   | `{}`（空陣列）       | `{}`              | ✅        | ✅        | ✅        | ✅        |

> ✅ 表示排序後的結果與 `std::sort()` 結果一致。

---

### 測試案例（效能驗證）

| 測試案例 | 元素數量 $n$ | 插入排序時間 | 快速排序時間 | 合併排序時間 | 堆積排序時間 |
|----------|--------------|----------------|----------------|----------------|----------------|
| 測試一   | 500          | 0.004 秒       | 0.001 秒       | 0.002 秒       | 0.001 秒       |
| 測試二   | 1000         | 0.016 秒       | 0.002 秒       | 0.003 秒       | 0.002 秒       |
| 測試三   | 2000         | 0.060 秒       | 0.005 秒       | 0.007 秒       | 0.005 秒       |
| 測試四   | 3000         | 0.130 秒       | 0.007 秒       | 0.009 秒       | 0.007 秒       |
| 測試五   | 4000         | 0.240 秒       | 0.010 秒       | 0.012 秒       | 0.010 秒       |
| 測試六   | 5000         | 0.370 秒       | 0.014 秒       | 0.015 秒       | 0.012 秒       |

### 正確性驗證方法

使用 std::is_sorted() 標準函式來檢查排序結果：
```cpp
if (!is_sorted(arr_copy.begin(), arr_copy.end()))
    cout << "排序錯誤！\n";
```

### 結論

測試結果顯示，四種排序演算法在正確性上皆與 std::sort() 結果一致，表示實作正確。

在效能方面：

1. 插入排序 適合小型資料，資料量大時效能迅速下降。

2. 快速排序 效能最佳，適合中大型資料。

3. 合併排序 表現穩定，僅次於快速排序。

4. 堆積排序 效能穩定，略慢於快速與合併排序。
## 申論及開發報告

1. 開發心得：
透過本次實作，加深了對各種排序法特性的理解。例如插入排序雖實作簡單，但在資料量大或最壞情況下表現不佳；相較之下，快速排序與合併排序在效能表現上較為穩定。

2. 延伸思考：
可進一步比較使用 std::sort（內建排序）的效率，或對大規模資料測試多執行緒排序方法。另外，也能進一步探討非比較排序如 Radix Sort 的實作與效能。
