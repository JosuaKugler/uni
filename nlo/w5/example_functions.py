import numpy as np

class rand_problem():
    def __init__(self, n) -> None:
        self.n = n
        self.A = self.create_random_A()
        self.b = np.random.rand(n)
        self.c = np.random.rand()
        self.f = self.quadratic_function()
        self.f_prime = lambda x : self.A @ x - self.b
        self.Pinv = np.identity(n)

        self.x0 = np.random.rand(n)
    
    def create_random_A(self):
        """create random spd matrix in dimension n x n"""
        M = np.random.rand(self.n,self.n)
        return np.dot(M, M.T)
    
    def quadratic_function(self):
        f = lambda x : 0.5 * x.T @ self.A @ x - self.b.T @ x + self.c
        return f

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
		[-2*(a - x[0]) + 2*b*(x[1] - x[0]**2)*(-2*x[0]), 2*b*(x[1] - x[0]**2)]
          )
	ddf = np.array(
             [[2 - 4*b*x[1] + 12*b*x[0]**2, -4*b*x[0]],
              [-4*b*x[0], 2*b]]
                 )
	return f, df, ddf

def himmelblau(x):
	f = (x[0]**2 + x[1]-11)**2 + (x[0]+x[1]**2-7)**2
	df = 0 #if I have some spare time maybe I'll compute it