import numpy as np

def compute_gradient(derivative, preconditioner):
	"""
	Compute a gradient from a derivative using a preconditioner.
	Implements Riesz isomorphism for the preconditioner scalar product.
	Accepts:
		       derivative:     array representing the derivative of a function at a point
		       preconditioner: 2d-array representing the matrix defining the scalar product
	Returns: 
		       gradient
	"""
	
	try:
		gradient = np.linalg.solve(preconditioner, derivative)
	except:
		print('Computing gradient from derivative failed. Your preconditioner might not be s.p.d. Defaulting to euclidean gradient.')
		gradient = derivative
	
	return gradient
