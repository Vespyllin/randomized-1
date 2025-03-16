import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("largest-linked-list-cut.csv")

# Group the data by 'n' and calculate the maximum linked list size for each 'n'
max_sizes = data.groupby('n')['LargestListSize'].max()

plt.figure(figsize=(10, 6))
plt.plot(data['n'], data['LargestListSize'], marker='o', linestyle='-', color='b', label='Largest Linked List Size')

plt.xscale('log')
plt.yscale('log')

plt.xlabel("Table Size (n)", fontsize=12)
plt.ylabel("Largest Linked List Size", fontsize=12)
plt.title("Largest Linked List Size in Hashing with Chaining", fontsize=14)

plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.legend()
plt.show()

