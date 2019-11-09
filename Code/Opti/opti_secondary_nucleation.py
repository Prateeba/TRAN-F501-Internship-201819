from pyomo.environ import *
from pyomo.dae import *
import math

m = AbstractModel()
m.t = ContinuousSet()   
m.MEAS_t = Set(within=m.t)  # Measurement times, must be subset of t

m.x1_meas = Param(m.MEAS_t) # m(t)

m.x1 = Var(m.t,within=PositiveReals) # m(t)

m.k1 = Var(within=PositiveReals, bounds=(1000,math.inf)) # kn 

m.x1dot = DerivativeVar(m.x1,wrt=m.t)

def _init_conditions(m):
	yield m.x1[0] == 0.000001
m.init_conditions=ConstraintList(rule=_init_conditions)

def _x1dot(m,i):
	if i==0:
		return Constraint.Skip
	return m.x1dot[i] == m.k1*m.x1[i]**2
m.x1dotcon = Constraint(m.t, rule=_x1dot)

def _obj(m):
	return sum((m.x1[i]-m.x1_meas[i])**2 for i in m.MEAS_t)
m.obj = Objective(rule=_obj)

m.pprint()

instance = m.create_instance('exp2.dat')
instance.t.pprint()

discretizer = TransformationFactory('dae.collocation')
discretizer.apply_to(instance,nfe=30)#,ncp=3)

solver=SolverFactory('ipopt')

results = solver.solve(instance,tee=True)


instance.k1.pprint()

#print(instance.k1.value * instance.k2.value)
