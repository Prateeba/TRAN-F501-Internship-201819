from networkx.drawing.nx_agraph import write_dot, graphviz_layout
import matplotlib.pyplot as plt
import networkx as nx
import numpy as np


class pseudo_dependency_graph:

	""" ############### Methods used for the minimum tree ###############""" 
	def __init__(self,initial_node, color) :
		self.initial_node = initial_node
		self.current_node = initial_node
		self.color = color 
		self.create_graph() 

	def create_graph(self):
		self.G = nx.DiGraph()
		self.G.add_node(self.initial_node,color=self.color,style='filled',fillcolor=self.color, time=0)
		
		#self.G.add_edge(self.edges[i][0], self.edges[i][1], weight=self.edges[i][2])
		#self.draw_graph(self.G)

	def get_graph(self) : 
		return self.G

	def set_current_node(self, n1) :
		self.current_node = n1  
		
	def add_edge_to_graph(self, n1, n2, w, t) :
		""" 
		* n1 = source node 
		* n2 = destination node 
		* w  = weight
		"""    
		self.G.add_node(n1,color=self.color,style='filled',fillcolor=self.color, time=t)  
		self.G.add_node(n2,color=self.color,style='filled',fillcolor=self.color, time=t)  
		self.G.add_edge(n1, n2, weight=w)
	
	def get_weight(self,n1,n2) :
		if (self.G.has_edge(n1, n2)): 
			return self.G.get_edge_data(n1, n2)['weight']
		else : 
			return 0


	def update(self, operation, operand, reaction_parameter, t) : 
		name = self.current_node
		if (name != " ") : 
			if (operation == "+") :
				n2 = name + self.initial_node*operand
				self.set_current_node(n2) 
				self.add_edge_to_graph(name,n2, reaction_parameter, t)
			
			elif (operation == "-") : 
				if len(self.current_node) <= operand : 
					n2 = " "
					self.set_current_node(n2) 
					self.add_edge_to_graph(name,n2, reaction_parameter, t)
				else : 
					n2 = self.initial_node*(len(self.current_node)-operand)
					self.set_current_node(n2) 
					self.add_edge_to_graph(name,n2, reaction_parameter, t)


	def draw_graph(self) :
		weights = nx.get_edge_attributes(self.G,'weight')     
		colours = nx.get_node_attributes(self.G,'color')
		c = list(colours.values()) 
		pos =graphviz_layout(self.G, prog='dot')
		nx.draw(self.G, pos, node_size = 3000, node_color = c,with_labels=True, arrows=True)
		nx.draw_networkx_edge_labels(self.G,pos,edge_labels=weights)   
		plt.show()

