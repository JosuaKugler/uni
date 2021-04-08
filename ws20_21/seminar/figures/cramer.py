import numpy as np
import mpmath
import matplotlib.pyplot as plt
import tikzplotlib

n = 10000

primes = [i for i in range(2, n) if all(i % y != 0 for y in range(2, i))]

primediffs = []
oldprime = 2
for prime in primes[1:]:
    primediffs.append(prime - oldprime)
    oldprime = prime

plt.step(primes[1:], primediffs)


y1 = np.power(primes, 0.525)
y2 = np.sqrt(primes) * np.log(primes)
plt.plot(primes, y1, "y")
plt.plot(primes, y2, "g")

plt.show()