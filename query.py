import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('./results/query.csv')

agg_data = data.groupby('n').agg({
    'Chaining-query': 'mean',  # Average running time
    'Perfect-query': 'mean',   # Average running time
    'Redblack-query': 'mean'   # Average running time
}).reset_index()


n = agg_data['n']
chaining_time = agg_data['Chaining-query']
perfect_time = agg_data['Perfect-query']
redblack_time = agg_data['Redblack-query']

# Add "penalty" to avoid log zero
chaining_time = chaining_time + 1e-10
perfect_time = perfect_time + 1e-10
redblack_time = redblack_time + 1e-10

plt.figure(figsize=(8, 6))
plt.plot(n, chaining_time, label='Chaining Query Running Time', marker='o', linestyle='-', color='b')
plt.plot(n, perfect_time, label='Perfect Query Running Time', marker='x', linestyle='--', color='g')
plt.plot(n, redblack_time, label='Red-Black Tree Query Running Time', marker='^', linestyle='-.', color='r')

plt.xscale('log')
plt.xlabel('n (Log scale)')
plt.ylabel('Running Time (in microseconds)')
plt.title('Running Time vs. Input Size (n) for Query')
plt.legend()
plt.tight_layout()
plt.show()

