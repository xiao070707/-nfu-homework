#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm> // �Ω� std::swap

using namespace std;

// ���J�Ƨǹ�{
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

// �ֳt�Ƨǹ�{�A�ϥΤT�Ƥ���ƪk�@�����
template <typename T>
int Partition(vector<T>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);

    swap(arr[mid], arr[high - 1]); // �N����Ʋ���˼ƲĤG��
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

// �X�ֱƧǹ�{�A�ϥέ��N��k
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

// ��n�Ƨǹ�{
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

// ���a���p�ƦC�ͦ���
template <typename T>
void WorstCaseInsertionSort(vector<T>& arr, int n) {
    // ����ƧǡG���a���p��󴡤J�Ƨ�
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

template <typename T>
void WorstCaseQuickSort(vector<T>& arr, int n) {
    // �w�Ƨǩΰf�Ƨǹ��ֳt�ƧǬ����a���p
    // �o�̧ڭ̨ϥΰf�Ƨ�
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

template <typename T>
void WorstCaseHeapSort(vector<T>& arr, int n) {
    // �����ϦV�ƧǪ��ƦC�O���a���p
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// �D�{�ǡG���q���P�ƶq�����U���ƧǮɶ�
int main() {
    srand(static_cast<unsigned int>(time(0)));

    // ��B���աG���q���P�ƶq�����U���ƧǮɶ�
    int sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        vector<int> arr(size);

        // �H���ͦ��ƦC
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10000;
        }

        // ���J�ƧǴ���
        vector<int> arr_copy = arr;
        clock_t start = clock();
        InsertionSort(arr_copy);
        clock_t end = clock();
        cout << "���J�Ƨ� (" << size << " �Ӥ���) �ɶ�: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

        // �ֳt�ƧǴ���
        arr_copy = arr;
        start = clock();
        QuickSort(arr_copy, 0, size - 1);
        end = clock();
        cout << "�ֳt�Ƨ� (" << size << " �Ӥ���) �ɶ�: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

        // �X�ֱƧǴ���
        arr_copy = arr;
        start = clock();
        MergeSort(arr_copy);
        end = clock();
        cout << "�X�ֱƧ� (" << size << " �Ӥ���) �ɶ�: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

        // ��n�ƧǴ���
        arr_copy = arr;
        start = clock();
        HeapSort(arr_copy);
        end = clock();
        cout << "��n�Ƨ� (" << size << " �Ӥ���) �ɶ�: "
            << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";
    }

    // ���a���p���աG5000�Ӥ���
    int n = 5000;  // �]�m���ռƶq�� 5000

    // �Ыبô��մ��J�ƧǪ����a���p
    vector<int> arr(n);
    WorstCaseInsertionSort(arr, n);
    clock_t start = clock();
    InsertionSort(arr);
    clock_t end = clock();
    cout << "���J�Ƨ� (���a���p) (" << n << " �Ӥ���) �ɶ�: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

    // �Ыبô��էֳt�ƧǪ����a���p
    WorstCaseQuickSort(arr, n);
    start = clock();
    QuickSort(arr, 0, n - 1);
    end = clock();
    cout << "�ֳt�Ƨ� (���a���p) (" << n << " �Ӥ���) �ɶ�: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

    // �Ыبô��զX�ֱƧǪ����a���p
    start = clock();
    MergeSort(arr);
    end = clock();
    cout << "�X�ֱƧ� (���a���p) (" << n << " �Ӥ���) �ɶ�: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

    // �Ыبô��հ�n�ƧǪ����a���p
    WorstCaseHeapSort(arr, n);
    start = clock();
    HeapSort(arr);
    end = clock();
    cout << "��n�Ƨ� (���a���p) (" << n << " �Ӥ���) �ɶ�: "
        << static_cast<double>(end - start) / CLOCKS_PER_SEC << " ��\n";

    return 0;
}
