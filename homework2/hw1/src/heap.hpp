#ifndef HEAP_HPP
#define HEAP_HPP

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

    void HeapifyUp(int index) {
        while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

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

    void PrintArray() const {
        cout << "MinHeap 陣列: ";
        for (const auto& val : heap) cout << val << " ";
        cout << endl;
    }

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

    void HeapifyUp(int index) {
        while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

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

    void PrintArray() const {
        cout << "MaxHeap 陣列: ";
        for (const auto& val : heap) cout << val << " ";
        cout << endl;
    }

    void PrintTree() const {
        cout << "MaxHeap 樹狀結構:\n";
        PrintTreeHelper(0, 0);
    }
};

#endif // HEAP_HPP

