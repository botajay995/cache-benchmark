import pandas as pd
import matplotlib.pyplot as plt

# 1. Read the data
df = pd.read_csv("data/stage2.csv")

# 2. Two runs exist for each (n, threads) pair, so average them
g = df.groupby(["n", "threads"])["median_ms"].mean().reset_index()

# 3. One line per matrix size
for n in [1024, 2048, 4096]:
    sub = g[g["n"] == n]
    base = sub[sub["threads"] == 1]["median_ms"].values[0]  # time with 1 thread
    speedup = base / sub["median_ms"].values                # >1 means faster
    plt.plot(sub["threads"].values, speedup, marker="o", label=f"N={n}")

# 4. Ideal linear speedup for reference
plt.plot([1, 12], [1, 12], "--", color="gray", label="Ideal (linear)")

# 5. Mark the 6 physical cores
plt.axvline(6, linestyle=":", color="red", label="6 physical cores")

# 6. Labels and save
plt.xlabel("Number of threads")
plt.ylabel("Speedup (time at 1 thread / time at T threads)")
plt.title("Threaded row-major traversal: speedup vs threads")
plt.legend()
plt.grid(True)
plt.savefig("plots/stage2_speedup.png", dpi=150)
