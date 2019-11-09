from scipy.optimize import basinhopping
import matplotlib.pyplot as plt
import scipy.optimize as opt
import scipy.stats as stats
import numpy as np
import math 


def func2d(x, n):
	f = np.cos(14.5 * x[0] - 0.3) + (x[1] + 0.2) * x[1] + (x[0] +0.2) * x[0]
	df = np.zeros(2)
	df[0] = -14.5 * np.sin(14.5 * x[0] - 0.3) + 2. * x[0] + 0.2
	df[1] = 2. * x[1] + 0.2*n
	return f,df

minimizer_kwargs = {"method":"L-BFGS-B", "jac":True}
x0 = [1.0, 1.0]
n = 1000
ret = basinhopping(func2d, x0, minimizer_kwargs=minimizer_kwargs,niter=200)
print("global minimum: x = [%.4f, %.4f], f(x0) = %.4f" % (ret.x[0],ret.x[1],ret.fun))