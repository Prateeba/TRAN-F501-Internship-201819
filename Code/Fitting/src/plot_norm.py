import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt

with open("results/normalized.txt", "r") as f:
	data = f.readlines()


for i in range (1, len(data)) : 
	points = data[i].strip().split(" ")
	x = points[0 : points.index('=>')]
	x_axis = [float(i) for i in x]
	
	y = points[points.index('=>')+1 : len(points)]
	y_axis = [float(i) for i in y]

	plt.scatter(x_axis, y_axis)


plt.title('To set', color='r')
plt.legend(loc='upper right')
plt.legend().draggable()
plt.ylabel("Time (h)")
plt.xlabel("To set")
plt.savefig('results/normalized_data.png')