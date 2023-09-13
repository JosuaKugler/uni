import numpy as np
from steihaug_Toint_CG import steihaug_Toint_CG

def generic_trust_region(x0, f, f_prime, H_routine, M_inverse, Delta_0, eta_1, eta_2, gamma_1, gamma_2):
    k = 0
    x = x0
    this_f = f(x)
    Delta = Delta_0

    history = {}
    history['Delta'] = [Delta]
    history['ared'] = []
    history['iterates'] = [x]
    history['objective_values'] = [this_f]

    M = np.linalg.inv(M_inverse)
    while k < 100:
        H = H_routine(x)
        s, pred = steihaug_Toint_CG(H, -f_prime(x), M_inverse, eps_rel=1e-4, Delta=Delta)
        s_m_norm = s.T @ M @ s
        x_new = x + s
        f_new = f(x_new)
        ared = this_f - f_new
        #print(f"pred: {pred}")
        rho = ared/pred
        #print(f"x={x}, f={this_f}, s={s}, pred={pred}, ared={ared}, Delta={Delta}")
        if rho >= eta_1:
            history['Delta'].append(Delta)
            history['ared'].append(ared)
            history['iterates'].append(x_new)
            history['objective_values'].append(f_new)
            x = x_new
            this_f = f_new
            if rho >= eta_2 and np.allclose(s_m_norm, Delta, rtol=1e-5, atol=1e-16):
                Delta = gamma_2 * Delta
        else:
            Delta = gamma_1 * Delta
        k = k + 1

    return x, history

