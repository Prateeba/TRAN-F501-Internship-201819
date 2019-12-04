import numpy as np
from abc import ABCMeta, abstractmethod
from matplotlib.font_manager import FontProperties
import scipy.optimize
import matplotlib.pyplot as plt


class Optimizer:

	def __init__(self, n_params, n_iter=5000):
		self.n_params = n_params
		self.n_iter = n_iter

	def run(self, obj):

		# Redefine parameter space:
		# [1, 1e+30] -> [0, 30]
		def obj_wrapper(x):
			y = 10. ** x
			return obj(y)

		# Random initial solution
		def random_sol():
			return 30 * np.random.rand(self.n_params)

		# Brute force de ses morts
		evaluations = list()
		for _ in range(self.n_iter):
			x0 = random_sol()
			value = obj_wrapper(x0)
			evaluations.append(list(x0) + [value])
		evaluations = np.asarray(evaluations)
		evaluations = evaluations[~np.isnan(evaluations[:, -1])]

		# Keep best random solution as initial solution
		idx = np.argmin(evaluations[:, -1])
		x0 = evaluations[idx, :-1]

		"""
		# Define bounds
		class BoundsDisplacement:
			def __call__(self, x):
				return np.clip(x, 0., 30.)

		# Run optimizer
		minimizer_kwargs = {
			'method': 'L-BFGS-B',
			# TODO: add jacobian to args
		}
		res = scipy.optimize.basinhopping(
				obj_wrapper,
				x0,
				niter=200,
				minimizer_kwargs=minimizer_kwargs,
				take_step=BoundsDisplacement())
		"""
		return x0

class Model(metaclass=ABCMeta):

	def __init__(self, m_0=1e-6, M_0=0, P_0=0):
		self.m_0 = m_0
		self.M_0 = M_0
		self.P_0 = P_0
		self.m_total = self.m_0 + self.M_0

	def fit(self, y, t):
		def objective(params):
			old_params = self._get_parameters()
			self._set_parameters(params)
			value = self.evaluate(y, t)
			self._set_parameters(old_params)
			return value
		n_params = len(self._get_parameters())
		params = Optimizer(n_params).run(objective)
		self._set_parameters(params)

	def evaluate(self, y, t):
		y_hat = self.simulate(t)
		if len(y.shape) == 2:
			return ((y[..., np.newaxis] - y_hat) ** 2.).mean()
		else:
			return ((y - y_hat) ** 2.).mean()

	@abstractmethod
	def simulate(self, t):
		pass

	@abstractmethod
	def _get_parameters(self):
		pass

	@abstractmethod
	def _set_parameters(self, params):
		pass

class NucleationElongationUnseeded(Model) : 
	def __init__(self, n_c=2, k_plus_k_n=1e+12, **kwargs):
		Model.__init__(self, **kwargs)
		self.n_c = n_c
		self.k_plus_k_n = k_plus_k_n

	def simulate(self,t) : 
		_lambda = np.sqrt(2 * self.k_plus_k_n * self.m_0 ** self.n_c)
		alpha_n = self.k_plus_k_n * self.n_c
		alpha_d = self.k_plus_k_n * self.m_0 ** self.n_c
		alpha = 0
		if not np.isnan(alpha_d) : 
			alpha = np.sqrt(alpha_n/alpha_d) * self.P_0
		mu = np.sqrt(1 + alpha ** 2)
		nu = np.log(alpha + mu)

		R = 1/mu * np.cosh(np.sqrt(self.n_c/2) * mu *_lambda * t + nu) **-2/self.n_c
		R[np.isnan(R)] = 1.
		M = self.m_total * (1 - self.m_0 / self.m_total * (R))
		return M 

	def _get_parameters(self):
		return (self.k_plus_k_n,)

	def _set_parameters(self, params):
		self.k_plus_k_n = params

