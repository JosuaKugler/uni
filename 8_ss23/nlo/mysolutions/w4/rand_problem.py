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
    
if __name__ == "main":
    x = rand_problem(4)
    print(x.A, x.b, x.c)