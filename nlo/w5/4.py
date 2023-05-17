import numpy as np
import matplotlib.pyplot as plt

from visualization_functions import (
    plot_2d_iterates_contours,
    plot_f_val_diffs,
    plot_step_sizes,
    plot_grad_norms,
)
from gradient_descent_UP import gradient_descent_UP
from globalized_newton_UP import globalized_newton_UP
from example_functions import rand_problem, rosenbrock


# compare gradient norms
N = 10
problems = []

for i in range(N):
    problems.append(rand_problem(2))

# normalize norm of random start point
for problem in problems:
    problem.x0 = problem.x0 * (np.linalg.norm(problem.x0)) ** (-1)

histories = []
# labels = []
if False:
    for problem in problems:
        histories.append(
            gradient_descent_UP(
                problem.x0,
                problem.f,
                problem.f_prime,
                problem.Pinv,
                sigma=1e-3,
                alpha_lower_bound=10,
                beta=0.5,
                #beta_upper=0.9,
            )
        )

problem = rand_problem(2)

histories = [globalized_newton_UP(problem.x0, problem.f, problem.f_prime, lambda xx: problem.A @ xx, )]


plot_grad_norms(
   histories=histories, labels=range(len(histories))
)  # Gradient norms - gradient descent algorithm

# for i, problem in enumerate(problems):
#    plot_2d_iterates_contours(problem.f, histories=[histories[i]], labels=[str(i)], xlims=[-10,10], ylims=[-10,10])

a = 1
b = 100
rosenbrock_f = lambda x: rosenbrock(a, b, x)[0]
rosenbrock_prime = lambda x: rosenbrock(a, b, x)[1]

rosenbrock_histories = []
rosenbrock_labels = []
configurations = [
    ([2, 2], 1e-2, 0.01, 0.5),
    ([2, 2.5], 1e-2, 0.1, 0.5),
    ([2.5, 2], 1e-4, 0.01, 0.5),
    ([2.5, 2.5], 1e-4, 0.1, 0.5),
]
for configuration in configurations:
    rosenbrock_histories.append(
        gradient_descent_UP(
            configuration[0],
            rosenbrock_f,
            rosenbrock_prime,
            np.identity(2),
            sigma=configuration[1],
            alpha_lower_bound=configuration[2],
            beta=configuration[3],
            max_iter=100,
        )
    )
    rosenbrock_labels.append(
        f"x0: {configuration[0]}, sigma: {configuration[1]}, alpha: {configuration[2]}, beta: {configuration[3]}"
    )


plot_grad_norms(
    histories=rosenbrock_histories,
    labels=rosenbrock_labels,
)

plot_2d_iterates_contours(
    rosenbrock_f,
    histories=rosenbrock_histories,
    labels=rosenbrock_labels,
    xlims=[-3, 3],
    ylims=[-2,4],
    title="Iterates and iso-lines of Rosenbrock function"
)

plt.show()