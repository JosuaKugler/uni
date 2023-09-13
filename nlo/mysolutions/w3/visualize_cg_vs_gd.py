import numpy as np
import matplotlib.pyplot as plt

from visualization_functions import plot_2d_iterates_contours, plot_f_val_diffs, plot_step_sizes, plot_grad_norms
from rand_problem import rand_problem


# Reset random number generator
np.random.seed(0)

# Set quadratic function data
A = np.array([[4.0, -1.25], [-1.25, 1.0]])
b = np.array([2.0,0])
c = 0

# Make quadratic function
f = lambda x: 0.5*x.T@(A@x) - b@x + c

xlims = (-2.5,5.5)
ylims = (-2.5,5.5)

preconditioners = [
    np.identity(len(b)),
    np.diag(np.diag(A)),
    A[::-1,::-1].T
]
eps = 1e-5
startpoints = []
for i in range(3):
    startpoints.append(
        np.array([
        (xlims[1]-xlims[0])*np.random.random_sample() + xlims[0],
        (ylims[1]-ylims[0])*np.random.random_sample() + ylims[0]
    ]))

def quadratic_minimization(x, A,b,c, M, eps, conjugacy = True):
    f = lambda x: 0.5*x.T@(A@x) - b@x + c

    k = 0
    M_inv = np.linalg.inv(M)
    r = A @ x - b
    d = - M_inv @ r
    delta = - (r).transpose() @ d
    history = {
			"iterates" : [],
			"objective_values" : [],
			"gradient_norms" : [],
			"step_lengths" : []
		}
    while delta > eps**2 and k < 100:
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

conjugacy_histories = []
conjugacy_labels = []
for i in range(len(preconditioners)):
    for startpoint in startpoints:
        conjugacy_histories.append(quadratic_minimization(startpoint,A,b,c,preconditioners[i],eps))
        conjugacy_labels.append(str(i) + " " + str(startpoint))

histories = []
labels = []
for i in range(len(preconditioners)):
    for startpoint in startpoints:
        histories.append(quadratic_minimization(startpoint,A,b,c,preconditioners[i],eps, conjugacy=False))
        labels.append(str(i) + " " + str(startpoint))

#plot_2d_iterates_contours(f, histories=conjugacy_histories, labels=conjugacy_labels, xlims=xlims, ylims=ylims)
#plot_2d_iterates_contours(f, histories=histories, labels=labels, xlims=xlims, ylims=ylims)

plt.show()