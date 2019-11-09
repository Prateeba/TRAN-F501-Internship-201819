import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt

with open("./results/sim.txt", "r") as f:
	data = f.readlines()

t = data[0].strip().split(" ")
time = [float(i) for i in t]

for i in range (1, len(data)) : 
	tmp = data[i].strip().split(" : ")   # tmp[0] = label  tmp[1] = the rest of the data 
	x = tmp[1].strip().split(" ")
	y_axis = [float(i) for i in x]
	

	plt.scatter(time, y_axis, label=tmp[0])


plt.title('To set', color='r')
plt.legend(loc='upper right')
plt.legend().draggable()
plt.ylabel("Time (h)")
plt.xlabel("To set")
plt.savefig('./results/sim.png')