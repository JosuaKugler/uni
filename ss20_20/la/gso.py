from sympy import *

A = Matrix([[1,I,0], [-I,3,I], [0,-I,1]])

def hA(x,y):
    return (x.T * A * conjugate(y))[0]

v1 = Matrix([1,0,0])
v2 = Matrix([0,1,0])
v3 = Matrix([0,0,1])

w1 = 1 / sqrt(hA(v1, v1)) * v1
w2tilde = v2 - hA(v2, w1) * w1
w2 =  1 / sqrt(hA(w2tilde, w2tilde)) * w2tilde
w3tilde = v3 - hA(v3, w1)*w1 - hA(v3, w2)*w2
w3 = 1/sqrt(hA(w3tilde, w3tilde)) * w3tilde

#test:
print("should be 1: ", hA(w1, w1))
print("should be 1: ", hA(w2, w2))
print("should be 1: ", hA(w3, w3))
print("should be 0: ", hA(w1, w2))
print("should be 0: ", hA(w1, w3))
print("should be 0: ", hA(w2, w3))

print(hA(w3tilde, w3tilde))
print(w1, w2, w3)