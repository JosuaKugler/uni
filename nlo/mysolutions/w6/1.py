import numpy as np
import matplotlib.pyplot as plt

from visualization_functions import (
    plot_2d_iterates_contours,
    plot_f_val_diffs,
    plot_step_sizes,
    plot_grad_norms,
)
from globalized_inexact_newton_UP import globalized_inexact_newton_UP
from globalized_newton_UP import globalized_newton_UP
from example_functions import rosenbrock

a = 1
b = 100
rosenbrock_f = lambda x: rosenbrock(a, b, x)[0]
rosenbrock_prime = lambda x: rosenbrock(a, b, x)[1]
rosenbrock_two_prime = lambda x: rosenbrock(a, b, x)[2]

configurations = [
    ([1, 2], 1e-4),
    ([2, 1], 1e-4),
    ([2.5, 2], 1e-4),
    ([0, 4], 1e-4),
]
rosenbrock_histories_n = []
rosenbrock_labels_n = []

for configuration in configurations:
    rosenbrock_histories_n.append(
        globalized_newton_UP(
            configuration[0],
            rosenbrock_f,
            rosenbrock_prime,
            rosenbrock_two_prime,
            np.identity(2),
            sigma=1e-4,
            eta=.5,
            rho=1e-6,
            p=.1,
            beta=.5,
            eps=1e-10,
            max_iter=100,
        )
    )
    rosenbrock_labels_n.append(f"x0: {configuration[0]}, sigma:{configuration[1]}")

rosenbrock_histories_ni = []
rosenbrock_labels_ni = []
for configuration in configurations:
    rosenbrock_histories_ni.append(
        globalized_inexact_newton_UP(
            configuration[0],
            rosenbrock_f,
            rosenbrock_prime,
            rosenbrock_two_prime,
            np.identity(2),
            eta_k = lambda _ : 1e-3,
            sigma=1e-4,
            eta=.5,
            rho=1e-6,
            p=.1,
            beta=.5,
            eps=1e-10,
            max_iter=1000,
        )
    )
    rosenbrock_labels_ni.append(f"x0: {configuration[0]}, sigma: {configuration[1]}")

plot_grad_norms(
    histories=rosenbrock_histories_n,
    labels=rosenbrock_labels_n,
)
plot_grad_norms(
    histories=rosenbrock_histories_ni,
    labels=rosenbrock_labels_ni
)

plot_2d_iterates_contours(
    rosenbrock_f,
    histories=rosenbrock_histories_n,
    labels=rosenbrock_labels_n,
    xlims=[-3, 3],
    ylims=[0,7],
    title="Iterates and iso-lines of Rosenbrock function for globalized newton"
)
plot_2d_iterates_contours(
    rosenbrock_f,
    histories=rosenbrock_histories_ni,
    labels=rosenbrock_labels_ni,
    xlims=[-3, 3],
    ylims=[-2,5],
    title="Iterates and iso-lines of Rosenbrock function for globalized inexact newton"
)
plt.show()