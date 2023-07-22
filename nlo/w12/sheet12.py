import numpy as np 
import matplotlib.pyplot as plt


# solves systems as in the algorithm
def solve_system(M,B,zeta,m,n):
    C = np.block([[M,B],[B.transpose(),np.zeros((m,n))]])
    zeta_new = np.pad(zeta,(0,m),"constant")
    return np.linalg.solve(C,-zeta_new)[:n]

def truncated_cg_for_symm_systems(b,d_part,A,M,B,eps_rel):
    m = np.shape(B)[0]
    n = np.shape(B)[1]

    alpha = 0 
    beta = 0
    q = 0
    theta = 0

    d = d_part 
    zeta = np.dot(A,d) - b
    p = solve_system(M,B,zeta,m,n)
    p_new = 0
    initial_delta = -np.dot(zeta,p)
    delta = initial_delta
    delta_new = 0
    delta_array = [delta]
    while delta >= eps_rel**2 * initial_delta:
        q = np.dot(A,p)
        theta = np.dot(q,p)
        if theta > 0:
            alpha = delta / theta 
            d = d + alpha*p 
            zeta = zeta + alpha*q
            p_new = solve_system(M,B,zeta,m,n)
            delta_new = - np.dot(zeta,p_new)
            beta = delta_new / delta
            p_new = p_new + beta* p
            p = p_new 
            delta = delta_new
            delta_array.append(delta) 
        else: 
            break 
    return(delta_array)



A = np.array([[11,3],[3,11]])
M = np.array([[-1,2],[2,-1]])
B = np.array([[1,0],[0,1]])

# c = [1,1], so d_part = [1,1]
d_part = np.array([1,1])
b = np.array([24,44])

plt.plot(truncated_cg_for_symm_systems(b,d_part,A,M,B,0.001))
plt.show()
