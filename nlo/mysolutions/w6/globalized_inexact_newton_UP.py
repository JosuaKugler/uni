import numpy as np
from armijo_procedures import armijo_backtracking
from truncated_CG import truncated_CG

def globalized_inexact_newton_UP(
    x_0, f, f_prime, f_two_prime, M_inv, eta_k, sigma, eta, rho, p, beta, eps=1e-5, max_iter=100
):
    """
    Implements Algorithm 5.30
    """
    debug = False

    k = 0
    f_k = f(x_0)
    r = f_prime(x_0)
    d_G = -M_inv @ r
    delta = -r.transpose() @ d_G
    history = {
        "iterates": [x_0],
        "objective_values": [f_k],
        "gradient_norms": [np.sqrt(delta)],
        "step_lengths": [],
    }
    x = x_0
    while delta > eps**2 and k < max_iter:
        
        if debug == True:
            print(f'solve {f_two_prime(x)} * x = {-r}')
        #d_N = np.linalg.solve(f_two_prime(x), -r) #exact
        d_N, d_N_norm_squared = truncated_CG(f_two_prime(x), -r, M_inv, eps_rel=eta_k(k)) #inexact

        if np.dot(f_prime(x), d_N) <= - min(eta, rho * np.linalg.norm(d_G)**p) * np.sqrt(delta) * np.sqrt(d_N_norm_squared):
            d = d_N
        else:
            d = d_G

        phi = lambda alpha: f(x + alpha * d)
        phi_0 = f_k  # f(x + 0*d) = f(x)
        phi_prime_0 = -delta
        
        if debug == True:
            case = ''
            if np.array_equiv(d, d_G):
                case = 'gradient'
            elif np.array_equiv(d, d_N):
                case = 'newton'
            else:
                case = 'bug!'
            print(f'{case}, phi_0={phi_0}, phi_prime_0={phi_prime_0} at x={x} and d={d}')
        alpha = armijo_backtracking(1, phi, phi_0, phi_prime_0, sigma, beta) #initial trial step size is 1

        x = x + alpha * d
        f_k = f(x)
        r = f_prime(x)
        d_G = -M_inv @ r
        delta = -r.transpose() @ d_G
        k = k + 1

        history["step_lengths"].append(alpha)
        history["iterates"].append(x)
        history["objective_values"].append(f_k)
        history["gradient_norms"].append(np.sqrt(delta))

    return history