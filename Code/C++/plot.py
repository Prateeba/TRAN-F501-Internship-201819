# FILENAME: plot.py
import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
 
def plot_data(data):
	colors = ['r', 'b', 'm', 'g', 'c', 'y', 'k']
	labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
	markers =['o', '8', '*', '^', 'P', 'd', 'X' ] 
	for i in range(len(data)-1) : 
		plt.plot(data[0], data[i+1],marker=markers[i] ,color=colors[i], label=labels[i]+' species')


	plt.legend(loc='upper left')
	plt.ylabel("Number of molecules")
	plt.xlabel("Time")

	plt.show()
 
if __name__ == "__main__":
	counter = 0
	n_species = 7 
	data = []
	while counter < n_species:
		try:
			tmp = input().strip().split()
			data.append(tmp) 
			#data = np.array(tmp, dtype=np.double)
		except EOFError:
			print("Input has terminated! Exiting")
			exit()
		except ValueError:
			print("Invalid input, skipping.  Input was: %s"%tmp)
			continue
		counter += 1

	plot_data(data)