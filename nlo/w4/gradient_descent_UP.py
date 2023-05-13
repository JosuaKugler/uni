import numpy as np
from armijo_procedures import armijo_backtracking, armijo_interpolation

def gradient_descent_UP(
    x_0, f, f_prime, M_inv, sigma, alpha_lower_bound, beta, beta_upper=None, eps=1e-5, max_iter=100
):
    """
    if beta_upper is given, we use the interpolating armijo algorithm with beta as beta_lower,
    otherwise the original armijo algorithm
    """

    interpolate = False
    if beta_upper:
        interpolate = True
        beta_lower = beta

    k = 0
    f_new = f(x_0)
    r = f_prime(x_0)
    d = -M_inv @ r
    delta = -r.transpose() @ d
    history = {
        "iterates": [x_0],
        "objective_values": [f_new],
        "gradient_norms": [np.sqrt(delta)],
        "step_lengths": [],
    }
    x = x_0
    while delta > eps**2 and k < max_iter:
        if k == 0:
            alpha_0 = alpha_lower_bound
        else:
            alpha_0 = max(alpha_lower_bound, (f_new - f_old) / delta)
        phi = lambda alpha: f(x + alpha * d)
        phi_0 = f_new  # f(x + 0*d) = f(x)
        phi_prime_0 = -delta
        if interpolate:
            alpha = armijo_interpolation(
                alpha_0, phi, phi_0, phi_prime_0, sigma, beta_lower, beta_upper
            )
        else:
            alpha = armijo_backtracking(alpha_0, phi, phi_0, phi_prime_0, sigma, beta)

        x = x + alpha * d
        f_old = f_new
        f_new = f(x)
        r = f_prime(x)
        d = -M_inv @ r
        delta = -r.transpose() @ d
        k = k + 1

        history["step_lengths"].append(alpha)
        history["iterates"].append(x)
        history["objective_values"].append(f_new)
        history["gradient_norms"].append(np.sqrt(delta))

    return history