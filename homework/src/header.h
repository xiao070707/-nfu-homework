#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>
#include <algorithm> // for std::swap

// 插入排序
template <typename T>
void InsertionSort(std::vector<T>& arr) {
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

// 快速排序：三數中位數法
template <typename T>
int Partition(std::vector<T>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);

    std::swap(arr[mid], arr[high - 1]);
    T pivot = arr[high - 1];

    int i = low;
    for (int j = low; j < high - 1; j++) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[high - 1]);
    return i;
}

template <typename T>
void QuickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// 合併排序（迭代）
template <typename T>
void Merge(std::vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T>
void MergeSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            Merge(arr, left, mid, right);
        }
    }
}

// 堆積排序
template <typename T>
void Heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

template <typename T>
void HeapSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

// 最壞情況數列生成器
template <typename T>
void WorstCaseInsertionSort(std::vector<T>& arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

template <typename T>
void WorstCaseQuickSort(std::vector<T>& arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

template <typename T>
void WorstCaseHeapSort(std::vector<T>& arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

#endif // SORT_ALGORITHMS_H
