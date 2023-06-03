import numpy as np

def steihaug_Toint_CG(H, b, Minv, eps_rel, Delta):
    """return approximate solution of Hs = b with ||s|| <= Delta"""
    
    #l = 0
    s = 0
    zeta = -b
    p = -Minv @ zeta
    delta_0 = - np.dot(zeta, p)
    delta = delta_0
    gamma = delta
    xi = 0
    omega = 0
    while delta >= eps_rel**2 * delta_0:
        #TODO: edit
        q = H @ p
        theta = np.dot(q, p)
        if theta > 0:
            alpha = delta/theta
            s_new = s + alpha * p
            omega = omega + 2*alpha*xi + alpha**2*gamma
            if np.sqrt(omega) > Delta:
                alpha_star = - xi/(2 * gamma) + xi/(2*gamma) * np.sqrt((1 - 4*gamma*(omega - Delta**2)))
                s = s + alpha_star * p
                pred = b * s - .5 * s.T @ H @ s
                return s, pred #add s_m_norm
            else:
                s = s_new
                zeta = zeta + alpha * q
                new_p = - Minv @ zeta
                new_delta = - np.dot(zeta, new_p)
                beta = new_delta/delta
                delta = new_delta

                xi = beta * (xi + alpha * gamma)
                gamma = delta + beta**2 * gamma

                p = new_p + beta*p
                
        else:
            alpha_star = - xi/(2 * gamma) + xi/(2*gamma) * np.sqrt((1 - 4*gamma*(omega - Delta**2)))
            s = s + alpha_star * p
            pred = b * s - .5 * s.T @ H @ s
            return s, pred #add s_m_norm
    pred = b * s - .5 * s.T @ H @ s
    return s, pred #add s_m_norm