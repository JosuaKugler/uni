# This script visualizes the influence of the choice of the preconditioner, the step length rule and the initial values when solving an spd quadratic optimization problem via the preconditioned steepest descent method

import numpy as np
from gradient_descent_quadratic import *
from scipy.linalg import eigh
from step_length_rules import *
from visualization_functions import plot_2d_iterates_contours, plot_f_val_diffs, plot_step_sizes, plot_grad_norms
import matplotlib.pyplot as plt

# Reset random number generator
np.random.seed(0)

# Set quadratic function data
A = np.array([[4.0, -1.25], [-1.25, 1.0]])
b = np.array([2.0,0])
c = 0

# Make quadratic function
f = lambda x: 0.5*x.T@(A@x) - b@x + c

# Set an arbitrary initial point that may be used
x0 = (2.0, 5.0)

# Set plotting upper and lower bounds
xlims = (-2.5,5.5)
ylims = (-2.5,5.5)

# Construct a "random" spd matrix with small entries to make preconditioners
rand_spd = np.random.rand(A.shape[0], A.shape[1])
rand_spd = 0.5 * (rand_spd.T + rand_spd) + A.shape[0] * np.identity(A.shape[0])
rand_spd = 1e-2 * rand_spd

# Construct some preconditioners
preconditioners = [(A[::-1,::-1].T, "A_T"),                     # Transposed A along antidiagonal
					(np.identity(len(x0)), "Identity"), # Identity
					(np.diag(np.diag(A)), "Diagonal"),  # Diagonal of A
					(A +  rand_spd, "A + eps * R"),     # Mildly perturbed A
					(A, "A")] # A

# save data for pseudo randomized initial values
nSamples = 10
dim = b.shape[0]

# make identity preconditioner
identity_preconditioner = np.identity(dim)

# Set gradient scheme parameters
options = {
	"atol_res": 5e-8,
	"rtol_res": 5e-8,
	"max_iterations" : 1e4,
	#"verbosity" : "verbose",
	"verbosity" : "quiet",
	"keep_history" : True,
	"reset_after" : 50
}

# Compute reference solution
reference_sol = np.linalg.solve(A,b)
reference_value = f(reference_sol)


### Visualize preconditioner effects
# Create some containers
outputs = []
labels = []
generalized_condition_numbers = []

# Solve problem for various preconditioners
for preconditioner, label in preconditioners:
	# solve problem
	outputs.append(
		gradient_descent_quadratic(lambda r: np.linalg.solve(preconditioner,r), A, b, c, x0, cauchy_quadratic, options)
		)
	labels.append(label)

	# save eigenvalue data
	generalized_eigenvalues = eigh(A, preconditioner, eigvals_only = True)
	generalized_condition_numbers.append(generalized_eigenvalues[-1] / generalized_eigenvalues[0])

	# Check solution
	if not np.allclose(outputs[-1]['solution'], reference_sol):
		print('Warning: gradient scheme may not have computed the correct solution')

# Plot preconditioner history in iterate space
iterFig = plot_2d_iterates_contours(f, histories = list(out["history"] for out in outputs), labels = labels, title = 'Preconditioner-Effect in Iterate-Space', xlims = xlims, ylims = ylims)

# Plot error energy norm
convFig = plot_f_val_diffs(list(out["history"] for out in outputs),
				[reference_value] * len(outputs),
				generalized_condition_numbers,
				labels=labels,
				title = 'Preconditioner-Effect on convergence')

# Plot step sizes
stepFig = plot_step_sizes(list(out["history"] for out in outputs), labels)

# Plot gradient norms
gradNormFig = plot_grad_norms(list(out["history"] for out in outputs), labels)

# Save figures
for fig, name in zip([iterFig, convFig, stepFig, gradNormFig],['iterates', 'convergence', 'step_sizes', 'grad_norms']):
	figName = '../figures/ex_008_gradient_descent_quadratic_precon_visualization_' + name + '.png'
	print('driver_ex_008 is saving figure: ' + figName)
	plt.figure(fig)
	plt.savefig(figName)


### Visualize initial guess effects
# Create a new container
outputs = []

# Fix a preconditioner for th remainder
preconditioner = identity_preconditioner

# Compute eigenvalues and condition number
generalized_eigenvalues = eigh(A, preconditioner, eigvals_only = True)
generalized_condition_number = (generalized_eigenvalues[-1] / generalized_eigenvalues[0])

# solve problem starting from various initial values
for i in np.arange(nSamples):
	x0x = (xlims[1]-xlims[0])*np.random.random_sample() + xlims[0]
	x0y = (ylims[1]-ylims[0])*np.random.random_sample() + ylims[0]

	outputs.append(
		gradient_descent_quadratic(lambda r: np.linalg.solve(preconditioner,r), A, b, c, np.array((x0x,x0y)), cauchy_quadratic, options)
		)

# Turn off labels
labels = None

# Plot history in iterate space
iterFig = plot_2d_iterates_contours(f, histories = list(out["history"] for out in outputs), labels = labels, title = 'Convergence from various initializations (cauchy step)', xlims = xlims, ylims = ylims)

# Plot error energy norm
convFig = plot_f_val_diffs(list(out["history"] for out in outputs),
				[reference_value] * len(outputs),
				[generalized_condition_number]* len(outputs),
				labels=labels,
				title = 'Convergence from various initializations (cauchy step)')

# Save figures
for fig, name in zip([iterFig, convFig, stepFig, gradNormFig],['iterates', 'convergence']):
	figName = '../figures/ex_008_gradient_descent_quadratic_init_visualization_cauchy_' + name + '.png'
	print('driver_ex_008 is saving figure: ' + figName)
	plt.figure(fig)
	plt.savefig(figName)

### Visualize fixed step length effects
# Create a new container
outputs = []

# Fixed step lengths
ts = [0.5, 1, 1.5, 2 - 1e-2]/generalized_eigenvalues[-1]

# solve problem starting from various initial values
for t in ts:
	step_length_rule = lambda data: fixed_step(data,t)

	for i in np.arange(nSamples):
		x0x = (xlims[1]-xlims[0])*np.random.random_sample() + xlims[0]
		x0y = (ylims[1]-ylims[0])*np.random.random_sample() + ylims[0]

		outputs.append(
			gradient_descent_quadratic(lambda r: np.linalg.solve(preconditioner,r), A, b, c, np.array((x0x,x0y)), step_length_rule, options)
			)


	# Plot history in iterate space
	iterFig = plot_2d_iterates_contours(f, histories = list(out["history"] for out in outputs), labels = labels, title = 'Convergence from various initializations (t = {:1.3e})'.format(t), xlims = xlims, ylims = ylims)

	# Plot error energy norm
	convFig = plot_f_val_diffs(list(out["history"] for out in outputs),
						[reference_value] * len(outputs),
						labels = labels,
						title = 'Convergence from various initializations (t = {:1.1e})'.format(t))

	# Save figures
	for fig, name in zip([iterFig, convFig, stepFig, gradNormFig],['iterates', 'convergence', 'step_sizes', 'grad_norms']):
		figName = '../figures/ex_008_gradient_descent_quadratic_init_visualization_fixed_' + '{:1.1e}_'.format(t) + name + '.png'
		print('driver_ex_008 is saving figure: ' + figName)
		plt.figure(fig)
		plt.savefig(figName)
