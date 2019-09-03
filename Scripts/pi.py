import numpy as np 
import matplotlib.pyplot as plt 

n = 100000000 # the number of points
x = np.random.rand(n, 2) # Create an array of the given shape and populate it with random samples from a uniform distribution over [0, 1]

inside = x[np.sqrt(x[:,0]**2 + x[:,1]**2) < 1] 
estimate = 4*len(inside)/len(x)

print('Estimate of pi : {}'.format(estimate))
plt.figure(figsize=(8,8))
plt.scatter(x[:,0], x[:,1], s=.5, c='red') 
plt.scatter(inside[:,0], inside[:,1], s=.5, c='blue') 
plt.show()