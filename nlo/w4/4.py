import numpy as np
import matplotlib.pyplot as plt

from visualization_functions import plot_2d_iterates_contours, plot_f_val_diffs, plot_step_sizes, plot_grad_norms
from rand_problem import rand_problem

max_iter = 100

def quadratic_minimization(x, A,b,c, M_inv, eps, conjugacy = True):
    f = lambda x: 0.5*x.T@(A@x) - b@x + c

    k = 0
    r = A @ x - b
    d = - M_inv @ r
    delta = - (r).transpose() @ d
    history = {
			"iterates" : [],
			"objective_values" : [],
			"gradient_norms" : [],
			"step_lengths" : []
		}
    while delta > eps**2 and k < max_iter:
        history["iterates"].append(x)
        history["objective_values"].append(f(x))
        history["gradient_norms"].append(np.sqrt(delta))
        q = A @ d
        theta = q.transpose() @ d
        alpha = delta/theta
        history["step_lengths"].append(alpha)
        x = x + alpha * d
        r = A@x - b
        #r = r + alpha * q
        d_old = d
        d = - M_inv @ r
        delta_old = delta
        delta = - r.transpose() @ d
        if conjugacy:
            beta = delta/delta_old
            d = d + beta * d_old
        k = k + 1

    history["iterates"].append(x)
    history["objective_values"].append(f(x))
    history["gradient_norms"].append(np.sqrt(delta))

    return history

#compare gradient norms

eps = 1e-5
N = 10
problems = []

for i in range(N):
    problems.append(rand_problem(20))

#normalize norm of random start point
for problem in problems:
    problem.x0 = problem.x0 * (np.linalg.norm(problem.x0))**(-1)

histories = []
conj_histories = []
#labels = []
for problem in problems:
    histories.append(quadratic_minimization(problem.x0, problem.A, problem.b, problem.c, problem.Pinv, eps, conjugacy=False))
    conj_histories.append(quadratic_minimization(problem.x0, problem.A, problem.b, problem.c, problem.Pinv, eps, conjugacy=True))

plot_grad_norms(histories=histories, labels=[]) #Gradient norms - gradient descent algorithm
plot_grad_norms(histories=conj_histories, labels=[]) #Gradient norms - conjugate gradient algorithm

#reference_values = [history["objective_values"][-1] for history in conj_histories]
#plot_f_val_diffs(histories=histories, labels=range(len(histories)), reference_values=reference_values)
#plot_f_val_diffs(histories=conj_histories, labels=range(len(histories)), reference_values=reference_values)


plt.show()