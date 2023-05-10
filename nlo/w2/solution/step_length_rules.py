# This module collects various step length computation schemes for iterative
# line search optimization algorithms.
from operator import itemgetter

def cauchy_quadratic(data):
	"""
	Compute the cauchy step size (exact minimizer of slice) in optimization of spd quadratic polynomial optimization problems.

	Accepts:
	        data: data supplied by the external optimizer (dictionary). Requires:
	        ["norm_residual"]: norm of the residual with respect to the inverse preconditioner norm
	        ["d"]: update direction

	Returns:
	t: the cauchy step length
	exitflag: 0 if no error
"""
# get data
	A, d, norm_residual = itemgetter('A','d','norm_residual')(data)

	# compute cauchy step length
	t = (norm_residual**2)/(d.T@(A(d)))

	# Check if the step length is in fact positive, i.e., whether slice has positive curvature.
	if t < 0.0:
		raise ValueError('The step length computation yields a negative step length.')
	else:
		return t, 0


def fixed_step(data, fixed_length):
	"""
	Return a fixed step length.

	Accepts:
	         data: data supplied by the external optimizer (dictionary). Unused

	Returns: 
	                t: the fixed step length
	         exitflag: 0
	"""
	if fixed_length < 0.0:
		raise ValueError('The step length computation yields a negative step length.')
	else:
		return fixed_length, 0
