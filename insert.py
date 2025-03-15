import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('./results/insert.csv')

agg_data = data.groupby('n').agg({
    'Chaining-insertion': 'mean',  
    'Perfect-insertion': 'mean',   
    'Redblack-insertion': 'mean'   
}).reset_index()

n = agg_data['n']
chaining_time = agg_data['Chaining-insertion']
perfect_time = agg_data['Perfect-insertion']
redblack_time = agg_data['Redblack-insertion']

# Avoid zero running time with "penalty" value 
chaining_time = chaining_time + 1e-10
perfect_time = perfect_time + 1e-10
redblack_time = redblack_time + 1e-10

plt.figure(figsize=(8, 6))
plt.plot(n, chaining_time, label='Chaining Insertion Running Time', marker='o', linestyle='-', color='b')
plt.plot(n, perfect_time, label='Perfect Insertion Running Time', marker='x', linestyle='--', color='g')
plt.plot(n, redblack_time, label='Red-Black Tree Insertion Running Time', marker='^', linestyle='-.', color='r')

plt.xscale('log')
plt.xlabel('n (Log scale)')
plt.ylabel('Running Time (in microseconds)')
plt.title('Running Time vs. Input Size (n) for Insertion')


plt.legend()
plt.tight_layout()
plt.show()
