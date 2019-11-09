from lmfit import minimize, Parameters, Parameter, report_fit
from scipy.integrate import odeint
from sklearn import preprocessing
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

## Trial for NUCLEATION ELONGATION, UNSEEDED 

def f(y, t, paras):
    """
    Your system of differential equations
    """
    x1 = y[0]     #mt -> m0
    x2 = y[1]     #Pt -> 0(for unseeded)
    try:
        kn = paras['kn'].value
        kplus = paras['kplus'].value

    except KeyError:
        kn, kplus = paras
    # the model equations
    f0 = kn * (x1**2) 
    f1 = kplus *x2 * x1 
    return [f0, f1]

def g(t, x0, paras):
    """
    Solution to the ODE x'(t) = f(t,x,k) with initial condition x(0) = x0
    """
    x = odeint(f, x0, t, args=(paras,))
    print(x)
    return x

def residual(paras, t, data):
    """
    compute the residual between actual data and fitted data
    """
    x0 = paras['x10'].value, paras['x20'].value
    model = g(t, x0, paras)

    # you only have data for one of your variables
    x2_model = model[:, 1]
    return (x2_model - data).ravel()


# initial conditions
x10 = 1e-6   #m0
x20 = 1      #Pt
y0 = [x10, x20]

# measured data
df = pd.read_csv("b.csv", sep=",", skiprows=1, usecols=[0,1], names=['TIME','CONC'])
t_measured = np.array(df["TIME"])
x2_measured = np.array(df["CONC"])


plt.figure()
plt.scatter(t_measured, x2_measured, marker='o', color='b', label='measured data', s=75)

# set parameters including bounds; you can also fix parameters (use vary=False)
params = Parameters()
params.add('x10', value=x10, vary=True)
params.add('x20', value=x20, vary=True)
params.add('kn', value=1000)
params.add('kplus', value=1000)

# fit model
result = minimize(residual, params, args=(t_measured, x2_measured), method='basinhopping', nan_policy='omit')  # leastsq nelder
# check results of the fit
data_fitted = g(t_measured, y0, result.params)

# plot fitted data
plt.plot(t_measured, data_fitted[:, 1], '-', linewidth=2, color='red', label='fitted data')
plt.legend()
plt.xlim([0, max(t_measured)])
plt.ylim([0, 1.1 * max(data_fitted[:, 1])])

# display fitted statistics
report_fit(result)

plt.show()