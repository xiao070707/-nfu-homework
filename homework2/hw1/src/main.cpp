
#include "heap.hpp"

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
