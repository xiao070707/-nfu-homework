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

// 最壞情況數列生成器
template <typename T>
void WorstCaseInsertionSort(vector<T>& arr, int n) {
    // 遞減排序：最壞情況對於插入排序
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

template <typename T>
void WorstCaseQuickSort(vector<T>& arr, int n) {
    // 已排序或逆排序對於快速排序為最壞情況
    // 這裡我們使用逆排序
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

template <typename T>
void WorstCaseHeapSort(vector<T>& arr, int n) {
    // 完全反向排序的數列是最壞情況
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// 主程序：測量不同數量元素下的排序時間
int main() {
    srand(static_cast<unsigned int>(time(0)));

    // 初步測試：測量不同數量元素下的排序時間
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

    // 最壞情況測試：5000個元素
    int n = 5000;  // 設置測試數量為 5000

    // 創建並測試插入排序的最壞情況
    vector<int> arr(n);
    WorstCaseInsertionSort(arr, n);
    clock_t start = clock();
    InsertionSort(arr);
    clock_t end = clock();
    cout << "插入排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    // 創建並測試快速排序的最壞情況
    WorstCaseQuickSort(arr, n);
    start = clock();
    QuickSort(arr, 0, n - 1);
    end = clock();
    cout << "快速排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    // 創建並測試合併排序的最壞情況
    start = clock();
    MergeSort(arr);
    end = clock();
    cout << "合併排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    // 創建並測試堆積排序的最壞情況
    WorstCaseHeapSort(arr, n);
    start = clock();
    HeapSort(arr);
    end = clock();
    cout << "堆積排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    return 0;
}
