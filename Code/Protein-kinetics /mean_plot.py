import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
from scipy.interpolate import make_interp_spline, BSpline

time = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
k_plus_k_n = [2.4381559480304205,2.436842934469693,2.372390006307681, 1.8955178971642184, 2.456580683480646, 2.4141806509621064, 1.6236517719160592,
2.007277661715572, 0.6560332453672935, 0.04572425859412643]

k_plus_k2 = [0.5748557315871972, 0.08440708175829315, 1.3801097506733473, 2.120438404990547, 0.3634341084416337, 0.39047114725307197,2.156798575448078, 2.0866585215030478, 2.2371266272737165,2.2266064431887314]

mean_square = [0.07888009870070369, 0.07920076544040683, 0.07795989767115859, 0.07762331160089107, 0.07911731480235772, 0.07915612966829733, 0.07781699116929953, 0.07756684395733345, 0.07882701224247812, 0.08005155418686258]


plt.step(time, k_plus_k_n)


#plt.plot(time, mean,'b--', label='mean')

plt.title('Sample trajectory of the secondary nucleation model with Amylofit\'s fitted parameters  ', color='b')
fontP = FontProperties()
fontP.set_size('x-small')
plt.legend(loc='upper center', prop=fontP, bbox_to_anchor=(0.5, 1.00),ncol=3, fancybox=True, shadow=True)
plt.ylabel("Number of molecules")
plt.xlabel("Time (h)")
plt.show()
plt.savefig('/results/second_nucleation.png')








