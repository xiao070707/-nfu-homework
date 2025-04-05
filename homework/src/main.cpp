#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "header.h"

void PrintVector(const std::vector<int>& arr) {
    for (int num : arr)
        std::cout << num << " ";
    std::cout << "\n";
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<int> sizes = {500, 1000, 2000, 3000, 4000, 5000};

    for (int size : sizes) {
        std::vector<int> original;
        for (int i = 0; i < size; ++i)
            original.push_back(std::rand() % 10000);

        std::vector<int> arr;

        std::cout << "=== 測試資料筆數: " << size << " ===\n";

        arr = original;
        clock_t start = clock();
        InsertionSort(arr);
        clock_t end = clock();
        std::cout << "插入排序耗時: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr = original;
        start = clock();
        QuickSort(arr, 0, arr.size() - 1);
        end = clock();
        std::cout << "快速排序耗時: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr = original;
        start = clock();
        MergeSort(arr, 0, arr.size() - 1);
        end = clock();
        std::cout << "合併排序耗時: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒\n";

        arr = original;
        start = clock();
        HeapSort(arr);
        end = clock();
        std::cout << "堆積排序耗時: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒\n";

        std::cout << "--------------------------\n";
    }

    return 0;
}
