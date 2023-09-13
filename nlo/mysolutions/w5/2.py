import numpy as np
import matplotlib.pyplot as plt
def local_newton(x_0, F, F_prime, eps = 1e-4, max_iter = 100):
    x = x_0
    k = 0
    while np.linalg.norm(F(x)) > eps and k < max_iter:
        d = - np.linalg.inv(F_prime(x)) @ F(x)
        x = x + d
    return x

def f(X):
    x = X[0]; y = X[1] 
    return np.array([x**3 - 3*x*y**2 - 1, 3*x**2*y - y**3])

def f_prime(X):
    x = X[0]; y = X[1] 
    return np.array([[3*x**2 - 3*y**2, -6*x*y], [6*x*y, 3*x**2 - 3*y**2]])

third_roots_of_unity = [[1,0],[-.5,np.sqrt(3)/2],[-.5,-np.sqrt(3)/2]] #all three complex roots of z**3 - 1
index_to_color = {0: (255,0,0), 1: (0,255,0), 2: (0,0,255), 3:(0,0,0)}

N = 500
x = np.linspace(-1,1,N)
y = np.linspace(-1,1,N)

xv, yv = np.meshgrid(x,y)
data = np.zeros((N,N,3),dtype=np.uint8)

for index in np.ndindex(N,N):
    x_0 = xv[index]
    y_0 = yv[index]
    X_0 = np.array([x_0, y_0])
    X = local_newton(X_0, f, f_prime)
    min_distance = .1 #sanity check
    zero_index = 3
    for i, zero in enumerate(third_roots_of_unity):
        distance = np.linalg.norm(X - zero)
        if distance < min_distance:
            min_distance = distance
            zero_index = i
    data[index] = index_to_color[zero_index]

plt.imshow(data, interpolation='nearest')
plt.show()    