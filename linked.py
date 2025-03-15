import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./results/largest_linked_list_sizes.csv")
max_sizes = data.groupby('n')['LargestListSize'].max()

plt.figure(figsize=(10, 6))
plt.xscale('log')
plt.yscale('log')
plt.xlabel("Table Size (n)", fontsize=12)
plt.ylabel("Max Linked List Size", fontsize=12)
plt.title("Maximum Linked List Size in Hashing with Chaining", fontsize=14)
plt.plot(max_sizes.index, max_sizes.values, marker='o', linestyle='-', color='b', label='Maximum of Linked List Size')

plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.legend()
plt.show()

