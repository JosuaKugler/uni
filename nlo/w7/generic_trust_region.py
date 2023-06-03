import numpy as np
from example_functions import rosenbrock
from steihaug_Toint_CG import steihaug_Toint_CG

def generic_trust_region(x0, f, f_prime, H_routine, M_inverse, Delta_0, eta_1, eta_2, gamma_1, gamma_2):
    k = 0
    x = x0
    f = f(x)
    Delta = Delta_0
    while k < 100:
        H = H_routine(k)
        s, pred, s_m_norm = steihaug_Toint_CG(H, -f_prime(x), M_inverse, eps_rel=1e-4, Delta=Delta)
        x_new = x + s
        f_new = f(x_new)
        ared = f_new - f
        rho = ared/pred
        if rho >= eta_1:
            x = x_new
            f = f_new
            if rho >= eta_2 and s_m_norm == Delta:
                Delta = gamma_2 * Delta
        else:
            Delta = gamma_1 * s_m_norm
        k = k + 1

    return x

