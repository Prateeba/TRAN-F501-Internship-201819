import math
import random 
import numpy as np 
import networkx as nx
import matplotlib.pyplot as plt
from pseudo_dependency_graph import pseudo_dependency_graph
 

class Eq_33(object):
	def __init__(self, C, D, T, W, X, Y, Z, T2, TINT) : 
		""" STEP 0 """
		self.C = C                             # Reaction parameters 
		self.D = D                             # Dimension of the arrays 
		self.T = T                             # initial time 
		self.W = W                             # number of molecules W at time T 
		self.X = X                             # number of molecules X at time T 
		self.Y = Y                             # number of molecules Y at time T 
		self.Z = Z                             # number of molecules Z at time T 
		self.T2 = T2                           # stopping time  
		self.TINT = TINT                       # time interval 
		self.TPRINT = self.T                   # Print out time
		self.A = [0]*self.D                    # quantities for the molecular population 
 
		# for plotting 
		self.w_plot = []
		self.x_plot = []
		self.y_plot = []
		self.z_plot = []                         
		self.t_plot = []     

		#pseudo_dependency_graph
		self.w_graph = pseudo_dependency_graph("W", 'r')
		self.x_graph = pseudo_dependency_graph("X", 'b') 
		self.y_graph = pseudo_dependency_graph("Y", 'y') 
		self.z_graph = pseudo_dependency_graph("Z", 'g')                  

	def compute_reactions(self) : 
		self.A[0] = self.C[0]*self.Y
		self.A[1] = self.C[1]*self.Y
		self.A[2] = self.C[2]*self.X*(self.X-1)/2
		self.A[3] = self.C[3]*self.Z
		self.A[4] = self.C[4]*self.W*self.X
		self.A[5] = self.C[5]*self.X*(self.X-1)/2 
		self.A0   = self.A[0] + self.A[1] + self.A[2] + self.A[3] + self.A[4] + self.A[5]

		
	def simulate(self) : 
		
		while (self.T < self.T2) : 
		
			self.compute_reactions() 
			r = np.random.rand(2, 1)                 # CALL URN(R1, R2) -- Uniform distribution
			tau = -math.log(r[0])/self.A0            # Calculate the dt 
			self.T += tau                            # update time according to dt
			
			if (self.T < self.TPRINT) : 
				R2A0 = r[1]*self.A0 
				SUM = 0 

				NU = random.randint(1,6)
				MU = NU 
				SUM += self.A[NU-1]

				if (SUM > R2A0) : 
					if (MU == 1) :
						self.X -= 1 
						self.Y += 1 

					if (MU == 2) : 
						self.X += 1
						self.Y -= 1 
					
					if (MU == 3) : 
						self.X -= 2 
						self.Z += 1 
					
					if (MU == 4) :
						self.X += 2 
						self.Z -= 1 
					
					if (MU == 5) :
						self.X += 1 
						self.W -= 1 
					
					if (MU == 6) :
						self.X -= 1 
						self.W += 1 
			else : 
				# print the results
				self.w_plot.append(self.W)
				self.x_plot.append(self.X)
				self.y_plot.append(self.Y)
				self.z_plot.append(self.Z)                       
				self.t_plot.append(self.TPRINT) 

				self.TPRINT += self.TINT
		self.plot()
		
	def plot(self) : 
		
		plt.plot(self.t_plot, self.w_plot, marker='o', color='r', label='W species')
		plt.plot(self.t_plot, self.x_plot, marker='v', color='b', label='X species')
		plt.plot(self.t_plot, self.y_plot, marker='*', color='y', label='Y species')
		plt.plot(self.t_plot, self.z_plot, marker='^', color='g', label='Z species')


		plt.legend(loc='upper left')
		plt.ylabel("Number of molecules")
		plt.xlabel("Time")

		plt.show()
		

if __name__ == '__main__':
	C = [random.randint(1,6), random.randint(1,6), random.randint(1,6), random.randint(1,6), random.randint(1,6), random.randint(1,6)]
	eq33 = Eq_33(C, 6, 0, 1, 1, 1, 1, 20, 0.5)
	eq33.simulate()