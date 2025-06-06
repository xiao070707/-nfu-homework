import matplotlib.pyplot as plt
import pandas as pd

# 讀取 CSV 檔
df = pd.read_csv('bst_height_log_ratio.csv')

# 繪圖
plt.figure(figsize=(10, 6))
plt.plot(df['n'], df['Height/log2(n)'], marker='o', color='blue', linestyle='-')
plt.title('Height / log₂(n) vs n for Random BST')
plt.xlabel('n (number of nodes)')
plt.ylabel('Height / log₂(n)')
plt.grid(True)
plt.xticks(df['n'])  # 每個 n 值都標示
plt.tight_layout()

# 顯示圖表
plt.show()
