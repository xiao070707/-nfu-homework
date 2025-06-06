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
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> n_values = { 100, 500, 1000, 2000, 3000, 4000,
                             5000, 6000, 7000, 8000, 9000, 10000 };

    ofstream fout("bst_height_log_ratio.csv");
    if (!fout) {
        cerr << "無法開啟檔案 bst_height_log_ratio.csv\n";
        return 1;
    }

    fout << "n,Height,log2(n),Height/log2(n)\n";
    cout << left << setw(6) << "n"
         << setw(8) << "Height"
         << setw(10) << "log2(n)"
         << "Height/log2(n)\n";

    double totalRatio = 0;
    int count = 0;

    for (int n : n_values) {
        BST tree;
        vector<int> keys;

        while (keys.size() < static_cast<size_t>(n)) {
            int val = rand();
            if (find(keys.begin(), keys.end(), val) == keys.end()) {
                keys.push_back(val);
            }
        }

        for (int key : keys) {
            tree.insert(key);
        }

        int h = tree.height();
        double log2n = log2(n);
        double ratio = h / log2n;
        totalRatio += ratio;
        count++;

        fout << n << "," << h << "," << log2n << "," << ratio << "\n";

        cout << left << setw(6) << n
             << setw(8) << h
             << setw(10) << fixed << setprecision(4) << log2n
             << fixed << setprecision(4) << ratio << "\n";
    }

    fout.close();

    cout << "\n平均 Height/log2(n)："
         << fixed << setprecision(4) << (totalRatio / count) << endl;
    cout << "結果已輸出到 bst_height_log_ratio.csv\n";

    return 0;
}

