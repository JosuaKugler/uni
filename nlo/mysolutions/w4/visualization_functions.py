# This module implements various plotting functions to visualize the results
# of iterative optimization schemes and more.

import numpy as np

import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

from mpl_toolkits import mplot3d

from scipy.spatial import HalfspaceIntersection
from scipy.spatial import ConvexHull

from itertools import cycle

plt.rcParams["figure.figsize"] = (10, 10)

def plot_2d_iterates_contours(f, histories, labels, title = 'Iterates and iso-lines of function', xlims = None, ylims = None):
	""" 
	Plot 2d iterates provided in histories of iterative solvers in the iterate 
	space
  
	Accepts:
		               f: the function that was minimized by the iterative solvers
		       histories: list of history dictionaries created from the iterative solvers
		          labels: list of label strings for the plot
		           title: title of the plot (default supplied)

	Returns:
		       figure handle
	"""
	if labels is None:
		labels = ['dummy']*len(histories)
		pltlabels = False
	else:
		pltlabels = True


	if xlims is None or ylims is None:
		# Determine a quadratic bounding box for the iterates
		all_iterates = np.vstack(list(np.vstack(history["iterates"]) for history in histories))

		min_x, max_x = np.min(all_iterates[0]), np.max(all_iterates[0])
		min_y, max_y = np.min(all_iterates[1]), np.max(all_iterates[1])

		dx = np.abs(max_x - min_x)
		dy = np.abs(max_y - min_y)

		alph = 0.5

		xlims, ylims = (min_x - alph*dx, max_x + alph*dx), (min_y - alph*dy, max_y + alph*dy)

	x_disc = np.linspace(xlims[0], xlims[1], num = 251)
	y_disc = np.linspace(ylims[0], ylims[1], num = 251)
	X, Y = np.meshgrid(x_disc, y_disc)

	# Get the function values of f on the grid for contour plots
	Z = np.zeros(X.shape)
	for i, x_comp in enumerate(x_disc):
		for j, y_comp in enumerate(y_disc):
			Z[i,j] = f(np.array([x_comp,y_comp]))
	
	fig, ax = plt.subplots()

	for i, history in enumerate(histories):
		# Plot contour lines at iterate function values levels (max of 20)
		#contour_vals = sorted(set(history["objective_values"][20::-1]))

		# Set relevant contour lines (max of 20)
		#contour_vals = sorted(set(history["objective_values"][20::-1]))
		contour_vals = np.linspace(min(history["objective_values"]), max(history["objective_values"]), 20)
		contour_vals = np.linspace(np.min(Z)-0.2*np.abs(np.min(Z)), np.max(Z)+0.2*np.abs(np.max(Z)), 20)

		# plot
		plt.contourf(X, Y, Z.T, cmap='gray_r', levels = contour_vals)
		
		# Plot 2d iterates
		plt.plot(np.vstack(history["iterates"])[:,0], np.vstack(history["iterates"])[:,1], 's-', label = labels[i])

	plt.gca().set_aspect('equal','box')
	plt.title(title)
	if pltlabels:
		plt.legend()
	plt.xlabel('x')
	plt.ylabel('y')
	ax.set_xlim(xlims)
	ax.set_ylim(ylims)

	return fig

def plot_f_val_diffs(histories, reference_values, condition_numbers = None, methods = None, labels = None, title = 'Difference of functional values'):
	"""
	Plot difference of objective function values provided in histories of
	iterative solvers and user supplied reference values (times 2 and taken the square root) for each history.
	
	If the user supplied reference values are the optimal value and the
	the problem is quadratic, then this equals the energy norm
	of the error. Otherwise this method may be used to provide approximative
	information.
	
	Optional plot is the expected upper bound for convergence
	speed for quadratic problems provided the generalized condition number.
	
	Accepts:
		               histories: list of history dictionaries created from the iterative solvers
		        reference_values: list of reference values
		       condition_numbers: list of generalized condition numbers if the problems in histories
		                          were quadratic (default None)
		                  labels: list of label strings for the plot
		                   title: title of the plot (default supplied)

	Returns:
		       No return values.
	"""
	if labels is None:
		labels = ['dummy']*len(histories)
		pltlabels = False
	else:
		pltlabels = True

	# Evaluate and plot the differences of the objective values and reference values
	fig = plt.figure()
	
	for history, reference_value, label in zip(histories, reference_values, labels):
		history["f_val_diffs"] = np.sqrt(2*(np.abs(history["objective_values"] - reference_value)))
		plt.semilogy(history["f_val_diffs"], label = label)
	
	# If condition_numbers were supplied, assume that f was quadratic and plot
	# upper bounds on convergence speed
	bound_labels = []

	if methods is None:
		methods = ['']*len(labels)

	try:
		plt.gca().set_prop_cycle(None) # Restart the color cycle
		
		for history, reference_value, condition_number, method, label in \
			zip(histories, reference_values, condition_numbers, methods, labels):
			# Evaluate the linear convergence factor from condition quotient
			contraction_CG = (np.sqrt(condition_number) - 1) / (np.sqrt(condition_number) + 1)
			contraction_SD = (condition_number - 1) / (condition_number + 1)
			
			# Evaluate initial energy norm of error squared from the function value diffs
			initial_error = history["f_val_diffs"][0]
			
			# Evaluate the predicted upper bound at each iteration starting from the initial error norm
			upper_error_bound_SD = initial_error * (contraction_SD**(np.arange(0,len(history["objective_values"]))))
			upper_error_bound_CG = 2*initial_error * (contraction_CG**(np.arange(0,len(history["objective_values"]))))
			
			if method == 'CG':
				plt.semilogy(upper_error_bound_CG, '--', label = label + ' bound')
			else:
				plt.semilogy(upper_error_bound_SD, '--', label = label + ' bound')

	except Exception as exx:
		#print("No upper bound plotable. " + exx.__str__())
		#print(exx)
		pass
		
	plt.title(title)
	plt.xlabel('Iteration')
	plt.ylabel(r'$||x-x^*||_A$')
	if pltlabels:
		plt.legend()

	return fig

def plot_step_sizes(histories,labels):
	"""Plot the step lengths of a list of histories."""
	fig = plt.figure()
	for history in histories:
		plt.plot(history["step_lengths"])
		
	plt.title('Step lengths')
	plt.xlabel('Iteration')
	plt.ylabel('Step length')
	if labels:
		plt.legend(labels)

	return fig

def plot_grad_norms(histories,labels):
	"""Plot the gradient norms of a list of histories."""
	fig = plt.figure()
	for history in histories:
		plt.semilogy(history["gradient_norms"])
		
	plt.title('Preconditioner norm of gradients')
	plt.xlabel('Iteration')
	plt.ylabel('Norm value')
	if labels:
		plt.legend(labels)

	return fig
