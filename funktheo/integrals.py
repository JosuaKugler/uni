from sympy import *

t = symbols("t")

a = 3*t
b = 3*(I-1)*t - I + 2
c = 3*I*(1-t)

adiff = diff(a,t)
bdiff = diff(b,t)
cdiff = diff(c,t)

ot = Rational(1,3)

A = integrate(a**2 * adiff, (t, 0, ot))
B = integrate(b**2 * bdiff, (t, ot, 2*ot))
C = integrate(c**2 * cdiff, (t, 2*ot, 1))
#print(A, B, C)


print(latex(integrate(b**2, (t, ot, 2*ot))))

print(latex(integrate(b**2 * bdiff, t)))