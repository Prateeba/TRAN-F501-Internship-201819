import scipy.optimize as opt
from numpy import exp

def f(variables) :
    (x,y) = variables

    first_eq = 1000*x**2
    second_eq = 1000*x*y
    return [first_eq, second_eq]

solution = opt.fsolve(f, (0.00001,0) )
print(solution)


