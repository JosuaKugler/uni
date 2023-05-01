import numpy as np
import matplotlib.pyplot as plt

def gradient_descent_plot(x, b, A, M, eps, ax, steps = "cauchy", stepsize = 0, stepsizefunction = None):
    x_steps = [x]

    k = 0
    M_inv = np.linalg.inv(M)
    r = A @ x - b
    d = - M_inv @ r
    delta = - (r).transpose() @ d
    other_criteria = True #e.g. stop when stepsizelist is exhausted
    while delta > eps**2 and other_criteria:
        q = A @ d
        if steps == "cauchy":
            theta = q.transpose() @ d
            alpha = delta/theta
        elif steps == "constant":
            if stepsize == 0:
                raise("stepsize can't be 0 if stepsize is constant")
            else:
                alpha = stepsize
        elif steps == "custom":
            if not stepsizefunction:
                raise("stepsizefunction can't be None if steps are custom")
            else:
                try:
                    alpha = stepsizefunction(x,r,k,M,M_inv)
                except:
                    raise("stepsizefunction is ill-defined")

        x = x + alpha * d
        r = r + alpha * q
        d = - M_inv @ r
        delta = - r.transpose() @ d
        k = k + 1

        #plotting
        x_steps.append(x)

    point_xs = []
    point_ys = []
    for point in x_steps:
        point_xs.append(point[0])
        point_ys.append(point[1])
    
    ax.plot(point_xs, point_ys)
    return x

def contour_plot(A,b,ax):
    x_vals = np.arange(-10,10,1)
    y_vals = np.arange(-10,10,1)
    X, Y = np.meshgrid(x_vals, y_vals)
    vals = np.array([X,Y])
    Ax = np.tensordot(A, vals, axes=([1,0]))
    xAx_pre = Ax * vals
    xAx = np.sum(xAx_pre,axis = 0)

    bx = np.tensordot(b, vals, axes=([0,0]))
    #bx = np.sum(bx_pre,axis = 0)
    #print(bx_pre.shape)

    Z = xAx - bx
    
    ax.contour(X, Y, Z)

#example
x = np.array([9.,9.])
b = np.array([0.,0.])
A = np.array([[2.,1.],[1.,3.]])
M1 = np.array([[1.,0.],[0.,1.]])
M2 = np.array([[2.,.5],[1.,1.5]])
Ms = [M1, M2]
eps = 1e-3

def foo(x,r,k,M,M_inv):
    return 1/(k+3)

fig, ax = plt.subplots(1,2) #possibly add more subplots
for i in range(2):
    contour_plot(A,b,ax[i])
    gradient_descent_plot((9.,9.),b,A,Ms[i],eps,ax[i])
    gradient_descent_plot((-9.,9.),b,A,Ms[i],eps,ax[i])
    gradient_descent_plot((9.,-9.),b,A,Ms[i],eps,ax[i])
    gradient_descent_plot((-9.,-9.),b,A,Ms[i],eps,ax[i])
    gradient_descent_plot((-9.,-9.),b,A,Ms[i],eps,ax[i],steps="constant",stepsize=.01)
    gradient_descent_plot((-9.,-9.),b,A,Ms[i],eps,ax[i],steps="custom",stepsizefunction=foo)
plt.savefig("example.png")