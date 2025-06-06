def total_input_time(m, k, n, t_seek, t_latency, t_transfer, t_cpu):
    """
    計算在 k 路合併時的總輸入時間與 CPU 時間比較
    參數:
        m        : 初始 runs 的數量
        k        : 合併的路數
        n        : 總資料筆數
        t_seek   : 磁碟尋道時間
        t_latency: 磁碟延遲時間
        t_transfer: 傳輸每筆資料所需時間
        t_cpu    : CPU 處理時間（假設固定）
    回傳:
        input_time: 總輸入時間 (秒)
        cpu_time  : CPU 處理時間 (秒)
    """
    # 計算需要多少次磁碟存取，ceil(m/k)
    disk_accesses = (m + k - 1) // k  

    # 總輸入時間 = 磁碟存取次數 * (尋道時間 + 延遲時間) + 傳輸時間 * 總筆數
    input_time = disk_accesses * (t_seek + t_latency) + t_transfer * n

    # CPU 時間假設固定不變
    cpu_time = t_cpu

    return input_time, cpu_time


# 參數設定
t_y = 0.08           # 延遲時間 80ms
t_1 = 0.02           # 尋道時間 20ms
t_seek = t_1         # 磁碟尋道時間
t_latency = t_y      # 磁碟延遲時間
t_transfer = 1e-3    # 每筆資料傳輸時間 0.001秒
n = 200000           # 資料筆數
m = 64               # runs數量
t_cpu = 5            # 假設 CPU 處理時間為 5 秒（可調整）

# 印出不同 k 值對應的輸入時間和 CPU 時間
print("k\tInput_Time(s)\tCPU_Time(s)")
for k in range(2, 33):
    input_t, cpu_t = total_input_time(m, k, n, t_seek, t_latency, t_transfer, t_cpu)
    print(f"{k}\t{input_t:.2f}\t\t{cpu_t:.2f}")
