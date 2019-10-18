# FILENAME: plot.py
import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
 
def plot_data(data1, data2, data3):
	colors = ['r', 'b', 'm', 'g', 'c', 'y', 'k']
	labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
	markers =['o', '8', '*', '^', 'P', 'd', 'X' ] 

	for i in range(len(data2)) : 
		plt.scatter(list(map(float, data1)), list(map(float, data2[i])) , marker=markers[1], label=data3[i])


	plt.legend(loc='upper left')
	plt.legend().draggable()
	plt.ylabel("Fluorescence")
	plt.xlabel("Time (h)")

	plt.show()

def data_process() : 
	counter = 0
	n = 41
	data_time = []
	data_elem = []
	handles = []
	while counter < n:
		try:
			tmp = input().strip().split(" ")
			print(len(tmp))
			if ("=>" in tmp) : 
				index = tmp.index("=>")
				data_time = tmp[0 : index]	
				data_elem.append(tmp[index+1 :len(tmp)-1])
			else : 
				handles = tmp
		except EOFError:
			print("Input has terminated! Exiting")
			exit()
		except ValueError:
			print("Invalid input, skipping.  Input was: %s"%tmp)
			continue
		counter += 1

	data_time.pop(len(data_time)-1)
	plot_data(data_time, data_elem, handles)

 
if __name__ == "__main__":

	data_process()
	