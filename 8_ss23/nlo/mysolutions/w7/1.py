import numpy as np
import matplotlib.pyplot as plt
from example_functions import rosenbrock

def get_s_inner(b, H_inverse, delta):
    s = H_inverse @ b
    b_norm_sq = b.T @ s
    b_norm = np.sqrt(b_norm_sq)
    if b_norm <= delta:
        return s, True
    else:
        #correction = np.sqrt(delta) / b_norm
        correction = delta / b_norm
        return correction * s, False


def get_S_delta_from_delta_bar(b, H_inverse, delta_bar, num_deltas):
    deltas = np.linspace(0,delta_bar,num_deltas)
    S_delta = []
    for delta in deltas:
        s, inner = get_s_inner(b, H_inverse, delta)
        S_delta.append((s, inner))
    return S_delta

num = 100
delta = 100
xs = [(0,-1), (0,.5)]
b_H_tupels = []
for x in xs:
    b = rosenbrock(1,100,x)[1]
    H = rosenbrock(1,100,x)[2]
    H_inverse = np.linalg.inv(H)
    b_H_tupels.append((b, np.eye(2)))
    b_H_tupels.append((b, H_inverse))

solutions = []
for b_H_tupel in b_H_tupels:
    S_delta = get_S_delta_from_delta_bar(*b_H_tupel, delta, num_deltas=num)
    solutions.append((S_delta, b_H_tupel))

fig, ax = plt.subplots(2,2)

for i, solution_tupel in enumerate(solutions):
    (S_delta, b_H_tupel) = solution_tupel
    (b, H) = b_H_tupel
    current_ax = ax[i%2,int(i>1)]
    for s in S_delta:
        (s, inner) = s
        if inner:
            c = 'red'
        else:
            c = 'blue'
        current_ax.scatter(*s,c=c)
    if (H==np.eye(2)).all():
        current_ax.title.set_text(f"$f'(x)^T={b}, H =$ id$_2$")
    else:
        current_ax.title.set_text(f"$f'(x)^T={b}, H = f''(x)$")

plt.show()