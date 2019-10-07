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

	for i in data2 : 
		plt.scatter(list(map(float, data1)), list(map(float, i)) , marker=markers[1])
	#plt.scatter(np.log10(data1), data2, marker=markers[0])
	

	plt.legend(loc='upper left')
	plt.ylabel("250uM Y")
	plt.xlabel("Time")

	plt.show()

def data_process() : 
	counter = 0
	n = 10
	data_time = []
	data_elem = []

	while counter < n:
		try:
			tmp = input().strip().split(" ")
			index = tmp.index("=>")
			data_time = tmp[0 : index]	
			data_elem.append(tmp[index+1 :len(tmp)-1])
		except EOFError:
			print("Input has terminated! Exiting")
			exit()
		except ValueError:
			print("Invalid input, skipping.  Input was: %s"%tmp)
			continue
		counter += 1

	data_time.pop(len(data_time)-1) #!!!!!!!!!!!!!! TO CHANGE !!!!!!!!!!!!!!! 

	plot_data(data_time, data_elem)

	
def plot_data_nprot(data) : 
	""" Plot raw data provided by c++ program with any preprocessing """

	x = []                     # contains the time steps 
	y = []
	for i in range(len(data)) : 
		x.append(data[i][0])


	for i in range(len(data)): # contains the data   
		data[i].pop(0)
		y.append(data[i]) 

	for xe, ye in zip(x, y):
		plt.scatter([xe] * len(ye), ye)

	plt.legend(loc='upper left')
	plt.ylabel("uM ")
	plt.xlabel("Time")

	plt.show()

def data_process_nprot() : 
	counter = 0
	n = 10
	data = []
	# Header is removed when normalizing 
	#tmp = input().strip().split(" ")
	while counter < n:
		try:
			tmp = input().strip().split(" ")
			tmp_tmp = [float(i) for i in tmp]
			data.append(tmp_tmp)
		except EOFError:
			print("Input has terminated! Exiting")
			exit()
		except ValueError:
			print("Invalid input, skipping.  Input was: %s"%tmp)
			continue
		counter += 1

	plot_data_nprot(data)
 
if __name__ == "__main__":

	data_process()
	