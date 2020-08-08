from astropy.table import Table
import numpy as np
from sympy import *
tab = Table.read('temp.tex')
tablist = np.array(tab)

tablelist = []

for row in tablist:
    thisrow = []
    for number in row:
        thisrow.append(number)
    tablelist.append(thisrow)

B = Matrix(tablelist)
A = B.T * B

q = symbols("q_p")

b = Matrix([0,0,0,0,0,0,0,q])

p = A**(-1) * b

deltap = B * p
print(B.T * deltap)