import numpy as np
from step_length_rules import *

def conjugate_gradient_quadratic(Pinv, A, b, c, x0 = None, step_length_rule = cauchy_quadratic, options = {}):
	"""
	This function solves the quadratic minimization problem
		min phi(u) = 0.5 * x'*A*x - b'*x + c,
	which is equivalent to the linear system
		A x = b,
	via the preconditioned steepest descent method.
	A is assumed to be symmetric.

	Accepts:
		            Pinv: The inverse procedure or inverse matrix of a symmetric positive definite matrix M defining the scalar product
		               A: the symmetric system matrix or its action on a vector as a function
		               b: the linear part
		               c: the constant part
		              x0: the initial guess (list or numpy array with ndim == 1)
		step_length_rule: a step length computation function
		         options: optional options (dictionary);
		                  the following key/value pairs are evaluated:
			                        ["atol_res"]: absolute stopping tolerance for the norm of the residual
			                        ["rtol_res"]: relative stopping tolerance for the norm of the residual
			                        Here 'norm' refers to the preconditioner-induced norm.
			               ["max_iterations"]: maximum number of iterations
			                    ["verbosity"]: "verbose" or "quiet"
			                 ["keep_history"]: whether or not to store the iteration history (True or False)
			                  ["reset_after"]: number of iterations that the data is updated instead of recomputed (int)
					  			["conjugacy"]: whether or not to use conjugate gradient instead of steepest descent (True or False)	

	Returns:
		result: a dictionary containing
		             solution: final iterate
		             function: the final iterate's objective value
		             residual: the final iterate's residual
		        norm_residual: (inverse) preconditioner-induced norm of final residual
		                 iter: number of iterations performed
		             exitflag: flag encoding why the algorithm terminated
		                       0: stopping tolerance described by atol_res, rtol_res reached
		                       1: maximum number of iterations reached
		              history: a dictionary for the history of the run containing
		                               iterates: the iterates x
		                       objective_values: the values of the objective function
		                         residual_norms: the norms of the objective residuals gradient
		                          steps_lengths: the step lengths chosen by the step length rule
	"""
	# Check if preconditioner was supplied as an action, otherwise assume matrix
	if not callable(Pinv):
		Pinvin = Pinv
		Pinv = lambda rr: Pinvin@rr

	# Check if system matrix was supplied as an action, otherwise assume matrix
	if not callable(A):
		Ain = A
		A = lambda xx: Ain@xx

	# Define an output function that will be used to print information on the state of the iteration
	def print_header():
		print('--------------------------------------------------------------------')
		print(' ITER          OBJ    NORM_RES     NORM_CORR     OBJ_CHNG           ')
		print('--------------------------------------------------------------------')

	# Define exitflags that will be printed when the algorithm terminates
	exitflag_messages = [
		'Relative or absolute tolerances on the norm of the residual is satisfied.',
		'Maximum number of optimization steps is reached.',
	]

	# Get the algorithmic options, using defaults if missing
	atol_res = options.get("atol_res", 1e-6)
	rtol_res = options.get("rtol_res", 1e-6)
	max_iterations = options.get("max_iterations", 1e3)
	verbosity = options.get("verbosity", "quiet")
	keep_history = options.get("keep_history", False)
	reset_after = options.get("reset_after", 0)
	conjugacy = options.get("conjugacy", True)

	# Initialize the iterates, counters etc.
	if x0 is None:
		x0 = np.zeros(np.array(c).shape)
		x = x0
	else:
		x0 = np.array(x0)
		x = x0
		
	iter = 0
	exitflag = None

	# Set the function and the derivative
	f = lambda xx: 0.5*xx.T@(A(xx)) - b@xx + c
	df = lambda xx: A(xx) - b

	# Initialize dummy values pertaining to the previous iterate
	x_old = np.full(x0.shape, np.inf)
	value_old = np.inf
	t=0

	# Prepare a dictionary to store the history
	if keep_history:
		history = {
			"iterates" : [],
			"objective_values" : [],
			"gradient_norms" : [],
			"step_lengths" : []
		}

	# Perform gradient descent steps until one of the termination criteria is met
	while exitflag is None:
		# Record the current iterate
		if keep_history: history["iterates"].append(x)

		# Dump some output
		if verbosity == 'verbose':
			if (iter%10 == 0): print_header()
			print(' %4d  ' % (iter), end = '')

		# Compute the function value and residual at current iterate
		if (iter%reset_after == 0):
			residual = df(x)
		else:
			residual = residual + t*A(d)

		value = c + 0.5*x.dot(residual - b)

		# Record the current value of the objective
		if keep_history: history["objective_values"].append(value)

		# Dump some output
		if verbosity == 'verbose': print('%11.4e  ' % (value), end = '')

		# Compute the preconditioned gradient and the square of its (preconditioner-induced) norm
		gradient = Pinv(residual)
		norm2_residual = residual.dot(gradient)

		if iter > 0:
			old_norm2_residual = norm2_residual
		# Check the computed norm square for positivity
		if norm2_residual < 0:
			raise ValueError('Your preconditioner appears not to be positive definite.')
		else:
			norm_residual = np.sqrt(norm2_residual)

		# Record the current norm of the gradient
		if keep_history: history["gradient_norms"].append(norm_residual)

		# Remember the norm of the initial gradient
		if (iter == 0): initial_norm_residual = norm_residual

		# Dump some output
		if verbosity == 'verbose': print('%11.4e  ' % (norm_residual), end = '')

		# Evaluate the norm of the update step
		norm_delta_x = t*norm_residual

		# Evaluate the change in the objective function values
		delta_f = value - value_old

		# Dump some output
		if verbosity == 'verbose': print('%11.4e  %11.4e' % (norm_delta_x, delta_f))

		# Stop when the maximum number of iterations has been reached
		if iter >= max_iterations:
			exitflag = 1
			break

		# Stop when the stopping tolerance on the norm of the gradient has been reached
		if norm_residual <= atol_res + rtol_res * initial_norm_residual:
			exitflag = 0
			break

		# Set the update direction
		if iter > 0: #there is no old d in step 0
			old_d = d
		d = -gradient

		# Prepare some data to pass down to the step length computation rule
		step_length_data = {
			"A": A,
			"value" : value,
			"residual" : residual,
			"d": d,
			"norm_residual": norm_residual
		}

		# Evaluate the step length t using the step length rule
		t, t_exitflag = step_length_rule(step_length_data)

		# Check whether of not the step length was computed succesfully
		if t_exitflag: raise AssertionError('Step length was not computed succesfully.')

		# Record the chosen step length
		if keep_history: history["step_lengths"].append(t)

		# Save the current iterate and associated function value for the next iteration
		x_old = x
		value_old = value
		
		#correct direction according to conjugacy:
		if iter > 0 and conjugacy:
			beta = norm2_residual/old_norm2_residual
			d = d + beta * old_d

		# Update the iterate and increase the counter
		x = x + t * d
		iter = iter + 1

	# Dump some output
	if verbosity == 'verbose':
		print('\n\nThe gradient descent method is exiting with flag %d.\n' %(exitflag) + str(exitflag_messages[exitflag])+'\n' )

	# Create and populate the result to be returned
	result = {
		"solution" : x,
		"function" : value,
		"gradient" : gradient,
		"norm_residual" : norm_residual,
		"iter" : iter,
		"exitflag" : exitflag
	}

	# Assign the history to the result if required
	if keep_history: result["history"] = history

	return result
