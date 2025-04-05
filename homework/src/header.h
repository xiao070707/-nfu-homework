#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <algorithm>

// 插入排序
template <typename T>
void InsertionSort(std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 快速排序（輔助）
template <typename T>
int Partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序
template <typename T>
void QuickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// 合併排序（輔助）
template <typename T>
void Merge(std::vector<T>& arr, int left, int mid, int right) {
    std::vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    size_t i = 0, j = 0;
    int k = left;
    while (i < L.size() && j < R.size()) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

// 合併排序
template <typename T>
void MergeSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

// 堆積排序（輔助）
template <typename T>
void Heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

// 堆積排序
template <typename T>
void HeapSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        Heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

#endif // HEADER_H
