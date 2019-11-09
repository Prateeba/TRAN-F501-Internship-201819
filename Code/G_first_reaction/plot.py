import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
from scipy.interpolate import make_interp_spline, BSpline


with open("results_100/w.txt", "r") as f:
	data = f.readlines()

all = []
time = [0, 0.1, 0.2, 0.30000000000000004, 0.4, 0.5, 0.6, 0.7, 0.7999999999999999, 0.8999999999999999, 0.9999999999999999, 1.0999999999999999, 1.2, 1.3, 1.4000000000000001, 1.5000000000000002, 1.6000000000000003, 1.7000000000000004, 1.8000000000000005, 1.9000000000000006, 2.0000000000000004, 2.1000000000000005, 2.2000000000000006, 2.3000000000000007, 2.400000000000001, 2.500000000000001, 2.600000000000001, 2.700000000000001, 2.800000000000001, 2.9000000000000012, 3.0000000000000013, 3.1000000000000014, 3.2000000000000015, 3.3000000000000016, 3.4000000000000017, 3.5000000000000018, 3.600000000000002, 3.700000000000002, 3.800000000000002, 3.900000000000002, 4.000000000000002, 4.100000000000001, 4.200000000000001, 4.300000000000001, 4.4, 4.5, 4.6, 4.699999999999999, 4.799999999999999, 4.899999999999999, 4.999999999999998, 5.099999999999998, 5.1999999999999975, 5.299999999999997, 5.399999999999997, 5.4999999999999964, 5.599999999999996, 5.699999999999996, 5.799999999999995, 5.899999999999995, 5.999999999999995, 6.099999999999994, 6.199999999999994, 6.299999999999994, 6.399999999999993, 6.499999999999993, 6.5999999999999925, 6.699999999999992, 6.799999999999992, 6.8999999999999915, 6.999999999999991, 7.099999999999991, 7.19999999999999, 7.29999999999999, 7.39999999999999, 7.499999999999989, 7.599999999999989, 7.699999999999989, 7.799999999999988, 7.899999999999988, 7.999999999999988, 8.099999999999987, 8.199999999999987, 8.299999999999986, 8.399999999999986, 8.499999999999986, 8.599999999999985, 8.699999999999985, 8.799999999999985, 8.899999999999984, 8.999999999999984, 9.099999999999984, 9.199999999999983, 9.299999999999983, 9.399999999999983, 9.499999999999982, 9.599999999999982, 9.699999999999982, 9.799999999999981, 9.89999999999998, 9.99999999999998]
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

plt.title('Sample trajectories of specie W', color='b')
fontP = FontProperties()
fontP.set_size('x-small')
#plt.legend(loc='upper center', prop=fontP, bbox_to_anchor=(0.5, 1.00),ncol=20, fancybox=True, shadow=True)
plt.ylabel("Number of molecules")
plt.xlabel("Time (h)")
plt.savefig('results_100/w.png')