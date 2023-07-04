from lemkelcp import lemkelcp as lcp
import numpy as np


def generalized_newton(F, F_prime, z_0, subproblem_solver, termination_criteria, eps):
    z = z_0
    n = 0
    while not termination_criteria(z, F, n, eps):
        n += 1
        print(f"Iteration {n}, z = {z}")
        exit_code, z_new = subproblem_solver(z, F, F_prime)
        if exit_code != 0:
            raise Exception(f"subproblem at z={z} not solvable")
        else:
            z = float(z_new)
    return z


def subproblem_solver_2_iii(z, F, F_prime):
    M = np.array([[F_prime(z)]])
    q = np.array([F(z) - F_prime(z) * z])
    print(M, q)

    try:
        sol = lcp.lemkelcp(M, q)
    except:
        return 1, None  # exit code 1: lemkel algorithm doesn't work

    if sol[1] == 0:
        return 0, sol[0]
    else:
        return 2, None  # exit code 2: lemkel algorithm returns non-zero exit code


def termination_criteria_100(z, F, n, eps):
    if n > 1000:
        return True
    else:
        if abs(min(z, 0)) < eps and abs(min(F(z), 0)) < eps and abs(F(z) * z) < eps:
            return True
        else:
            return False


def F(z):
    return (z - 1) ** 2


def F_prime(z):
    return 2 * (z - 1)


result = generalized_newton(
    F,
    F_prime,
    z_0=0.99,
    subproblem_solver=subproblem_solver_2_iii,
    termination_criteria=termination_criteria_100,
    eps=1e-5,
)
print(result)