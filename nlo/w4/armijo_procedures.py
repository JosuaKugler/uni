"""
define armijo algorithms to find a suitable step size
"""

def armijo_condition(alpha, phi_alpha, phi_0, phi_prime_0, sigma):
    """evaluate armijo condition"""
    return phi_alpha <= phi_0 + sigma * alpha * phi_prime_0


def armijo_backtracking(alpha_0, phi, phi_0, phi_prime_0, sigma, beta):
    """
    return a step size alpha that satisfies the armijo condition
    using the simple backtracking approach
    """
    alpha = alpha_0
    while not armijo_condition(alpha, phi(alpha), phi_0, phi_prime_0, sigma):
        alpha = beta * alpha
    return alpha

def armijo_interpolation(alpha_0, phi, phi_0, phi_prime_0, sigma, beta_lower, beta_upper):
    """
    return a step size alpha that satisfies the armijo condition
    use the interpolation approach
    """
    alpha = alpha_0
    phi_alpha = phi(alpha)
    while not armijo_condition(alpha, phi_alpha, phi_0, phi_prime_0, sigma):
        alpha_star = (-phi_prime_0 * alpha**2)/2*(phi_alpha - phi_0 - phi_prime_0 * alpha)
        alpha = min(max(alpha_star, beta_lower * alpha), beta_upper * alpha) #clip alpha to interval
        phi_alpha = phi(alpha)
    return alpha
