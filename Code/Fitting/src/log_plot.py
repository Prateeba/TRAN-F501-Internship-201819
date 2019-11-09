import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
 

with open("results/vs_plot.txt", "r") as f:
	data = f.readlines()

scaling_exp = data[0].strip()

p1 = data[1].strip().split(" ")
p2 = data[2].strip().split(" ")

x = p1[0 : p1.index('=>')]
x_axis = [float(i) for i in x]
	
y = p1[p1.index('=>')+1 : len(p1)]
y_axis = [float(i) for i in y]

x_fit = p2[0 : p2.index('=>')]
x_fit_axis = [float(i) for i in x_fit]

y_fit = p2[p2.index('=>')+1 : len(p2)]
y_fit_axis = [float(i) for i in y_fit]

plt.scatter(x_axis, y_axis , marker='o', color='g', label='Half time of each curve')
plt.plot(x_fit_axis, y_fit_axis, color='b', linewidth=1.0, linestyle='--', label="Initial monomer concentration of each curve")

plt.title('Half-time versus monomer concentration \n Scaling exponent = '+scaling_exp, color='r')
plt.legend(loc='upper right')
plt.legend().draggable()
plt.ylabel("Half-time (h)")
plt.xlabel("Initial monomer concentration")

plt.savefig('results/half_time_vs_monomer.png')