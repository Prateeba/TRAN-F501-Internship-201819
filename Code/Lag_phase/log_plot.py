import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
 

def plot_log() : 


	x_scatter = [3.91202,3.91202,3.91202,3.91202,3.68888,3.68888,3.68888,3.68888,3.55535,3.55535,3.55535,3.55535,3.4012,3.4012,3.4012,3.4012,3.21888,3.21888,3.21888,3.21888,2.99573,2.99573,2.99573,2.99573,2.83321,2.83321,2.83321,2.83321,2.70805,2.70805,2.70805,2.70805,2.56495,2.56495 ,2.56495 ,2.56495 ,2.3979 ,2.3979 ,2.3979, 2.3979]
	y_scatter = [-0.154487, -0.129786 ,-0.1062 ,-0.169626, 0.0507843, 0.091483 ,0.0651825 ,-0.000687145 ,0.185681 ,0.16441 ,0.235387 ,0.227006, 0.346291 ,0.343067 ,0.346596, 0.368058 ,0.505184 ,0.496054 ,0.473503, 0.489358 ,0.877045 ,0.859143, 0.824695, 0.877237, 0.950545 ,0.911877 ,0.888853 ,0.930473 ,1.06451 ,1.05152, 1.06144 ,1.04789 ,1.13102, 1.2501 ,1.19779 ,1.14715 ,1.44008 ,1.39281 ,1.44074 ,1.5366]

	x_fit = [3.91202, 3.91202 ,3.91202, 3.91202, 3.68888, 3.68888 ,3.68888, 3.68888, 3.55535 ,3.55535, 3.55535 ,3.55535 ,3.4012, 3.4012 ,3.4012 ,3.4012 ,3.21888 ,3.21888 ,3.21888 ,3.21888 ,2.99573 ,2.99573 ,2.99573, 2.99573, 2.83321, 2.83321 ,2.83321, 2.83321 ,2.70805, 2.70805 ,2.70805 ,2.70805 ,2.56495 ,2.56495, 2.56495 ,2.56495 ,2.3979 ,2.3979, 2.3979, 2.3979]
	y_fit = [-0.168596, -0.168596, -0.168596, -0.168596 ,0.0622024, 0.0622024, 0.0622024, 0.0622024, 0.200315, 0.200315, 0.200315 ,0.200315 ,0.359754, 0.359754 ,0.359754 ,0.359754, 0.54833 ,0.54833, 0.54833 ,0.54833 ,0.779129, 0.779129, 0.779129 ,0.779129, 0.947223 ,0.947223 ,0.947223 ,0.947223 ,1.07668 ,1.07668, 1.07668 ,1.07668 ,1.22469 ,1.22469 ,1.22469 ,1.22469 ,1.39747 ,1.39747 ,1.39747 ,1.39747]


	plt.scatter(x_scatter, y_scatter , marker='o', color='g', label='Half time of each curve')
	plt.plot(x_fit, y_fit, color='b', linewidth=1.0, linestyle='--', label="Initial monomer concentration of each curve")

	#plt.text(2, 4,"Scaling exponent = -1.03431 ")
	plt.title('Half-time versus monomer concentration : Scaling exponent = -1.03431', color='r')

	plt.legend(loc='upper right')
	plt.legend().draggable()
	plt.ylabel("Half-time (h)")
	plt.xlabel("Initial monomer concentration")

	plt.show()




	
if __name__ == "__main__":
	plot_log()