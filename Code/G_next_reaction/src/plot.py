import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties

with open("./results/sim.txt", "r") as f:
	data = f.readlines()

t = data[0].strip().split(" ")
time = [float(i) for i in t]

for i in range (1, len(data)) : 
	tmp = data[i].strip().split(" : ")   # tmp[0] = label  tmp[1] = the rest of the data 
	x = tmp[1].strip().split(" ")
	y_axis = [float(i) for i in x]
	

	plt.scatter(time, y_axis, label=tmp[0])



plt.title('Sample trajectory of the secondary nucleation model \n with Amylofit\'s fitted parameters  ', color='b')
fontP = FontProperties()
fontP.set_size('x-small')
plt.legend(loc='upper center', prop=fontP, bbox_to_anchor=(0.5, 1.00),ncol=3, fancybox=True, shadow=True)
plt.ylabel("Number of molecules")
plt.xlabel("Time step")
plt.savefig('./results/sim.png')