import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from pseudo_dependency_graph import pseudo_dependency_graph
 

class Secondary_nucleation(object):
	def __init__(self, C, D, T, M, P, F, S, T2, TINT) : 
		""" STEP 0 """
		self.C = C                             # Reaction parameters 
		self.D = D                             # Dimension of the arrays 
		self.T = T                             # initial time 
		self.M = M                             # number of Monomers at time T 
		self.P = P                             # number of Primary nuclei at time T 
		self.F = F                             # number of fibril ends at time T 
		self.S = S                             # number of secondary nucleations at time T 
		self.T2 = T2                           # stopping time  
		self.TINT = TINT                       # time interval 
		self.TPRINT = self.T                   # Print out time
		self.A = [0]*self.D                    # quantities for the molecular population 
 
		# for plotting 
		self.m_plot = []
		self.p_plot = []
		self.f_plot = []
		self.s_plot = []                         
		self.t_plot = []     
                 

	def compute_reactions(self) : 
		self.A[0] = self.C[0]*self.M
		self.A[1] = self.C[1]*self.M
		self.A[2] = self.C[2]*self.M
		self.A[3] = self.C[3]*self.M
		self.A0   = self.A[0] + self.A[1] + self.A[2] + self.A[3] 
		
	def simulate(self) : 
		
		while (self.T < self.T2) : 
		
			self.compute_reactions() 
			r = np.random.rand(2, 1)                 # CALL URN(R1, R2) -- Uniform distribution
			tau = -math.log(r[0])/self.A0            # Calculate the dt 
			self.T += tau                            # update time according to dt
			print(self.T)
			if (self.T < self.TPRINT) : 
				R2A0 = r[1]*self.A0 
				SUM = 0 

				NU = random.randint(1,4)
				MU = NU 
				SUM += self.A[NU-1]

				if (SUM > R2A0) : 
					if (MU == 1) :
						self.M -= 1 
						self.P += 1 

					if (MU == 2) : 
						self.M -= 1
						self.F += 1 
					
					if (MU == 3) : 
						self.M -= 1 
						self.S += 1 
					
					if (MU == 4) :
						self.M -= 1 
						self.F += 1 
			else : 
				# print the results
				self.m_plot.append(self.M)
				self.p_plot.append(self.P)
				self.f_plot.append(self.F)
				self.s_plot.append(self.S)                       
				self.t_plot.append(self.TPRINT) 

			self.TPRINT += self.TINT
		#self.plot()
		self.output_plot() 
		
	"""def plot(self) : 
		
		plt.plot(self.t_plot, self.w_plot, marker='o', color='r', label='W species')
		plt.plot(self.t_plot, self.x_plot, marker='v', color='b', label='X species')
		plt.plot(self.t_plot, self.y_plot, marker='*', color='y', label='Y species')
		plt.plot(self.t_plot, self.z_plot, marker='^', color='g', label='Z species')


		plt.legend(loc='upper left')
		plt.ylabel("Number of molecules")
		plt.xlabel("Time")

		plt.show() """

	def output_plot(self) : 
		print(self.t_plot)
		with open('m.txt', 'a') as f:
			for item in self.m_plot : 
				f.write("%s " % item)
			f.write("\n")
		with open('p.txt', 'a') as f:
			for item in self.p_plot : 
				f.write("%s " % item)
			f.write("\n")
		with open('f.txt', 'a') as f:
			for item in self.s_plot : 
				f.write("%s " % item)
			f.write("\n")
		with open('s.txt', 'a') as f:
			for item in self.f_plot : 
				f.write("%s " % item)
			f.write("\n")

	def get_t_plot(self) : 
		return self.t_plot 
	def get_m_plot(self) : 
		return self.m_plot
	def get_p_plot(self) :
		return self.p_plot
	def get_f_plot(self) :
		return self.f_plot
	def get_s_plot(self) :
		return self.s_plot   
		

if __name__ == '__main__':
	i = 0
	n = 5
	C = [4, 4, 9, 9]
	eq33 =  Secondary_nucleation(C, 4, 0, 10000, 100, 100, 100, 0.1,1)
	while (i < n ) : 
		eq33.simulate()
		print(i)
		i+= 1 


	