import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
from scipy.interpolate import make_interp_spline, BSpline


with open("../results/g.txt", "r") as f:
	data = f.readlines()

all = []
time = [0.000000,1.000000,2.000000,3.000000,4.000000,5.000000,6.000000,7.000000,8.000000,9.000000,10.000000,11.000000,12.000000,13.000000,14.000000,15.000000,16.000000,17.000000,18.000000,19.000000,20.000000]
#time = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]
for i in range (0, len(data)) : 
	tmp = data[i].strip().split(" ")   
	y_axis = [float(i) for i in tmp]
	all.append(y_axis)
	plt.step(time, y_axis, label='Realization '+str(i+1))

mean = []
for i in range(0, len(all[0])) : 
	tmp = 0 
	for j in range(len(all)) : 
		tmp += all[j][i]
	mean.append(tmp/(len(all)))

xnew = np.linspace(min(time), max(time), 1000)
spl = make_interp_spline(time, mean, k=3)  # type: BSpline
power_smooth = spl(xnew)

plt.plot(xnew, power_smooth, 'k--', label='stochastic mean')

#plt.plot(time, mean,'b--', label='mean')

plt.title('Sample trajectories of specie G', color='b')
fontP = FontProperties()
fontP.set_size('x-small')
plt.legend(loc='upper center', prop=fontP, bbox_to_anchor=(0.5, 1.00),ncol=3, fancybox=True, shadow=True)
plt.ylabel("Number of molecules")
plt.xlabel("Time (h)")
plt.savefig('../results/g.png')