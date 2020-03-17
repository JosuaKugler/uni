import matplotlib.pyplot as plt
import numpy as np
import scipy
import sympy

def f300(v):
    """
    Funktion, die den Funktionswert an der Stelle v berechnet
    """
    #T = 300
    const = 1 #sqrt(2/pi) * (m/(k_B*T))^{3/2}
    expconst = -1 #-m/(2k_B * T)
    return const * v**2 * np.exp(expconst * v**2)

def f1000(v):
    """
    Funktion, die den Funktionswert an der Stelle v berechnet
    """
    #T = 1000
    const = 1 #sqrt(2/pi) * (m/(k_B*T))^{3/2}
    expconst = -1 #-m/(2k_B * T)
    return const * v**2 * np.exp(expconst * v**2)

#x = np.linspace(start, stop, num) num = Anzahl der Werte im Intervall von start bis stop
x = np.linspace(-3,3, 601)

fig = plt.figure()
ax = fig.add_subplot(111)
plt.plot(x, f300(x), "r", label = "T = 300 K")
plt.plot(x, f1000(x), "b", label = "T = 1000 K")

plt.xlabel("$v$")
plt.ylabel("$f(v)$")
plt.legend()
plt.savefig("./3ac.pdf")
plt.show()