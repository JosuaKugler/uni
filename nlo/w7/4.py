import numpy as np
from generic_trust_region import generic_trust_region
from example_functions import rosenbrock

a = 1
b = 100
rosenbrock_f = lambda x: rosenbrock(a, b, x)[0]
rosenbrock_prime = lambda x: rosenbrock(a, b, x)[1]
rosenbrock_two_prime = lambda x: rosenbrock(a, b, x)[2]

x0 = [0,0]

generic_trust_region(
    x0,
    rosenbrock_f,
    rosenbrock_prime,
    lambda _: np.eye(2),
    np.eye(2),
    Delta_0=1,
    eta_1=0.3,
    eta_2=0.7,
    gamma_1=.5,
    gamma_2=2,
)
