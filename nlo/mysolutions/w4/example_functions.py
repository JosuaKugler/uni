import numpy as np

def rosenbrock(a,b,x):	
	"""
	Implements the rosenbrock function
	Accepts:
		       a,b: scalar parameters
		       x: array of length 2
	Returns: 
		       f:  function value
		       df: derivative value
	"""
	f  = (a - x[0])**2 + b * (x[1] - x[0]**2)**2
	df = np.array(
		[2*(a - x[0]) + 2*b*(x[1] - x[0]**2)*(-2*x[0]),
		 2*b*(x[1] - x[0]**2)
		]
		)
	return f, df

def himmelblau(x):
	f = (x[0]**2 + x[1]-11)**2 + (x[0]+x[1]**2-7)**2
	df = 0 #if I have some spare time maybe I'll compute it