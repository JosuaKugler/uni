#task 2 (iii)
import numpy as np
import matplotlib.pyplot as plt

x = np.arange(0,20)

def seq(k, i):
    if i == 0:
        return 2.**((-1)**k - k)
    elif i == 1:
        return 2.**(-k)
    elif i == 2:
        return 2.**(-k**2)
    elif i == 3:
        return 2.**(-2**k)

fig, axs = plt.subplots(2,4)

for i in range(4):
    axs[0,i].scatter(x, seq(x, i))
    axs[1,i].scatter(x, np.log(seq(x, i)))

plt.show()