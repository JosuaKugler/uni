# This script visualizes the set of M-gradients with corresponding half space of descent directions
import numpy as np
import sys
import matplotlib.pyplot as plt
from operator import itemgetter
from compute_gradient import *

def quadratic_polynomial(A,b,c,x):
	"""
	Implements the quadratic polynomial f(x) = 0.5 * x^T A x + bx + c
	Accepts:
		       A: 2d array n by n
		       b: array of length n
		       c: scalar
		       x: array of length n
	Returns: 
		       f:  function value
		       df: derivative value
	"""
	x = np.array(x)
	f = 0.5*x.T@(A@x) + b@x + c
	df =  A@x + b
	return f, df

def rosenbrock(a,b,x):	
	"""
	Implements the rosenbrock function
	Accepts:
		       a,b: scalar parameters
		       x: array of length 2
	Returns: 
		       f:  function value
		       df: derivative value
	"""
	f  = (a - x[0])**2 + b * (x[1] - x[0]**2)**2
	df = np.array(
		[2*(a - x[0]) + 2*b*(x[1] - x[0]**2)*(-2*x[0]),
		 2*b*(x[1] - x[0]**2)
		]
		)
	return f, df

def get_configuration(configurationName):
	# Return configurations to investigate
	match configurationName:
		case 'quadratic_1':
			A = np.array(
				[[2, 0],
				[0, 1]]
				)
			b = np.array([0,0])
			c = 0
			
			configuration = {
				'fun': lambda x: quadratic_polynomial(A,b,c,x),
				'xlims': (-3,3),
				'ylims': (-3,3),
				'x': (1,1),
			}
			
		case 'quadratic_2':
			A = 1e-1*np.array(
				[[2, 1],
				[1, 1]]
				)
			b = np.array([-1,1])
			c = 0
			
			configuration = {
				'fun': lambda x: quadratic_polynomial(A,b,c,x),
				'xlims': (14,22),
				'ylims': (-32,-26),
				'x': (16,-28),
			}
			
		case 'quadratic_3':
			A = np.array(
				[[1, 0],
				[0, 0]]
				)
			b = np.array([0,0])
			c = 0
			
			configuration = {
				'fun': lambda x: quadratic_polynomial(A,b,c,x),
				'xlims': (-2,2),
				'ylims': (-2,2),
				'x': (-1,0),
			}
			
		case 'rosenbrock':
			a = 1
			b = 10
			
			configuration = {
				'fun': lambda x: rosenbrock(a,b,x),
				'xlims': (-2,2),
				'ylims': (-1,3),
				'x': (0.5,1.5),
			}
			
		case _:
			print('<<<<<<< Unknown configuration name >>>>>>>')
			sys.exit()

	return configuration

for configName in ['quadratic_1','quadratic_2','quadratic_3','rosenbrock']:
	configuration = get_configuration(configName)
	fun, xlims, ylims, x0 = itemgetter('fun','xlims','ylims','x')(configuration)

	# Compute function value and derivative
	f, df = fun(x0)
	
	# Compute euclidean gradient
	eucGradient = compute_gradient(df,np.eye(2))
	
	# Make some M gradients
	ds = []
	Mgrads = []
	for s in np.linspace(-1,1,6):
		# Set a target d
		eucGradientOrth = np.array([-eucGradient[1], eucGradient[0]])
		d = -eucGradient + s * eucGradientOrth
		ds.append(d)
		
		# Compute suitable preconditioner for target d using BFGS update formula
		g = -df
		gamma = 1/np.inner(g,d)
		M = np.eye(2) - np.outer(d,d)/np.inner(d,d) + gamma*np.outer(g,g)
		# Compute M gradient
		Mgrad = compute_gradient(df, M)
		# Verify that we computed a reasonable M
		if not np.allclose(d,-Mgrad):
			print("Predescribed d and computed M-gradient don't coincide. Check your computations.")
		Mgrads.append(Mgrad)
		
	### Visualization
	# Create mesh
	nd = 300
	xgrid = np.linspace(xlims[0], xlims[1], nd)
	ygrid = np.linspace(ylims[0], ylims[1], nd)
	[X, Y] = np.meshgrid(xgrid, ygrid)

	# Create contour data
	Z = np.empty(X.shape)
	for i,x in enumerate(xgrid):
		for j,y in enumerate(ygrid):
			Z[j,i], _ = fun(np.array([x,y])) 
		
	# Create figure
	fig, ax = plt.subplots(figsize = (8,8))
	ax.set_title(configName)
	ax.set_xlabel('x')
	ax.set_ylabel('y')
	ax.set_xlim(xlims)
	ax.set_ylim(ylims)
	ax.set_aspect('equal')
	# Contour plot
	ax.contour(X, Y, Z, levels = 40)
	# Point of eval 
	xcircle = plt.Circle(x0, 0.1, color='r',fill=True)
	ax.add_patch(xcircle)
	# Negative gradient (normal to halfspace of descent directions)
	plt.arrow(*x0, *(-eucGradient), head_width=0.05, length_includes_head=True)
	ax.annotate(r"$-\nabla f$", xy = np.array(x0)-1.2*eucGradient, xytext = np.array(x0) - 1.2*eucGradient, fontsize=15)
	# Descent directions (halfspace)
	if np.abs(eucGradient[1]) > 1e-5:
		interf = x0[1] + eucGradient[0]/eucGradient[1]*(x0[0]-xgrid)
		ax.plot(xgrid, interf)
		ybound = ylims[0] if eucGradient[1]>0 else ylims[1]
		ax.fill_between(xgrid,ybound, interf, alpha = 0.15)
	elif np.abs(eucGradient[0]) > 1e-5:
		ax.vlines(x0[0], *ylims)
		xbound = xlims[0] if eucGradient[0]>0 else xlims[1]
		ax.axvspan(xbound, x0[0], alpha = 0.15)
		
	# M gradients
	for d, Mgrad in zip(ds,Mgrads):
		plt.arrow(*x0, *d, head_width=0.05, length_includes_head=True)
		ax.annotate(r"$d$", xy = np.array(x0)+1.2*d, xytext = np.array(x0) + 1.2*d, fontsize=15)

		plt.arrow(*x0, *(-Mgrad), head_width=0.05, length_includes_head=True, color = 'r', linestyle = 'dashed')
		ax.annotate(r"$-\nabla_M f$", xy = np.array(x0)-1.15*Mgrad, xytext = np.array(x0) - 1.15*Mgrad, fontsize=15, color='r')
	
	figName = '../figures/ex_004_descent_halfspace_visualization_' + configName + '.png'
	print('driver_ex_004 is saving figure: ' + figName)
	plt.savefig(figName)
