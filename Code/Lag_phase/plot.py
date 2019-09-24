# FILENAME: plot.py
import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
 
def plot_data(data1, data2):
	colors = ['r', 'b', 'm', 'g', 'c', 'y', 'k']
	labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
	markers =['o', '8', '*', '^', 'P', 'd', 'X' ] 
	
	plt.scatter(np.log10(data1), data2, marker=markers[0])


	plt.legend(loc='upper left')
	plt.ylabel("250uM Y")
	plt.xlabel("Time")

	plt.show()
 
if __name__ == "__main__":
	counter = 0
	n = 250 
	data_time = []
	data_elem = []
	while counter < n:
		try:
			tmp = input().strip().split(" => ")
			if (len(tmp) > 1) : 
 				data_time.append(float(tmp[0]))
 				data_elem.append(float(tmp[1])) 
		except EOFError:
			print("Input has terminated! Exiting")
			exit()
		except ValueError:
			print("Invalid input, skipping.  Input was: %s"%tmp)
			continue
		counter += 1

	plot_data(data_time, data_elem)