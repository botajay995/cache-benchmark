import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/stage1.csv")
row = df[df["type"] == "row"]
col = df[df["type"] == "col"]

plt.plot(row["n"], row["median_ms"], marker="o", label="Row-major")
plt.plot(col["n"], col["median_ms"], marker="o", label="Column-major")

plt.xscale("log")
plt.yscale("log")

plt.xlabel("Matrix size N (N x N ints)")
plt.ylabel("Median time (ms)")
plt.title("Row-major vs column-major traversal")
plt.legend()
plt.grid(True)

plt.savefig("plots/stage1.png", dpi=150)




