from sympy import *

t = symbols("t")

def skalarprodukt(pol1, pol2):
    return integrate(pol1*pol2, (t, 0, 1))

def norm(pol):
    return sqrt(skalarprodukt(pol, pol))

def normiere(pol):
    return pol / norm(pol)

pol1 = 1
pol2 = t
pol3 = t**2
pol4 = t**3

x1 = pol1

x2tilde = pol2 - skalarprodukt(pol2, x1)* x1
print(latex(x2tilde))
x2 = normiere(x2tilde)
print(latex(x2))

x3tilde = pol3 - skalarprodukt(pol3, x1) * x1 - skalarprodukt(pol3, x2) * x2
print(latex(x3tilde))
x3 = normiere(x3tilde)
print(latex(x3))

x4tilde = t**3 - skalarprodukt(t**3, x1) * x1 - skalarprodukt(t**3, x2) * x2 - skalarprodukt(t**3, x3) * x3
print(latex(x4tilde))
x4 = normiere(x4tilde)
print(latex(x4))