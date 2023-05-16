import numpy as np
from armijo_procedures import armijo_backtracking

def globalized_newton_UP(
    x_0, f, f_prime, f_two_prime, M, sigma, eta, rho, p, beta, eps=1e-5, max_iter=100
):
    """
    Implements Algorithm 5.30
    """
    M_inv = np.linalg.inv(M)

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
        solvable = True
        try:
            d_N = np.linalg.solve(f_two_prime(x), -r)
        except:
            solvable = False
            d = d_G
        if solvable:
            if np.dot(f_prime(x), d_N) <= - min(eta, rho * np.linalg.norm(d_G)**p) * np.sqrt(delta) * np.sqrt(d_N.T @ M @ d_N): #Mnorm of d_N
                d = d_N
            else:
                d = d_G

        phi = lambda alpha: f(x + alpha * d)
        phi_0 = f_k  # f(x + 0*d) = f(x)
        phi_prime_0 = -delta
        
        alpha = armijo_backtracking(1, phi, phi_0, phi_prime_0, sigma, beta) #initial trial step size is 1

        x = x + alpha * d
        f_k = f(x)
        r = f_prime(x)
        d = -M_inv @ r
        delta = -r.transpose() @ d
        k = k + 1

        history["step_lengths"].append(alpha)
        history["iterates"].append(x)
        history["objective_values"].append(f_k)
        history["gradient_norms"].append(np.sqrt(delta))

    return history