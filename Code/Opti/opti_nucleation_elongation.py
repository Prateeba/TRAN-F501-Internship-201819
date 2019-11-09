from pyomo.environ import *
from pyomo.dae import *
import math

m = AbstractModel()
m.t = ContinuousSet()   
m.MEAS_t = Set(within=m.t)  # Measurement times, must be subset of t

m.x1_meas = Param(m.MEAS_t) # m(t)
m.x2_meas = Param(m.MEAS_t) # p(t)

m.x1 = Var(m.t,within=PositiveReals) # m(t)
m.x2 = Var(m.t,within=PositiveReals) # p(t)


m.k1 = Var(within=PositiveReals, bounds=(1000,math.inf)) # kn 
m.k2 = Var(within=PositiveReals, bounds=(1000,math.inf)) # kplus

m.x1dot = DerivativeVar(m.x1,wrt=m.t)
m.x2dot = DerivativeVar(m.x2,wrt=m.t)

def _init_conditions(m):
	yield m.x1[0] == 0.000001
	yield m.x2[0] == 0.00
m.init_conditions=ConstraintList(rule=_init_conditions)


def _x1dot(m,i):
	if i==0:
		return Constraint.Skip
	return m.x1dot[i] == m.k1*m.x1[i]**2
m.x1dotcon = Constraint(m.t, rule=_x1dot)

def _x2dot(m,i):
	if i==0:
		return Constraint.Skip
	return m.x2dot[i] ==  m.k2*m.x1[i]*m.x2[i]
m.x2dotcon = Constraint(m.t, rule=_x2dot)


def _obj(m):
	return sum((m.x1[i]-m.x1_meas[i])**2+(m.x2[i]-m.x2_meas[i])**2 for i in m.MEAS_t)
m.obj = Objective(rule=_obj)

m.pprint()

instance = m.create_instance('exp.dat')
instance.t.pprint()

discretizer = TransformationFactory('dae.collocation')
discretizer.apply_to(instance,nfe=30)#,ncp=3)

solver=SolverFactory('ipopt')

results = solver.solve(instance,tee=True)

instance.x1.pprint() 
instance.x2.pprint() # P 

instance.k1.pprint()
instance.k2.pprint()

print(instance.k1.value * instance.k2.value)
