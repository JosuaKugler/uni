import numpy as np
import mpmath
import matplotlib.pyplot as plt
import tikzplotlib

n = 100000

x = np.arange(1,n,200)
primes = [x for x in range(2, n) if all(x % y != 0 for y in range(2, x))]

def pi(n):
    counter = 0
    for prime in primes:
        if prime < n:
            counter += 1
        else:
            break
    return counter

fig= plt.figure()
ax = fig.add_axes([0.1,0.1,0.8,0.8])
#ax.step(x, y, label='primes')
#ax.set_xticks(x)
#ax.set_xticklabels(labels=[str(i) for i in x])

y1 = []
y2 = []
y3 = []
y4 = []
y5 = []
y6 = []


def trudgian(x):
    return 0.2795 * x / (np.log(x)**0.75) * np.exp(-np.sqrt(np.log(x)/6.455))

def rh(x):
    return np.sqrt(x) * np.log(x)/(8*np.pi)

for i in x:
    value = float(mpmath.li(int(i), offset=True))
    differencerh = rh(i)
    differencetr = trudgian(i)
    y1.append(pi(i))
    y2.append(value)
    y3.append(value + differencerh)
    y4.append(value - differencerh)
    y5.append(value + differencetr)
    y6.append(value - differencetr)
#y2 = [mpmath.li(i, offset=True) for i in x]

#print(y2)

ax.step(x, y1, label=r"$\pi(x)$")
ax.plot(x, y2, label=r"$\operatorname{Li}(x) = \int_2^x \frac{\mathrm{d} t}{\ln t}$")
#ax.plot(x, y3, "gray")
#ax.plot(x, y4, "gray")
#ax.plot(x, y5, "gray")
#ax.plot(x, y6, "gray")

ax.set(ylim = (0,11900))

#plt.grid(axis='x', color='0.95')
plt.legend()
#plt.title('plt.step(where=...)')
tikzplotlib.save("figures/pi_li_none.tex")
plt.show()