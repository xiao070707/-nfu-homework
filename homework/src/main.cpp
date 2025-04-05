#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "header.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        vector<int> arr(size);
        for (int i = 0; i < size; i++) arr[i] = rand() % 10000;

        vector<int> arr_copy = arr;
        clock_t start = clock();
        InsertionSort(arr_copy);
        clock_t end = clock();
        cout << "插入排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr_copy = arr;
        start = clock();
        QuickSort(arr_copy, 0, size - 1);
        end = clock();
        cout << "快速排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr_copy = arr;
        start = clock();
        MergeSort(arr_copy);
        end = clock();
        cout << "合併排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr_copy = arr;
        start = clock();
        HeapSort(arr_copy);
        end = clock();
        cout << "堆積排序 (" << size << " 個元素) 時間: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";
    }

    int n = 5000;
    vector<int> arr(n);

    WorstCaseInsertionSort(arr, n);
    clock_t start = clock();
    InsertionSort(arr);
    clock_t end = clock();
    cout << "插入排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    WorstCaseQuickSort(arr, n);
    start = clock();
    QuickSort(arr, 0, n - 1);
    end = clock();
    cout << "快速排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    start = clock();
    MergeSort(arr);
    end = clock();
    cout << "合併排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    WorstCaseHeapSort(arr, n);
    start = clock();
    HeapSort(arr);
    end = clock();
    cout << "堆積排序 (最壞情況) (" << n << " 個元素) 時間: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒\n";

    return 0;
}
