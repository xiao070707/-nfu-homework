#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "bst.hpp"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));  // 設定亂數種子

    // 測試用的 n 值陣列（樹節點數）
    vector<int> n_values = { 100, 500, 1000, 2000, 3000, 4000,
                             5000, 6000, 7000, 8000, 9000, 10000 };

    ofstream fout("bst_height_log_ratio.csv");  // 開啟輸出檔案
    if (!fout) {
        cerr << "無法開啟檔案 bst_height_log_ratio.csv\n";
        return 1;
    }

    // 輸出 CSV 標題列
    fout << "n,Height,log2(n),Height/log2(n)\n";

    // 終端機輸出欄位標題
    cout << left << setw(6) << "n"
         << setw(8) << "Height"
         << setw(10) << "log2(n)"
         << "Height/log2(n)\n";

    double totalRatio = 0;  // 用來計算平均 Height/log2(n)
    int count = 0;

    // 對每個 n 值進行實驗
    for (int n : n_values) {
        BST tree;
        vector<int> keys;

        // 產生不重複的亂數 key，直到數量達 n
        while (keys.size() < static_cast<size_t>(n)) {
            int val = rand();
            if (find(keys.begin(), keys.end(), val) == keys.end()) {
                keys.push_back(val);
            }
        }

        // 將所有 key 插入 BST
        for (int key : keys) {
            tree.insert(key);
        }

        int h = tree.height();       // 計算樹高
        double log2n = log2(n);      // 計算 log2(n)
        double ratio = h / log2n;    // 高度與 log2(n) 的比率
        totalRatio += ratio;
        count++;

        // 輸出結果到 CSV
        fout << n << "," << h << "," << log2n << "," << ratio << "\n";

        // 同時在終端輸出結果
        cout << left << setw(6) << n
             << setw(8) << h
             << setw(10) << fixed << setprecision(4) << log2n
             << fixed << setprecision(4) << ratio << "\n";
    }

    fout.close();

    // 輸出平均值
    cout << "\n平均 Height/log2(n)："
         << fixed << setprecision(4) << (totalRatio / count) << endl;
    cout << "結果已輸出到 bst_height_log_ratio.csv\n";

    return 0;
}