class SecondaryNucleationUnseeded(Model):
	def __init__(self, n_c=2, n_2=2, k_plus_k_n=1e+12, k_plus_k_2=1e+5, **kwargs):
		Model.__init__(self, **kwargs)
		self.n_c = n_c
		self.n_2 = n_2
		self.k_plus_k_n = k_plus_k_n
		self.k_plus_k_2 = k_plus_k_2

	def simulate(self, t):
		kappa = np.sqrt(2. * (self.m_0 ** (1 + self.n_2))) * np.sqrt(self.k_plus_k_2)
		_lambda = np.sqrt(2. * (self.m_0 ** self.n_c)) * np.sqrt(self.k_plus_k_n)
		C_plus = self.M_0 / (2. * self.m_0)
		if not np.isnan(kappa):
			C_plus += (_lambda ** 2.) / (2. * kappa ** 2.)
		C_minus = -C_plus

		f_inf  = 4. * self.k_plus_k_n * (self.m_0 ** self.n_c) / self.n_c
		f_inf += 4. * self.k_plus_k_2 * self.m_total * (self.m_0 ** self.n_2) / self.n_2
		f_inf += 4. * self.k_plus_k_2 * (self.m_0 ** (self.n_2 + 1)) / (self.n_2 + 1)
		k_inf = np.sqrt(f_inf)

		k_bar_inf = np.sqrt((k_inf ** 2.) - 2. * C_plus * C_minus * (kappa ** 2.))
		B_plus = (k_inf + k_bar_inf) / (2. * kappa)
		B_minus = (k_inf - k_bar_inf) / (2. * kappa)
		M_inf = self.m_total
		R = (B_minus + C_plus * np.exp(kappa * t)) / (B_plus + C_plus * np.exp(kappa * t))
		R[np.isnan(R)] = 1.
		M = M_inf * (1. - (1. - self.M_0 / M_inf) * np.exp(-k_inf * t) * (R * \
				(B_plus + C_plus) / (B_minus + C_plus)) ** (k_inf / (kappa * k_bar_inf)))
		return M

	def _get_parameters(self):
		return (self.k_plus_k_n, self.k_plus_k_2)

	def _set_parameters(self, params):
		self.k_plus_k_2, self.k_plus_k_n = params

class FragmentationUnseeded(Model): 
	def __init__(self, n_c=2, k_plus_k_n=1e+7, k_plus_k_minus=1e+5, **kwargs):
		Model.__init__(self, **kwargs)
		self.n_c = n_c
		self.k_plus_k_n = k_plus_k_n
		self.k_plus_k_minus = k_plus_k_minus

	def simulate(self, t) : 
		sigma = self.k_plus_k_n * self.m_0 ** self.n_c + self.k_plus_k_minus * self.M_0
		kappa = np.sqrt(2 * self.k_plus_k_n*self.m_0*self.k_plus_k_minus)
		M_inf = self.m_total/self.k_plus_k_n

		left = self.k_plus_k_n * (4 * sigma * kappa *np.cosh(kappa*t))
		right = 4 * self.P_0*kappa**2 * np.sinh(kappa*t)
		exp = np.exp(-(left + right / 2*kappa**3)) 
		exp[np.isnan(exp)] = 1.

		M_t = M_inf + exp * (self.M_0 - M_inf) * np.exp(2*kappa + sigma / kappa**2)
		return M_t

	def _get_parameters(self):
		return (self.k_plus_k_n, self.k_plus_k_minus)

	def _set_parameters(self, params):
		self.k_plus_k_n, self.k_plus_k_minus = params

def load_file(filepath):
	with open(filepath, 'r') as f:
		data = list()
		lines = f.readlines()
		if 'time' in lines[0]:
			line = lines[0].rstrip()
			header = line.split('\t')
			lines = lines[1:]
		else:
			header = None
		for line in lines:
			elements = line.rstrip().split('\t')
			data.append([float(el) for el in elements])
		data = np.asarray(data)
	return header, data

if __name__ == '__main__':

	# Load the data
	header, data = load_file('nprot.2016.010-S2.txt')
	t = data[:, 0]        # time 
	obs = data[:, 15]     # Observation

	# Define relative aggregate concentration as the observed
	obs /= obs[-1, :]

	# ASSUMPTION: m_total == M_inf
	y = obs[:, 1]
	y_end = obs[:, -1]
	m_total = y_end[-1]

	# Initial fibril mass concentration
	M_0 = y[0]

	# Initial monomer concentration
	m_0 = m_total - M_0

	# Create the model
	model = SecondaryNucleationUnseeded(m_0=m_0, M_0=M_0)

	# Fit the data
	model.fit(obs, t)

	# Simulate the model
	M = model.simulate(t)

	# Display the results
	plt.plot(t, M, label='fit')
	colors = iter(plt.cm.rainbow(np.linspace(0, 1, obs.shape[1])))
	for k in range(obs.shape[1]):
		c = next(colors)
		plt.scatter(t, obs[:, k], marker='o', c=c)

	fontP = FontProperties()
	fontP.set_size('x-small')
	plt.legend(loc='upper left', prop=fontP, bbox_to_anchor=(0.5, 1.00),ncol=3, fancybox=True, shadow=True)
	plt.ylabel('Relative aggregate concentration')
	plt.xlabel('Time')

	plt.text(0.9, 0.1, 'Optimal k_plus_k_n: '+str(model.k_plus_k_n), fontsize=10)
	plt.text(0.9, 0.2, 'Optimal k_plus_k_2: '+str(model.k_plus_k_2), fontsize=10)

	print('\n' * 7)
	print('Optimal k_plus_k_n: ', model.k_plus_k_n)
	print('Optimal k_plus_k_minus: ', model.k_plus_k_2)
	print('Mean square : ', model.evaluate(obs, t))

	plt.savefig('results/SecondaryNucleationUnseeded.png')
	plt.show()
	
