from sympy import *

#T = Matrix([[1, sqrt(2)/2 * I, -sqrt(2)/2], [0, sqrt(2)/2, sqrt(2)/2 * I], [0,0,sqrt(2)]])
B = Matrix([[2, -2 * I, -I], [0,0,-1], [0,0,2 * I]])

Bstar = conjugate(B.T) 

print(B * Bstar)
print(Bstar * B)