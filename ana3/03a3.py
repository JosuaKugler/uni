import numpy as np
import matplotlib.pyplot as plt 
import tikzplotlib

def f(k, x):
    if k == 0:
        return x
    else:
        if x < 1/3:
            return 0.5*f(k-1, 3*x)
        elif x <= 2/3:
            return 0.5
        else:
            return 0.5*(1 + f(k-1, 3*x - 2))
def plot(k):
    x = []
    for i in range(3**k + 1):
        x.append(i * 3**(-k))

    y = []
    for i in x:
        y.append(f(k, i))
    plt.plot(x,y)

#plot(0)
plot(1)
plot(2)
plot(3)


tikzplotlib.save("03a3fig.tex")
plt.show()
