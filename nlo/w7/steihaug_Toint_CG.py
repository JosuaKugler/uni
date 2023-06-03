import numpy as np

def steihaug_Toint_CG(A, b, Minv, eps_rel):
    "return approximate solution of Ad = b"
    
    #l = 0
    d = 0
    zeta = -b
    p = -Minv @ zeta
    delta = - np.dot(zeta, p)
    gamma = delta
    while delta >= eps_rel**2 * delta:
        #TODO: edit
        q = A @ p
        theta = np.dot(q, p)
        if theta > 0:
            alpha = delta/theta
            d = d + alpha * p
            zeta = zeta + alpha * q
            new_p = - Minv @ zeta
            new_delta = - np.dot(zeta, new_p)
            beta = new_delta/delta
            delta = new_delta
            gamma = delta + beta**2 * gamma
            p = new_p + beta*p
        else:
            break
    return d, gamma