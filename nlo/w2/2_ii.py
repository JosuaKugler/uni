import numpy as np
import matplotlib.pyplot as plt

def compute_gradient(derivative, preconditioner):
    m_gradient = - np.linalg.inv(preconditioner) @ derivative
    return m_gradient

#example in three dimensions:
def example():
    derivative = np.array([1,2,3])
    preconditioner = np.array([[1,2,3],[4,5,6],[7,8,9]])
    print(compute_gradient(derivative, preconditioner))

#visualization for two dimensions

def visualize(derivative):

    fix, ax = plt.subplots(1,2)

    derivative = np.array(derivative)
    r = np.arange(-1, 1, 0.01)
    theta = np.pi * r
    x = np.sin(theta)
    y = np.cos(theta)
    #d = np.array([x,y])
    #derivative: 1 x 2, d: 2 x 200 
    good_x = []
    good_y = []
    for x_i, y_i in zip(x,y):
        if (np.matmul(np.array([x_i,y_i]), derivative.transpose())) < 0:
            good_x.append(x_i)
            good_y.append(y_i)

    ax[0].scatter(good_x,good_y) #directions where gradient * direction < 0

    #all symmetric positive definite matrices of size 2x2 are symmetric, trace > 0 and det > 0 
    #(and these three conditions are sufficient)
    #[[a,b],[b,c]]
    #we choose b = 1 or b = -1 because positive scalar multiples are boring. Then det(A) > 0 => ac > 1 and tr(A) > 0 => a + c > 0
    a = np.logspace(-4,4,100)
    c = np.logspace(-4,4,100)

    spd_matrices_p = np.array([[[a_i,1.], [1., c_i]] for a_i in a for c_i in c if a_i * c_i > 1], dtype=float)
    spd_matrices_n = np.array([[[a_i,-1.], [-1., c_i]] for a_i in a for c_i in c if a_i * c_i > 1], dtype=float)
    spd_matrices = np.concatenate((spd_matrices_p, spd_matrices_n))
    
    #in this step we could use our compute_gradient function, but this is easier:
    steepest_directions = spd_matrices @ derivative
    
    steepest_x = []
    steepest_y = []
    for pair in steepest_directions:
        x_i = pair[0]
        y_i = pair[1]
        norm = np.sqrt(x_i**2 + y_i**2)
        steepest_x.append(-x_i/norm)
        steepest_y.append(-y_i/norm)
    ax[1].scatter(steepest_x,steepest_y)
    #print(steepest_directions) #list of vectors with [x,y] coordinates after multiplication with M

    #plt.plot(steepest_directions)
    plt.savefig("2_ii_2d_plot.png")
    plt.show()

visualize([2.,.5])